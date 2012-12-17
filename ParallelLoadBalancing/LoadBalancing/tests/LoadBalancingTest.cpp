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

#include "LoadBalancingTest.h"

#include "utils/Assert.h"
#include "utils/MockCommunicator.h"

#include <LoadBalancing/ILoadBalancingAlgorithm.h>
#include <LoadBalancing/IMPICommunicator.h>

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
			//assert(false);
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
	
	int accuracy = 4;

	int bpNumberI = 1;
	int bpNumberJ = 1;
	
	int receiveCalls = -1;

	auto comm = MockCommunicator(
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
		[accuracy](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			//assert(false);
			return MPI_SUCCESS;
		},
		[&receiveCalls, accuracy](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			assert(source == (receiveCalls / 5 + 1));
			assert(datatype == MPI_INT);
			
			switch (receiveCalls / 5 + 1)
			{
			case 1:
				{
					switch (receiveCalls % 5 + 1)
					{
					case 1:
						{
							assert(count == 1);
							*((int*)buf) = 4;
							return MPI_SUCCESS;
						}
					case 2:
						{
							assert(count == accuracy - 1);
							memset(buf, 0, sizeof(int) * (accuracy - 1));
							return MPI_SUCCESS;
						}
					case 3:
						{
							assert(count == accuracy - 1);
							memset(buf, 0, sizeof(int) * (accuracy - 1));
							return MPI_SUCCESS;
						}
					case 4:
						{
							assert(count == accuracy - 1);
							memset(buf, 0, sizeof(int) * (accuracy - 1));
							return MPI_SUCCESS;
						}
					case 5:
						{
							assert(count == accuracy - 1);
							memset(buf, 0, sizeof(int) * (accuracy - 1));
							return MPI_SUCCESS;
						}
					default:
						assert(false);
						return MPI_SUCCESS;
					}
				}
			case 2:
				{
					switch (receiveCalls % 5 + 1)
					{
					case 1:
						{
							assert(count == 1);
							*((int*)buf) = 16;
							return MPI_SUCCESS;
						}
					case 2:
						{
							assert(count == accuracy - 1);
							for(int i = 0; i < accuracy - 1; i++)
								((int*)buf)[i] = 4 * (i + 1);
							return MPI_SUCCESS;
						}
					case 3:
						{
							assert(count == accuracy - 1);
							for(int i = 0; i < accuracy - 1; i++)
								((int*)buf)[i] = 4 * (i + 1);
							return MPI_SUCCESS;
						}
					case 4:
						{
							assert(count == accuracy - 1);
							for(int i = 0; i < accuracy - 1; i++)
								((int*)buf)[i] = 4 * (i + 1);
							return MPI_SUCCESS;
						}
					case 5:
						{
							assert(count == accuracy - 1);
							for(int i = 0; i < accuracy - 1; i++)
								((int*)buf)[i] = 4 * (i + 1);
							return MPI_SUCCESS;
						}
					default:
						assert(false);
						return MPI_SUCCESS;
					}
					
				}
			case 3:
				{
					switch (receiveCalls % 5 + 1)
					{
					case 1:
						{
							assert(count == 1);
							*((int*)buf) = 8;
							return MPI_SUCCESS;
						}
					case 2:
						{
							assert(count == accuracy - 1);
							for(int i = 0; i < accuracy - 1; i++)
								((int*)buf)[i] = 2 * (i + 1);
							return MPI_SUCCESS;
						}
					case 3:
						{
							assert(count == accuracy - 1);
							for(int i = 0; i < accuracy - 1; i++)
								((int*)buf)[i] = 2 * (i + 1);
							return MPI_SUCCESS;
						}
					case 4:
						{
							assert(count == accuracy - 1);
							memset(buf, 0, sizeof(int) * (accuracy - 1));
							return MPI_SUCCESS;
						}
					case 5:
						{
							assert(count == accuracy - 1);
							memset(buf, 0, sizeof(int) * (accuracy - 1));
							return MPI_SUCCESS;
						}
					default:
						assert(false);
						return MPI_SUCCESS;
					}
					
				}
			default:
				{
					assert(false);
					return 0;
				}
			}
		}
	);

	auto lb = LoadBalancingAlgorithm(accuracy);
	
	auto time_matrix = new int[8];
	
	for(int i = 0; i < 8; i++)
		time_matrix[i] = 1;
	
	/*auto time_matrix = new int[20];
	
	for(int i = 0; i < 20; i++)
		time_matrix[i] = i;*/

	auto oldSolutionI = new int[3];
	auto oldSolutionJ = new int[3];	
	
	oldSolutionI[0] = -1;
	oldSolutionI[1] = 1;
	oldSolutionI[2] = 5;

	oldSolutionJ[0] = -1;
	oldSolutionJ[1] = 3;
	oldSolutionJ[2] = 5;
	/*oldSolutionI[0] = -1;
	oldSolutionI[1] = 3;
	oldSolutionI[2] = 5;

	oldSolutionJ[0] = -1;
	oldSolutionJ[1] = 4;
	oldSolutionJ[2] = 5;*/

	auto newSolutionI = new int[3];
	auto newSolutionJ = new int[3];

	newSolutionI[0] = -1;
	newSolutionI[1] = 1;
	newSolutionI[2] = 5;
	
	newSolutionJ[0] = -1;
	newSolutionJ[1] = 3;
	newSolutionJ[2] = 5;
	
	lb.Run(comm, time_matrix, oldSolutionI, oldSolutionJ, bpNumberI, bpNumberJ, newSolutionI, newSolutionJ);
	
	assert(newSolutionI[1] == 2 && newSolutionJ[1] == 2);
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
//	auto comm = MockCommunicator(
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
