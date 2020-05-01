// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Thu Dec 26 2019
//  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

#pragma once

#include <type_traits>
#include <meta/meta.hpp>
#include "executionGraph/common/Assert.hpp"
#include "executionGraph/common/MemoryUtils.hpp"
#include "executionGraph/common/SfinaeMacros.hpp"
#include "executionGraph/common/StaticAssert.hpp"
#include "executionGraph/common/TupleUtil.hpp"
#include "executionGraph/common/TypeDefs.hpp"
#include "executionGraph/nodes/LogicCommon.hpp"

namespace executionGraph
{
    /* ---------------------------------------------------------------------------------------*/
    /*!
        Sepcific data handle for `LogicDataNode<T>`.

        @date Fri Dec 27 2019
        @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
    */
    /* ---------------------------------------------------------------------------------------*/
    template<typename TData>
    class LogicDataHandle final
    {
    public:
        static constexpr bool isReadOnly = std::is_const_v<TData>;

        using Data    = TData;
        using RawData = std::remove_const_t<Data>;

        EG_STATIC_ASSERT(!std::is_reference_v<Data>, "Data needs to be no reference");

        friend class LogicDataHandle<const Data>;  //! Read-only handle is a friend.

    private:
        //! Interface for any handle passed to this instance.
        class ILogicDataHandle
        {
        public:
            virtual ~ILogicDataHandle() noexcept = default;

        public:
            //! Access to memory of the underlying data.
            virtual Data* data() noexcept = 0;
        };

        //! Type-erased wrapper, to allow any type which
        //! fulfills `ILogicDataHandle`.
        template<typename T>
        class Wrapper final : public ILogicDataHandle
        {
        public:
            template<typename... Args>
            Wrapper(Args&&... args) noexcept
                : m_handle(std::forward<Args>(args)...)
            {}

        public:
            Data* data() noexcept override
            {
                return m_handle.data();
            }

        private:
            T m_handle;
        };

    private:
        //! Check type signature of `TData`.
        template<typename T>
        static constexpr bool constructibleFrom = std::is_same_v<std::remove_const_t<Data>,
                                                                 std::remove_const_t<T>> &&
                                                  (isReadOnly || !std::is_const_v<T>);

        template<typename Handle,
                 typename T = std::remove_pointer_t<decltype(std::declval<Handle>().data())>>
        static constexpr bool constructibleFromHandle = constructibleFrom<T>;

    public:
        LogicDataHandle() noexcept = default;
        explicit LogicDataHandle(std::nullptr_t) noexcept
            : LogicDataHandle(){};

        //! Construct from another other `handle`
        //! by using an allocator `alloc`.
        //! See `memoryUtils::makeUniqueErased` to what
        //! types `RawAllocator` can be.
        template<typename Handle,
                 typename RawAllocator = memoryUtils::DefaultAllocator,
                 EG_ENABLE_IF(std::is_rvalue_reference_v<Handle&&>),
                 EG_ENABLE_IF(constructibleFromHandle<Handle>)>
        LogicDataHandle(Handle&& handle,
                        RawAllocator alloc = {}) noexcept
        {
            using H = naked<Handle>;
            static_assert(!std::is_pointer_v<H>, "No pointer allowed as `Handle` type");

            auto h   = memoryUtils::makeUniqueErased<Wrapper<Handle>>(std::move(alloc),
                                                                    std::move(handle));
            m_data   = h->data();
            m_handle = std::move(h);
        }

        //! Construct a `LogicDataHandle` by wrapping
        //! a `Handle` and its constructor `args` by using
        //! an allocator `alloc`.
        template<typename Handle,
                 typename... Args,
                 typename RawAllocator = memoryUtils::DefaultAllocator>
        static LogicDataHandle create(const std::tuple<Args...>& args,
                                      RawAllocator alloc = {})
        {
            EG_STATIC_ASSERT((... && std::is_reference_v<Args>),
                             "All `Args` in tht tuple need to be lvalue/rvalue-references!");

            return tupleUtil::invoke(
                args,
                [&](auto&&... args) {
                    return LogicDataHandle(
                        Handle(std::forward<decltype(args)>(args)...),
                        std::move(alloc));
                });
        }

        //! Copy-construction not allowed.
        LogicDataHandle(const LogicDataHandle&) = delete;
        //! Copy-assignment not allowed.
        LogicDataHandle& operator=(const LogicDataHandle&) = delete;

        //! @todo make m_handle convertible to a const m_handle
        //! unique_ptr ...

        //! Move constructor.
        template<typename T,
                 EG_ENABLE_IF(constructibleFrom<T>)>
        LogicDataHandle(LogicDataHandle<T>&& handle) noexcept
        {
            *this = std::move(handle);
        }

        //! Moves itself into a read-only handle.
        //! @post This instance is moved and is ` == nullptr`.
        LogicDataHandle<const Data> moveToConst() noexcept
        {
            EG_STATIC_ASSERT(!isReadOnly,
                             "DataHandle is already read-only, no need to convert it");
            return LogicDataHandle<const Data>{std::move(*this)};
        }

        //! Move assignment.
        template<typename T,
                 EG_ENABLE_IF(constructibleFrom<T>)>
        LogicDataHandle& operator=(LogicDataHandle<T>&& handle) noexcept
        {
            m_handle      = std::move(handle.m_handle);
            m_data        = handle.m_data;
            handle.m_data = nullptr;
            return *this;
        }

    public:
        bool operator==(std::nullptr_t) noexcept
        {
            return m_data == nullptr;
        }

        bool operator!=(std::nullptr_t) noexcept
        {
            return !(*this == nullptr);
        }

    public:
        //! Convert to bool.
        operator bool() noexcept
        {
            return m_data != nullptr;
        }

    public:
        //! Data-access.
        auto& operator*() const noexcept
        {
            return *m_data;
        }

        //! Data-access.
        auto* operator->() const noexcept
        {
            return m_data;
        }

        auto& get() const noexcept
        {
            return *m_data;
        }

    private:
        UniquePtrErased<ILogicDataHandle> m_handle;  //! The type-erased data handle.
        Data* m_data = nullptr;                      //! The actual data.
    };

    //! Invoke a function `f` with all data handles values.
    template<typename... Handles,
             typename F,
             EG_ENABLE_IF((... && meta::is_v<naked<Handles>, LogicDataHandle>))>
    decltype(auto) invoke(const std::tuple<Handles...>& handles,
                          F&& f)
    {
        return tupleUtil::invoke(
            handles,
            [&](const auto&... handles) {
                return f(handles.get()...);
            });
    }
}  // namespace executionGraph