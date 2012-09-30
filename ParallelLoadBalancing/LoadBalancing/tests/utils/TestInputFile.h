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

#ifndef _TESTINPUTFILE_H
#define _TESTINPUTFILE_H

#include "../../IInputFile.h"
#include <functional>

class TestInputFile : public IInputFile
{
public:
	typedef std::function<size_t(void*, size_t, size_t)> ReadFunction;
	typedef std::function<int(long, int)> SeekFunction;

	TestInputFile(ReadFunction readImpl, SeekFunction seekImpl)
		: m_readImpl(readImpl)
		, m_seekImpl(seekImpl)
	{
	}

	
	size_t Read(void *buffer, size_t elementSize, size_t count)
	{
		return m_readImpl(buffer, elementSize, count);
	}

	int Seek(long offset, int origin)
	{
		return m_seekImpl(offset, origin);
	}

private:
	ReadFunction m_readImpl;
	SeekFunction m_seekImpl;
};

#endif
