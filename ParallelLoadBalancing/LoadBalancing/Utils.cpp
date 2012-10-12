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

#include "Utils.h"

#include <stdio.h>
#include <LoadBalancing/IMPICommunicator.h>

void PrintDistributedMatrix(IMPICommunicator& comm, int bpNumberI, int bpNumberJ, const double localMatrix[], int localWidth, int localHeight)
{
	int mpiRank;
	comm.Rank(&mpiRank);
	
	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int _;

	if(procJ == 0 && procI > 0)
	{
		comm.Recv(&_, 1, MPI_INTEGER, mpiRank - 1, 0, NULL);
	}

	for(int i = 0; i < localHeight; i++)
	{
		if(procJ > 0)
		{
			comm.Recv(&_, 1, MPI_INTEGER, mpiRank - 1, 0, NULL);
		}
		else if(i > 0)
		{
			comm.Recv(&_, 1, MPI_INTEGER, mpiRank + bpNumberJ, 0, NULL);
		}

		for(int j = 0; j < localWidth; j++)
		{
			printf("%-8lg ", localMatrix[i * localWidth + j]);
		}
	
		if(procJ < bpNumberJ)
		{
			comm.Send(&_, 1, MPI_INTEGER, mpiRank + 1, 0);
		}
		else
		{
			printf("\n");
				
			if(i < localHeight - 1)
			{
				comm.Send(&_, 1, MPI_INTEGER, mpiRank - bpNumberJ, 0);
			}
		}
	}
	
	if(procI < bpNumberI && procJ == bpNumberJ)
	{
		comm.Send(&_, 1, MPI_INTEGER, mpiRank + 1, 0);
	}
	
	if(mpiRank + 1 < (bpNumberI + 1) * (bpNumberJ + 1))
	{
		comm.Recv(&_, 1, MPI_INTEGER, mpiRank + 1, 0, NULL);
	}
	else
	{
		printf("\n");
	}

	if(mpiRank > 0)
	{
		comm.Send(&_, 1, MPI_INTEGER, mpiRank - 1, 0);
	}
}
