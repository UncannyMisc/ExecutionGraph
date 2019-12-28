//! ========================================================================================
//!  ExecutionGraph
//!  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//!
//!  @date Tue Jan 09 2018
//!  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//!
//!  This Source Code Form is subject to the terms of the Mozilla Public
//!  License, v. 2.0. If a copy of the MPL was not distributed with this
//!  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//! ========================================================================================

#pragma once

#include <memory>
#include "executionGraph/common/Assert.hpp"

namespace executionGraph
{
    /* ---------------------------------------------------------------------------------------*/
    /*!
        A singelton class which does not construct the type on the fly like most implementations
        The Singelton needs to be explicity instanciated somewhere, best in the main(...) 
        function!
        See the makros below!

        @date Sun Feb 18 2018
        @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
     */
    /* ---------------------------------------------------------------------------------------*/
    template<typename T>
    class Singleton
    {
    private:
        struct Creator
        {
            Creator(T* p) { instance = p; }
            static T* instance;  //!< Gets initialized by a static class of Creator.
        };

    public:
        Singleton()
        {
            static Creator s(static_cast<T*>(this));  //!< First thread initializes the pointer! (Thread-Safe -> "magic statics")
        }
        ~Singleton()
        {
            Creator::instance = nullptr;
        }

        //! deleted copy constructor. This is a forbidden operation.
        Singleton(const Singleton<T>&) = delete;

        //! deleted operator= . This is a forbidden operation.
        Singleton& operator=(const Singleton<T>&) = delete;

    public:
        static T& getInstance(void)
        {
            EG_ASSERT(Creator::instance, "Singleton not instanciated!");
            return *Creator::instance;
        }

        static T* getInstancePtr(void)
        {
            return Creator::instance;
        }
    };

    template<typename T>
    T* Singleton<T>::Creator::instance = nullptr;

}  // namespace executionGraph

//! Instanciate a singelton `name` with type `type` and ctor arguments `ctor_args`.
#define EG_INSTANCIATE_SINGLETON_CTOR(type, name, ctor_args) \
    auto name = std::unique_ptr<type>(new type ctor_args);

//! Instanciate a singelton `name` with type `type`.
#define EG_INSTANCIATE_SINGLETON(type, name) INSTANCIATE_UNIQUE_SINGELTON_CTOR(type, name, ())
