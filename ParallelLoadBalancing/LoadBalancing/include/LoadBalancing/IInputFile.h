// ****************************************************************************
// LOAD BALANCING
// Copyright (C) 2012 Gerasimov, Smoryakova, Katerov, Afanasov, Kulakovich, Sobolev
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ****************************************************************************

#ifndef _IINPUTFILE_H
#define _IINPUTFILE_H

#include <stddef.h>

/**
 * \class   IInputFile
 *
 * \brief   Input file interface. Absraction for read-only file.
 */

class IInputFile
{
public:

    /**
     * \fn  virtual size_t IInputFile::Read(void *buffer, size_t elementSize, size_t count) = 0;
     *
     * \brief   Reads an array of \a count elements, each one with a size of \a elementSize bytes, from the file and stores them in the block of memory specified by \a buffer.
     *
     * \param [out]  buffer     Pointer to a block of memory with a minimum size of (\a elementSize * \a count) bytes.
     * \param   elementSize     Size in bytes of each element to be read.
     * \param   count           Number of elements, each one with a size of \a elementSize bytes.
     *
     * \return  The total number of elements successfully read.
     */

	virtual size_t Read(void *buffer, size_t elementSize, size_t count) = 0;

    /**
     * \fn  virtual int IInputFile::Seek(long offset, int origin) = 0;
     *
     * \brief   Sets the position indicator associated with the stream to a new position defined by adding offset to a reference position specified by origin.
     *
     * \param   offset  Number of bytes to offset from origin.
     * \param   origin  Position from where offset is added. It is specified by one of the following constants:
     *                  \a SEEK_SET Beginning of file
     *                  \a SEEK_CUR Current position of the file pointer
     *                  \a SEEK_END End of file
     *
     * \return  If successful, the function returns a zero value.
     *          Otherwise, it returns nonzero value.
     */

    virtual int Seek(long offset, int origin) = 0;
};

#endif
