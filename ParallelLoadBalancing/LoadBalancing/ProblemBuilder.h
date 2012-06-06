#ifndef _PROBLEMBUILDER_H
#define _PROBLEMBUILDER_H

#include "IProblemBuilder.h"
#include "mpi.h"

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