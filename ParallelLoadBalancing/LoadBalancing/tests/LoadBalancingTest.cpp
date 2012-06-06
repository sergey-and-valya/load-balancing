#include "LoadBalancingTest.h"

#include "utils/Assert.h"
#include "utils/TestCommunicator.h"

#include "../ILoadBalancingAlgorithm.h"
#include "../IMPICommunicator.h"

#include "../LoadBalancingAlgorithm.h"

#include <stdlib.h>

void LoadBalancingTest()
{
	int localWidth  = 100;
	int localHeight = 200;
	int accuracy = 5;

	int bpNumberI = 10;
	int bpNumberJ = 5;
	int mpiRank = 10;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int sendCalls = 0;

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
		[&sendCalls, localWidth, localHeight, accuracy](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			sendCalls++;

			switch(sendCalls)
			{
			case 1:
				{
					assert(count == 1);
					assert(*((int*)buf) == localWidth * localHeight / 2);
					assert(dest == 0);
					assert(datatype == MPI_INT);
			
					return MPI_SUCCESS;
				}
				break;
			case 2:
				{
					assert(dest == 0);
					assert(datatype == MPI_INT);
					assert(count == accuracy - 1);

					int* intbuf = (int*)buf;

					for(int i = 0; i < accuracy - 1; i++)
					{
						assert(intbuf[i] == 2000 * (i + 1));
					}

					return MPI_SUCCESS;
				}
				break;
			case 3:
				{
					assert(dest == 0);
					assert(datatype == MPI_INT);
					assert(count == accuracy - 1);

					int* intbuf = (int*)buf;

					for(int i = 0; i < accuracy - 1; i++)
					{
						assert(intbuf[i] == 2000 * (i + 1));
					}

					return MPI_SUCCESS;
				}
				break;
			case 4:
				{
					assert(dest == 0);
					assert(datatype == MPI_INT);
					assert(count == accuracy - 1);

					int* intbuf = (int*)buf;

					for(int i = 0; i < accuracy - 1; i++)
					{
						assert(intbuf[i] == 2000 * (i + 1));
					}

					return MPI_SUCCESS;
				}
			case 5:
				{
					assert(dest == 0);
					assert(datatype == MPI_INT);
					assert(count == accuracy - 1);

					int* intbuf = (int*)buf;

					for(int i = 0; i < accuracy - 1; i++)
					{
						assert(intbuf[i] == 2000 * (i + 1));
					}

					return MPI_SUCCESS;
				}
			default:
				{
					assert(false);
					return 0;
				}
			}
		},
		[](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			assert(false);
			return MPI_SUCCESS;
		}
	);

	auto lb = LoadBalancingAlgorithm(accuracy);
	
	auto time_matrix = new int[localWidth * localHeight];
	
	for(int i = 0; i < localWidth; i++)
	{
		for(int j = 0; j < localHeight; j++)
		{
			time_matrix[i * localHeight + j] = i % 2;
		}
	}

	auto oldSolutionI = new int[bpNumberI + 2];
	auto oldSolutionJ = new int[bpNumberJ + 2];
	
				
	for(int i = 0; i <= bpNumberI + 1; i++)
	{
		oldSolutionI[i] = i * localHeight - 1;
	}
			
	for(int i = 0; i <= bpNumberJ + 1; i++)
	{
		oldSolutionJ[i] = i * localWidth - 1;
	}

	auto newSolutionI = new int[bpNumberI + 2];
	auto newSolutionJ = new int[bpNumberJ + 2];
	
	lb.Run(comm, time_matrix, oldSolutionI, oldSolutionJ, bpNumberI, bpNumberJ, newSolutionI, newSolutionJ);
}

void LoadBalancingCentralTest()
{
	
	int accuracy = 5;

	int bpNumberI = 10;
	int bpNumberJ = 5;
	
	int receiveCalls = 0;

	auto comm = TestCommunicator(
		[bpNumberI, bpNumberJ](int* size) -> int
		{
			*size = (bpNumberI + 1) * (bpNumberJ + 1);
			return MPI_SUCCESS;
		},
		[](int* rank) -> int
		{
			*rank = 0;
			return MPI_SUCCESS;
		},
		[localWidth, localHeight, accuracy](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			assert(false);
		},
		[&receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			
			assert(source == (receiveCalls / 5 + 1));
			assert(datatype == MPI_INT);

			
			switch(receiveCalls % 5)
			{
			case 0:
				{
					switch(receiveCalls/5 + 1)
					{
					case 1:
						{
							
						}
					}
					assert(count == 1);
					return MPI_SUCCESS;
				}
			default:
				{
					assert(false);
					return 0;
				}
			}
			receiveCalls++;
		}
	);

	auto lb = LoadBalancingAlgorithm(accuracy);
	
	auto time_matrix = new int[localWidth * localHeight];
	
	for(int i = 0; i < localWidth; i++)
	{
		for(int j = 0; j < localHeight; j++)
		{
			time_matrix[i * localHeight + j] = i % 2;
		}
	}

	auto oldSolutionI = new int[bpNumberI + 2];
	auto oldSolutionJ = new int[bpNumberJ + 2];
	
				
	for(int i = 0; i <= bpNumberI + 1; i++)
	{
		oldSolutionI[i] = i * localHeight - 1;
	}

	for(int i = 0; i <= bpNumberJ + 1; i++)
	{
		oldSolutionJ[i] = i * localWidth - 1;
	}

	auto newSolutionI = new int[bpNumberI + 2];
	auto newSolutionJ = new int[bpNumberJ + 2];
	
	lb.Run(comm, time_matrix, oldSolutionI, oldSolutionJ, bpNumberI, bpNumberJ, newSolutionI, newSolutionJ);
}



//void LoadBalancingCentralTest()
//{
//	int localWidth  = 100;
//	int localHeight = 200;
//	int accuracy = 5;
//
//	int bpNumberI = 10;
//	int bpNumberJ = 5;
//	
//	int receiveCalls = 0;
//
//	auto comm = TestCommunicator(
//		[bpNumberI, bpNumberJ](int* size) -> int
//		{
//			*size = (bpNumberI + 1) * (bpNumberJ + 1);
//			return MPI_SUCCESS;
//		},
//		[](int* rank) -> int
//		{
//			*rank = 0;
//			return MPI_SUCCESS;
//		},
//		[localWidth, localHeight, accuracy](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
//		{
//			assert(false);
//		},
//		[&receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
//		{
//			
//			assert(source == (receiveCalls / 5 + 1));
//			assert(datatype == MPI_INT);
//
//			
//			switch(receiveCalls % 5)
//			{
//			case 0:
//				{
//					assert(count == 1);
//					return MPI_SUCCESS;
//				}
//			default:
//				{
//					assert(false);
//					return 0;
//				}
//			}
//			receiveCalls++;
//		}
//	);
//
//	auto lb = LoadBalancingAlgorithm(accuracy);
//	
//	auto time_matrix = new int[localWidth * localHeight];
//	
//	for(int i = 0; i < localWidth; i++)
//	{
//		for(int j = 0; j < localHeight; j++)
//		{
//			time_matrix[i * localHeight + j] = i % 2;
//		}
//	}
//
//	auto oldSolutionI = new int[bpNumberI + 2];
//	auto oldSolutionJ = new int[bpNumberJ + 2];
//	
//				
//	for(int i = 0; i <= bpNumberI + 1; i++)
//	{
//		oldSolutionI[i] = i * localHeight - 1;
//	}
//
//	for(int i = 0; i <= bpNumberJ + 1; i++)
//	{
//		oldSolutionJ[i] = i * localWidth - 1;
//	}
//
//	auto newSolutionI = new int[bpNumberI + 2];
//	auto newSolutionJ = new int[bpNumberJ + 2];
//	
//	lb.Run(comm, time_matrix, oldSolutionI, oldSolutionJ, bpNumberI, bpNumberJ, newSolutionI, newSolutionJ);
//}
