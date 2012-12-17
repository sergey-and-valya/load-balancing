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

#include "Environment.h"

#include "ProblemBuilder.h"
#include "Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void Environment::Run(IMPICommunicator& comm, IDomainModel& dm, ILoadBalancingAlgorithm& lb, ILoadBalancingCondition& lbc, IRebalancer& rb)
{
	int mpi_size;
	int mpi_rank;

	comm.Size(&mpi_size);
	comm.Rank(&mpi_rank);
	
	int currentSolution = 0;
	int currentMatrix = 0;

	int* solutionI[2];
	int* solutionJ[2];
	double* matrix[2];
	int* time_matrix[2];
	int bpNumberI;
	int bpNumberJ;

	ProblemBuilder pb(comm, &solutionI[0], &solutionJ[0], &matrix[0], &bpNumberI, &bpNumberJ, malloc);
	dm.LoadProblem(comm, pb);
	
	int procI = mpi_rank / (bpNumberJ + 1);
	int procJ = mpi_rank % (bpNumberJ + 1);

	int matrixHeight = solutionI[0][procI + 1] - solutionI[0][procI];
	int matrixWidth = solutionJ[0][procJ + 1] - solutionJ[0][procJ];
		
	solutionI[1] = (int*)malloc(sizeof(int) * (bpNumberI + 2));
	solutionJ[1] = (int*)malloc(sizeof(int) * (bpNumberJ + 2));
	
	matrix[1]   = (double*)malloc(sizeof(double) * matrixHeight * matrixWidth);
	time_matrix[0] = (int*)malloc(sizeof(int)    * matrixHeight * matrixWidth);
	time_matrix[1] = (int*)malloc(sizeof(int)    * matrixHeight * matrixWidth);

	while(dm.Run(comm, time_matrix[currentMatrix], matrix[currentMatrix], matrix[(currentMatrix + 1) % 2], solutionI[currentSolution], solutionJ[currentSolution], bpNumberI, bpNumberJ))
	{
		lbc.Reset();

		while(lbc.ShouldRebalance(comm, time_matrix[currentMatrix],
				solutionI[currentSolution], solutionJ[currentSolution],
				bpNumberI, bpNumberJ))
		{
			int newSolution = (currentSolution + 1) % 2;
			memcpy(solutionI[newSolution], solutionI[currentSolution], (bpNumberI + 2) * sizeof(int));
			memcpy(solutionJ[newSolution], solutionJ[currentSolution], (bpNumberJ + 2) * sizeof(int));

			bool canRunAgain = lb.Run(comm,
				time_matrix[currentMatrix],
				solutionI[currentSolution], solutionJ[currentSolution],
				bpNumberI, bpNumberJ,
				solutionI[newSolution], solutionJ[newSolution]
				);
				
			int newMatrix = (currentMatrix + 1) % 2;
			int newMatrixHeight = solutionI[newSolution][procI + 1] - solutionI[newSolution][procI];
			int newMatrixWidth  = solutionJ[newSolution][procJ + 1] - solutionJ[newSolution][procJ];

			if(newMatrixHeight * newMatrixWidth != matrixHeight * matrixWidth)
			{
				matrix[newMatrix]      = (double*)realloc(matrix[newMatrix],      sizeof(double) * newMatrixHeight * newMatrixWidth);
				time_matrix[newMatrix] = (int*)   realloc(time_matrix[newMatrix], sizeof(int)    * newMatrixHeight * newMatrixWidth);
			}

			rb.Rebalance(comm, solutionI[currentSolution], solutionJ[currentSolution], matrix[currentMatrix],      solutionI[newSolution], solutionJ[newSolution], matrix[newMatrix],      bpNumberI, bpNumberJ, MPI_DOUBLE, sizeof(double));
			rb.Rebalance(comm, solutionI[currentSolution], solutionJ[currentSolution], time_matrix[currentMatrix], solutionI[newSolution], solutionJ[newSolution], time_matrix[newMatrix], bpNumberI, bpNumberJ, MPI_INT,    sizeof(int));
			
			currentSolution = newSolution;

			if(newMatrixHeight * newMatrixWidth != matrixHeight * matrixWidth)
			{
				matrix[currentMatrix]      = (double*)realloc(matrix[currentMatrix],      sizeof(double) * newMatrixHeight * newMatrixWidth);
				time_matrix[currentMatrix] = (int*)   realloc(time_matrix[currentMatrix], sizeof(int)    * newMatrixHeight * newMatrixWidth);
			}
			
			matrixWidth   = newMatrixWidth;
			matrixHeight  = newMatrixHeight;
			currentMatrix = newMatrix;

			if(!canRunAgain)
				break;
		}
	}

	
	if(printResults)
	{
		PrintDistributedMatrix(comm, bpNumberI, bpNumberJ, matrix[currentMatrix], matrixWidth, matrixHeight);
	}

	free(solutionI[0]);
	free(solutionJ[0]);
	free(solutionI[1]);
	free(solutionJ[1]);
	free(matrix[0]);
	free(matrix[1]);
	free(time_matrix[0]);
	free(time_matrix[1]);
}
