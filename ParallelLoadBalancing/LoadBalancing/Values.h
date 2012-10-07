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

#ifndef _VALUES_H
#define _VALUES_H

#include <vector>

class Values
{
public:
	Values(size_t blockSize) : values(blockSize * blockSize)
							 , blockSize(blockSize)
							 , offsetI(0)
							 , offsetJ(0)
	{
	}

	void SetValue(int i, int j, double value)
	{
		values[i + j * blockSize] = value;
	}
	
	double Value(int i, int j) const
	{
		return values[i + j * blockSize];
	}

	void SetOffsetI(int offsetI)
	{
		this->offsetI = offsetI;
	}

	void SetOffsetJ(int offsetJ)
	{
		this->offsetJ = offsetJ;
	}

	bool HasValue(int i, int j) const
	{
		return (0 <= i - offsetI) && (i - offsetI < (int)blockSize) &&
			   (0 <= j - offsetJ) && (j - offsetJ < (int)blockSize);
	}

    

protected:
	std::vector<double> values;
	size_t blockSize;
	int offsetI;
	int offsetJ;
};

#endif