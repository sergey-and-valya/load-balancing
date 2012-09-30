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

#ifndef _PROBLEMBUILDER_H
#define _PROBLEMBUILDER_H

#include "IProblemBuilder.h"

typedef void* (*arrayAllocator)(size_t bytes);

class ProblemBuilder : public IProblemBuilder
{
public:
	ProblemBuilder(IMPICommunicator& comm, int** solutionI, int** solutionJ, double** matrix, int* bpNumberI, int* bpNumberJ, arrayAllocator alloc)
		: comm(comm)
		, solutionI(solutionI)
		, solutionJ(solutionJ)
		, matrix(matrix)
		, bpNumberI(bpNumberI)
		, bpNumberJ(bpNumberJ)
		, alloc(alloc)
	{}

	void SetBreakPointCount(int bpNumberI, int bpNumberJ)
	{
		*this->bpNumberI = bpNumberI;
		*this->bpNumberJ = bpNumberJ;
	}

	int* CreateSolutionI()
	{
		*solutionI = (int*)alloc(sizeof(int) * ((*bpNumberI) + 2));
		return *solutionI;
	}

	int* CreateSolutionJ()
	{
		*solutionJ = (int*)alloc(sizeof(int) * ((*bpNumberJ) + 2));
		return *solutionJ;
	}
	
	double* CreateLocalMatrix()
	{
		int mpi_rank;

		comm.Rank(&mpi_rank);
	
		int procI = mpi_rank / (*bpNumberJ + 1);
		int procJ = mpi_rank % (*bpNumberJ + 1);

		int matrixRows = (*solutionI)[procI + 1] - (*solutionI)[procI];
		int matrixCols = (*solutionJ)[procJ + 1] - (*solutionJ)[procJ];
	
		*matrix = (double*)alloc(sizeof(double) * matrixRows * matrixCols);
		return *matrix;
	}

private:
	int** solutionI;
	int** solutionJ;
	double** matrix;
	int* bpNumberI;
	int* bpNumberJ;
	arrayAllocator alloc;
	IMPICommunicator& comm;
};

#endif
