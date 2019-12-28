// =========================================================================================
//  ExecutionGraph
//  Copyright (C) 2014 by Gabriel Nützi <gnuetzi (at) gmail (døt) com>
//
//  @date Sat Apr 28 2018
//  @author Gabriel Nützi, gnuetzi (at) gmail (døt) com
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
// =========================================================================================

#include "executionGraph/serialization/FileMapper.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "executionGraph/common/Exception.hpp"

namespace executionGraph
{
    //! Construktor loading a file into memory.
    FileMapper::FileMapper(const std::path& filePath)
    {
        load(filePath);
    }

    //! Destructor unloading the file from memory.
    FileMapper::~FileMapper()
    {
        close();
    }

    //! Loads a file into memory.
    //! Taken from https://www.safaribooksonline.com/library/view/linux-system-programming/0596009585/ch04s03.html
    //! Throws exception if something goes wrong!
    void FileMapper::load(const std::path& filePath)
    {
        m_filePath = filePath;
        // Map the file into memory

        auto fileDescriptor = ::open(m_filePath.c_str(), O_RDONLY);
        EG_THROW_IF(fileDescriptor == -1, "File '{0}' could not be opened!", m_filePath);

        struct stat sb;
        EG_THROW_IF(::fstat(fileDescriptor, &sb) == -1,
                           "Could not read file stats '{0}",
                           m_filePath);
        EG_THROW_IF(!S_ISREG(sb.st_mode),
                           "File '{0}' is not a file!",
                           m_filePath);

        m_mappedBytes   = sb.st_size;  // Map the whole file!
        m_offset        = 0;
        m_mappedAddress = ::mmap(0, m_mappedBytes, PROT_READ, MAP_SHARED, fileDescriptor, m_offset);
        EG_THROW_IF(m_mappedAddress == MAP_FAILED,
                           "File '{0}' could not be mapped in memory!",
                           m_filePath);

        EG_THROW_IF(::close(fileDescriptor) == -1,
                           "Unused file descriptor '{0}' could not be closed!",
                           m_filePath);
    }

    //! Close the mapped file.
    void FileMapper::close()
    {
        if(m_mappedAddress)
        {
            // Remove the memory mapped file (no error checking!)
            munmap(m_mappedAddress, m_mappedBytes);
            m_mappedAddress = nullptr;
            m_mappedBytes   = 0;
            m_offset        = 0;
            m_filePath.clear();
        }
    }

    //! Move-Construct the FileMapper and reset `other`.
    FileMapper::FileMapper(FileMapper&& other)
    {
        *this = std::move(other);
    }

    //! Move-Assign the FileMapper and reset `other`.
    FileMapper& FileMapper::operator=(FileMapper&& other)
    {
        m_filePath = std::move(other.m_filePath);

        m_offset       = std::move(other.m_offset);
        other.m_offset = 0;

        m_mappedAddress       = std::move(other.m_mappedAddress);
        other.m_mappedAddress = nullptr;

        m_mappedBytes       = std::move(other.m_mappedBytes);
        other.m_mappedBytes = 0;

        return *this;
    }
}  // namespace executionGraph