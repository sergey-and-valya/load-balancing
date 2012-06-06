#include "RebalancerTest.h"

#include "utils/Assert.h"
#include "utils/TestCommunicator.h"

#include "../IRebalancer.h"
#include "../IMPICommunicator.h"

#include "../Rebalancer.h"

void RebalancerNoMoveTest()
{
	auto rb = Rebalancer();

	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;

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
			return 0;
		},
		[](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			assert(false);
			return 0;
		}
	);

	
	auto oldMatrix = new double[oldLocalWidth * oldLocalHeight];
	
	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth; j++)
		{
			oldMatrix[i * oldLocalWidth + j] = i * oldLocalWidth + j;
		}
	}
	
	auto newMatrix = new double[oldLocalWidth * oldLocalHeight];
	
	auto oldSolutionI = new int[bpNumberI + 2];
	auto oldSolutionJ = new int[bpNumberJ + 2];

	auto newSolutionI = new int[bpNumberI + 2];
	auto newSolutionJ = new int[bpNumberJ + 2];
	
				
	for(int i = 0; i <= bpNumberI + 1; i++)
	{
		oldSolutionI[i] = i * oldLocalHeight - 1;
		newSolutionI[i] = oldSolutionI[i];
	}

	for(int i = 0; i <= bpNumberJ + 1; i++)
	{
		oldSolutionJ[i] = i * oldLocalWidth - 1;
		newSolutionJ[i] = oldSolutionJ[i];
	}
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * oldLocalWidth + j]);
		}
	}
}


void RebalancerMoveLeftTest()
{
	auto rb = Rebalancer();

	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int receiveCalls = 0;

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
			return 0;
		},
		[oldLocalHeight, mpiRank, &receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			switch(receiveCalls)
			{
			case 1:
				{
					assert(source == mpiRank - 1);
					assert(count == oldLocalHeight);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -i - 1;
					}
				
					return MPI_SUCCESS;

					break;
				}
			default:
				{
					assert(false);
					return 0;
					break;
				}
			}
			return 0;
		}
	);

	
	auto oldMatrix = new double[oldLocalWidth * oldLocalHeight];
	
	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth; j++)
		{
			oldMatrix[i * oldLocalWidth + j] = i * oldLocalWidth + j;
		}
	}
	
	auto newMatrix = new double[(oldLocalWidth + 1) * oldLocalHeight];
	
	auto oldSolutionI = new int[bpNumberI + 2];
	auto oldSolutionJ = new int[bpNumberJ + 2];

	auto newSolutionI = new int[bpNumberI + 2];
	auto newSolutionJ = new int[bpNumberJ + 2];
	
				
	for(int i = 0; i <= bpNumberI + 1; i++)
	{
		oldSolutionI[i] = i * oldLocalHeight - 1;
		newSolutionI[i] = oldSolutionI[i];
	}

	for(int i = 0; i <= bpNumberJ + 1; i++)
	{
		oldSolutionJ[i] = i * oldLocalWidth - 1;
		newSolutionJ[i] = oldSolutionJ[i];
	}

	newSolutionJ[procJ]--;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	for(int i = 0; i < oldLocalHeight; i++)
	{
		assert(newMatrix[i * (oldLocalWidth + 1)] == -i - 1);

		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * (oldLocalWidth + 1) + j + 1]);
		}
	}
}