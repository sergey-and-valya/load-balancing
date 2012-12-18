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

#include "DomainModel.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

DomainModel::DomainModel(IInputFile& inputFile, IFunction& func, int steps)
	: inputFile(inputFile)
	, func(func)
	, steps(steps)
	, step(0)
{
}

void DomainModel::LoadProblem(IMPICommunicator& comm, IProblemBuilder& builder)
{
	int row_global;
	int col_global;
	int num_processor_row;
	int num_processor_col;
	
	int mpi_rank;
	comm.Rank(&mpi_rank);
	
	int mpi_size;
	comm.Size(&mpi_size);

	int x = (int)floor(sqrt((double)mpi_size));
	
	int M = x;
	int N = x;
	
	int m = 1000;
	int n = 1000;

	builder.SetBreakPointCount(M - 1, N - 1);

	int* solutionI = builder.CreateSolutionI();
	int* solutionJ = builder.CreateSolutionJ();

	for(int i = 0; i <= M; i++)
	{
		solutionI[i] = i * m - 1;
	}

	for(int j = 0; j <= N; j++)
	{
		solutionJ[j] = j * n - 1;
	}
	
	double* matrix = builder.CreateLocalMatrix();
}

bool DomainModel::Run(
	IMPICommunicator& comm,
	int time_matrix[],
	const double matrix[],
	double new_matrix[],
	const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
	const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
	int bpNumberI,
	int bpNumberJ)
{
	int rank;
	comm.Rank(&rank);
	
	int procI = rank / (bpNumberJ + 1);
	int procJ = rank % (bpNumberJ + 1);

	int dummy;
	if(procJ % 2 == 0)
	{
		if(procJ > 0)
		{
			comm.Recv(&dummy, 1, MPI_INT, rank - 1, 0, 0);
		}
		if(procJ < bpNumberJ)
		{
			comm.Recv(&dummy, 1, MPI_INT, rank + 1, 0, 0);
		}
	}
	else
	{
		if(procJ < bpNumberJ)
		{
			comm.Send(&dummy, 1, MPI_INT, rank + 1, 0);
		}
		if(procJ > 0)
		{
			comm.Send(&dummy, 1, MPI_INT, rank - 1, 0);
		}
	}
	
	if(procI % 2 == 0)
	{
		if(procI > 0)
		{
			comm.Recv(&dummy, 1, MPI_INT, rank - bpNumberI - 1, 0, 0);
		}
		if(procI < bpNumberI)
		{
			comm.Recv(&dummy, 1, MPI_INT, rank + bpNumberI + 1, 0, 0);
		}
	}
	else
	{
		if(procI < bpNumberI)
		{
			comm.Send(&dummy, 1, MPI_INT, rank + bpNumberI + 1, 0);
		}
		if(procI > 0)
		{
			comm.Send(&dummy, 1, MPI_INT, rank - bpNumberI - 1, 0);
		}
	}

	int m = solutionI[procI + 1] - solutionI[procI];
	int n = solutionJ[procJ + 1] - solutionJ[procJ];
	
	int rows = solutionI[bpNumberI + 1] + 1;
	int cols = solutionJ[bpNumberJ + 1] + 1;
	
	int p = 5;
	double px[] = {  100,     200,   2000,     500,    700 };
	double py[] = {  400,     120,    350,     400,     80 };
	double dx[] = {   20,       3,    -50,       0,    -20 };
	double dy[] = {    0,      -8,     11,      40,    120 };
	double w[]  = { 1000,   50000,   3000,  200000,  10000 };
	double a[]  = {    1,      50,     14,      50,      1 };
	double b[]  = {    1,       0,    0.5,     0.7,      1 };
	double c[]  = {    0,       1,    0.5,     0.2,      1 };

	for(int k = 0; k < p; k++)
	{
		px[p] += dx[p] * step;
		py[p] += dy[p] * step;
	}

	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int I = solutionI[procI] + i + 1;
			int J = solutionJ[procJ] + j + 1;

			//time_matrix[i * n + j] = 1 + 100 / (1.2 + sin(sqrt(((I - SI) * (I - SI) + (J - SJ) * (J - SJ)) / 100.0) + step * 0.5));
			
			time_matrix[i * n + j] = 1;
			for(int k = 0; k < p; k++)
			{
				time_matrix[i * n + j] += w[p] / (a[p] + sqrt(b[p] * (I - px[p]) * (I - px[p]) + c[p] * (J - py[p]) * (J - py[p])));
			}

			new_matrix[i * n + j] = 0;
			for(int k = 0; k < time_matrix[i * n + j]; k++)
			{
				for(int s = 0; s < 1000; s++)
				{
					if(rand())
					{
						new_matrix[i * n + j]++;
					}
				}
			}
		}
	}

	return ++step < steps;
}