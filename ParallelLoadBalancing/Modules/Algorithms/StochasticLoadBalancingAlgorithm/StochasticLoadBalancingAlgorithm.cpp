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

#include "StochasticLoadBalancingAlgorithm.h"
#include <memory.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

StochasticLoadBalancingAlgorithm::StochasticLoadBalancingAlgorithm()
	: vertical(true)
	, offset(0)
{
	srand(time(0));
}

void Barrier(IMPICommunicator& comm)
{
	int mpiRank;
	int dummy;
	comm.Rank(&mpiRank);

	if(mpiRank == 0)
	{
		int mpiSize;
		comm.Size(&mpiSize);

		MPI_Status s;
		for(int i = 1; i < mpiSize; ++i)
		{
			comm.Recv(&dummy, 1, MPI_INT, i, 0, 0);
		}
	}
	else
	{
		comm.Send(&dummy, 1, MPI_INT, 0, 0);
	}
}

void StochasticLoadBalancingAlgorithm::Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[])
{
	int mpiSize;
	int mpiRank;
	
	comm.Size(&mpiSize);
	comm.Rank(&mpiRank);
	
	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);
	
	int startI = oldSolutionI[procI] + 1;
	int endI   = oldSolutionI[procI + 1] + 1;
	
	int startJ = oldSolutionJ[procJ] + 1;
	int endJ   = oldSolutionJ[procJ + 1] + 1;
	
	int rows = endI - startI;
	int cols = endJ - startJ;

	int myTotalSum  = 0;
	int hisTotalSum = 0;

	if(vertical)
	{
		bool left = procJ % 2 == offset;

		if(left && (procJ + 1 < bpNumberJ + 1) || !left && procJ > 0)
		{
			int* sums = new int[cols];
		
			for(int j = 0; j < cols; ++j)
			{
				int sum = 0;
				for(int i = 0; i < rows; ++i)
				{
					 sum += time_matrix[i * cols + j];
				}

				if(left)
				{
					sums[cols - j - 1] = sum;
				}
				else
				{
					sums[j] = sum;
				}

				myTotalSum += sum;
			}

			if(left)
			{
				comm.Send(&myTotalSum,  1, MPI_INT, mpiRank + 1, 0);
				comm.Recv(&hisTotalSum, 1, MPI_INT, mpiRank + 1, 0, 0);
			}
			else
			{
				comm.Recv(&hisTotalSum, 1, MPI_INT, mpiRank - 1, 0, 0);
				comm.Send(&myTotalSum,  1, MPI_INT, mpiRank - 1, 0);
			}

			int movement = 0;
			if(myTotalSum > hisTotalSum)
			{
				int diff = myTotalSum - hisTotalSum;
				int oldDiff;
			
				do
				{
					myTotalSum -= sums[movement];
					hisTotalSum += sums[movement];
					++movement;
					oldDiff = diff;
					diff = abs(myTotalSum - hisTotalSum);
				}
				while(oldDiff > diff);
				--movement;

				if(left)
				{
					movement = -movement;
				}
				else
				{
					comm.Send(&movement, 1, MPI_INT, mpiRank - 1, 0);
				}
			}
			else if(left)
			{
				comm.Recv(&movement, 1, MPI_INT, mpiRank + 1, 0, 0);
			}

			delete[] sums;
		
			if(left)
			{
				int myMinMax[] = { movement, movement };

				int step = 1;

				while(true)
				{
					int theirMinMax[2];

					if(procI % (step + 1) == 0)
					{
						if(procI + step >= bpNumberI + 1)
							break;

						comm.Recv(theirMinMax, 2, MPI_INT, mpiRank + step * (bpNumberJ + 1), 0, 0);
				
						if(myMinMax[0] > theirMinMax[0])
							myMinMax[0] = theirMinMax[0];
				
						if(myMinMax[1] < theirMinMax[1])
							myMinMax[1] = theirMinMax[1];
					}
					else
					{
						comm.Send(myMinMax, 2, MPI_INT, mpiRank - step * (bpNumberJ + 1), 0);
						break;
					}

					step *= 2;
				}

				if(procI == 0)
				{
					bool moveLeft = myMinMax[0] < 0;
					if(myMinMax[0] * myMinMax[1] > 0)
					{
						newSolutionJ[procJ + 1] += myMinMax[0];
					}

					if(rand() % 2 == 0)
					{
						newSolutionJ[procJ + 1] += moveLeft ? -1 : 1;
					}
				}

				while(step > 0)
				{
					if(procI % (step + 1) == 0)
					{
						if(procI + step < bpNumberI + 1)
							comm.Send(newSolutionJ + procJ + 1, 1, MPI_INT, mpiRank + step * (bpNumberJ + 1), 0);
					}
					else
					{
						comm.Recv(newSolutionJ + procJ + 1, 1, MPI_INT, mpiRank - step * (bpNumberJ + 1), 0, 0);
					}

					step /= 2;
				}
			}

			if(left)
			{
				comm.Send(newSolutionJ + procJ + 1, 1, MPI_INT, mpiRank + 1, 0);
			}
			else
			{
				comm.Recv(newSolutionJ + procJ, 1, MPI_INT, mpiRank - 1, 0, 0);
			}
		}
	}
	else
	{
		bool top = procI % 2 == offset;

		if(top && (procI + 1 < bpNumberI + 1) || !top && procI > 0)
		{
			int* sums = new int[rows];
		
			for(int i = 0; i < rows; ++i)
			{
				int sum = 0;
				for(int j = 0; j < cols; ++j)
				{
					 sum += time_matrix[i * cols + j];
				}

				if(top)
				{
					sums[rows - i - 1] = sum;
				}
				else
				{
					sums[i] = sum;
				}

				myTotalSum += sum;
			}

			if(top)
			{
				comm.Send(&myTotalSum,  1, MPI_INT, mpiRank + bpNumberJ + 1, 0);
				comm.Recv(&hisTotalSum, 1, MPI_INT, mpiRank + bpNumberJ + 1, 0, 0);
			}
			else
			{
				comm.Recv(&hisTotalSum, 1, MPI_INT, mpiRank - bpNumberJ - 1, 0, 0);
				comm.Send(&myTotalSum,  1, MPI_INT, mpiRank - bpNumberJ - 1, 0);
			}

			int movement = 0;
			if(myTotalSum > hisTotalSum)
			{
				int diff = myTotalSum - hisTotalSum;
				int oldDiff;
			
				do
				{
					myTotalSum -= sums[movement];
					hisTotalSum += sums[movement];
					++movement;
					oldDiff = diff;
					diff = abs(myTotalSum - hisTotalSum);
				}
				while(oldDiff > diff);
				--movement;

				if(top)
				{
					movement = -movement;
				}
				else
				{
					comm.Send(&movement, 1, MPI_INT, mpiRank - bpNumberJ - 1, 0);
				}
			}
			else if(top)
			{
				comm.Recv(&movement, 1, MPI_INT, mpiRank + bpNumberJ + 1, 0, 0);
			}

			delete[] sums;
		
			if(top)
			{
				int myMinMax[] = { movement, movement };

				int step = 1;

				while(true)
				{
					int theirMinMax[2];

					if(procJ % (step + 1) == 0)
					{
						if(procJ + step >= bpNumberJ + 1)
							break;

						comm.Recv(theirMinMax, 2, MPI_INT, mpiRank + step, 0, 0);
				
						if(myMinMax[0] > theirMinMax[0])
							myMinMax[0] = theirMinMax[0];
				
						if(myMinMax[1] < theirMinMax[1])
							myMinMax[1] = theirMinMax[1];
					}
					else
					{
						comm.Send(myMinMax, 2, MPI_INT, mpiRank - step, 0);
						break;
					}

					step *= 2;
				}

				if(procJ == 0)
				{
					bool moveTop = myMinMax[0] < 0;
					if(myMinMax[0] * myMinMax[1] > 0)
					{
						newSolutionI[procI + 1] += myMinMax[0];
					}

					if(rand() % 2 == 0)
					{
						newSolutionI[procI + 1] += moveTop ? -1 : 1;
					}
				}

				while(step > 0)
				{
					if(procJ % (step + 1) == 0)
					{
						if(procJ + step < bpNumberJ + 1)
							comm.Send(newSolutionI + procI + 1, 1, MPI_INT, mpiRank + step, 0);
					}
					else
					{
						comm.Recv(newSolutionI + procI + 1, 1, MPI_INT, mpiRank - step, 0, 0);
					}

					step /= 2;
				}
			}

			if(top)
			{
				comm.Send(newSolutionI + procI + 1, 1, MPI_INT, mpiRank + bpNumberJ + 1, 0);
			}
			else
			{
				comm.Recv(newSolutionI + procI, 1, MPI_INT, mpiRank - bpNumberJ - 1, 0, 0);
			}
		}

		offset = 1 - offset;
	}

	vertical = !vertical;
}
