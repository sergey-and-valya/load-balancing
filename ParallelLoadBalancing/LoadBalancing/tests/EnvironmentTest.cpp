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

#include "EnvironmentTest.h"

#include <LoadBalancing/IDomainModel.h>
#include <LoadBalancing/ILoadBalancingAlgorithm.h>
#include <LoadBalancing/IEnvironment.h>
#include <LoadBalancing/IMPICommunicator.h>

#include "../Environment.h"
#include "utils/MockCommunicator.h"
#include "utils/MockLoadBalancingAlgorithm.h"
#include "utils/MockLoadBalancingCondition.h"
#include "utils/MockDomainModel.h"
#include "utils/MockRebalancer.h"
#include "utils/Assert.h"


void EnvironmentTest()
{
	int localWidth  = 100;
	int localHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int step = 0;
	int steps = 10;

	auto env = Environment(false);

	auto comm = MockCommunicator(
		[bpNumberI, bpNumberJ](int* size) -> int
		{
			*size = (bpNumberI + 1) * (bpNumberJ + 1);
			return MPI_SUCCESS;
		},
		[mpiRank](int* rank) -> int
		{
			*rank = mpiRank;
			return MPI_SUCCESS;
		},
		[](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			assert(false);
			return MPI_SUCCESS;
		},
		[](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			assert(false);
			return MPI_SUCCESS;
		}
	);

	auto lb = MockLoadBalancingAlgorithm(
		[procI](IMPICommunicator& comm, const int time_matrix[], const int oldSolutionI[], const int oldSolutionJ[], int bpNumberI, int bpNumberJ, int newSolutionI[], int newSolutionJ[]) -> bool
		{
			newSolutionI[procI]--;
			return false;
		}
	);
	
	auto dm = MockDomainModel(
		[localWidth, localHeight, bpNumberI, bpNumberJ](IMPICommunicator& comm, IProblemBuilder& builder)
		{
			builder.SetBreakPointCount(bpNumberI, bpNumberJ);
			
			auto solutionI = builder.CreateSolutionI();
			auto solutionJ = builder.CreateSolutionJ();
						
			for(int i = 0; i <= bpNumberI + 1; i++)
			{
				solutionI[i] = i * localHeight - 1;
			}

			for(int i = 0; i <= bpNumberJ + 1; i++)
			{
				solutionJ[i] = i * localWidth - 1;
			}
	

			auto localMatrix = builder.CreateLocalMatrix();
			
			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					localMatrix[i * localWidth + j] = i * localWidth + j;
				}
			}
		},
		[&step, steps, localWidth, localHeight](IMPICommunicator& comm, int time_matrix[], const double matrix[], double new_matrix[], const int solutionI[], const int solutionJ[], int bpNumberI, int bpNumberJ) -> bool
		{
			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					assert(matrix[i * localWidth + j] == i * localWidth + j + step * (bpNumberI + 1) * (bpNumberJ + 1));
				}
			}

			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					time_matrix[i * localWidth + j] = i * localWidth + j;
					new_matrix[i * localWidth + j]  = i * localWidth + j + (step + 1) * (bpNumberI + 1) * (bpNumberJ + 1);
				}
			}

			return ++step < steps;
		}
	);
	
	auto rb = MockRebalancer(
		[localWidth, localHeight](IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const void* oldMatrix, const int newSolutionI[], const int newSolutionJ[], void* newMatrix, int bpNumberI, int bpNumberJ, MPI_Datatype datatype)
		{
			assert(oldSolutionI);
			assert(datatype == MPI_INT);
			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					static_cast<int*>(newMatrix)[i * localWidth + j] = i * localWidth + j;
				}
			}
		}
	);
	
	

	auto lbc = MockLoadBalancingCondition(
		[](IMPICommunicator& comm, const int time_matrix[], const int solutionI[], const int solutionJ[], int bpNumberI, int bpNumberJ)
		{
			return true;
		},
		[]()
		{
		}
	);

	env.Run(comm, dm, lb, lbc, rb);
}
