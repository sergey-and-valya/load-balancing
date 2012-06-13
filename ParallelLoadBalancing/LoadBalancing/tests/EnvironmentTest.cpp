#include "EnvironmentTest.h"

#include "../ITestingSystem.h"
#include "../ILoadBalancingAlgorithm.h"
#include "../IEnvironment.h"
#include "../IMPICommunicator.h"

#include "../Environment.h"
#include "utils/TestCommunicator.h"
#include "utils/TestLoadBalancing.h"
#include "utils/TestTestingSystem.h"
#include "utils/TestRebalancer.h"
#include "utils/Assert.h"


void EnvironmentTest()
{
	
	int localWidth  = 100;
	int localHeight = 200;
	int newLocalWidth;
	int newLocalHeight;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int step = 0;
	int steps = 10;

	int state = 0;

	auto env = Environment(true);

	auto comm = TestCommunicator(
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

	auto lb = TestLoadBalancing(
		[&state, &newLocalWidth, &newLocalHeight, procI](IMPICommunicator& comm, const int time_matrix[], const int oldSolutionI[], const int oldSolutionJ[], int bpNumberI, int bpNumberJ, int newSolutionI[], int newSolutionJ[])
		{
			state = (state + 1) % 2;
			switch(state)
			{
			case 0:
				{
					newLocalHeight--;
					newSolutionI[procI]--;
					break;
				}
			default:
				{
					assert(false);
				}
			}
		}
	);
	
	auto ts = TestTestingSystem(
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
		[&step, steps, &localWidth, &localHeight](IMPICommunicator& comm, int time_matrix[], const double matrix[], double new_matrix[], const int solutionI[], const int solutionJ[], int bpNumberI, int bpNumberJ) -> bool
		{
			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					assert(matrix[i * localWidth + j] == i * localWidth + j);
				}
			}

			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					time_matrix[i * localWidth + j] = i * localWidth + j;
					time_matrix[i * localWidth + j] = i * localWidth + j;
				}
			}
			return ++step < steps;
		}
	);
	
	auto rb = TestRebalancer(
		[&localWidth, &localHeight](IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ)
		{
			for(int i = 0; i < localHeight; i++)
			{
				for(int j = 0; j < localWidth; j++)
				{
					newMatrix[i * localWidth + j] = i * localWidth + j;
				}
			}
		}
	);

	env.Run(comm, ts, lb, rb);
}
