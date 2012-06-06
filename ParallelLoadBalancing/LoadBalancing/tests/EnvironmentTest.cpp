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
	int bpNumberI = 5;
	int bpNumberJ = 6;
	int mpiRank = 10;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

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
			return MPI_SUCCESS;
		},
		[](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			return MPI_SUCCESS;
		}
	);

	auto lb = TestLoadBalancing(
		[procI, procJ](IMPICommunicator& comm, const int time_matrix[], const int oldSolutionI[], const int oldSolutionJ[], int bpNumberI, int bpNumberJ, int newSolutionI[], int newSolutionJ[])
		{
			newSolutionI[procI]--;
		}
	);
	
	auto ts = TestTestingSystem(
		[bpNumberI, bpNumberJ](IMPICommunicator& comm, IProblemBuilder& builder)
		{
			int height = (bpNumberI + 1) * 100;
			int width  = (bpNumberJ + 1) * 100;

			builder.SetBreakPointCount(bpNumberI, bpNumberJ);
			
			auto solutionI = builder.CreateSolutionI();
			auto solutionJ = builder.CreateSolutionJ();
			
			solutionI[0] = -1;
			solutionJ[0] = -1;
			
			solutionI[bpNumberI + 1] = height - 1;
			solutionJ[bpNumberJ + 1] = width - 1;
			
			for(int i = 1; i <= bpNumberI; i++)
			{
				solutionI[i] = i * 100 - 1;
			}
			
			for(int i = 1; i <= bpNumberJ; i++)
			{
				solutionJ[i] = i * 100 - 1;
			}

			auto localMatrix = builder.CreateLocalMatrix();
			
			int mpiRank;

			comm.Rank(&mpiRank);

			int procI = mpiRank / (bpNumberJ + 1);
			int procJ = mpiRank % (bpNumberJ + 1);

			for(int i = 0; i < 100; i++)
			{
				for(int j = 0; j < 100; j++)
				{
					localMatrix[i * 100 + j] = i * width + j;
				}
			}
		},
		[](IMPICommunicator& comm, int time_matrix[], const double matrix[], double new_matrix[], const int solutionI[], const int solutionJ[], int bpNumberI, int bpNumberJ)
		{
		}
	);
	
	auto rb = TestRebalancer(
		[](IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ)
		{
		}
	);

	env.Run(comm, ts, lb, rb);
}
