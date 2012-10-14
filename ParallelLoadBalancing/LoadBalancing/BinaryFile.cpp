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

#include "BinaryFile.h"

BinaryFile::BinaryFile(const char* filename)
{
	file = fopen(filename, "rb");
}

BinaryFile::~BinaryFile()
{
	fclose(file);
}

size_t BinaryFile::Read(void *buffer, size_t elementSize, size_t count)
{
	return fread(buffer, elementSize, count, file);
}

int BinaryFile::Seek(long offset, int origin)
{
	return fseek(file, offset, origin);
}
