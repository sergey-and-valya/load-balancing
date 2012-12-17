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

#include "RebalancerTest.h"

#include "utils/Assert.h"
#include "utils/MockCommunicator.h"

#include <LoadBalancing/IRebalancer.h>
#include <LoadBalancing/IMPICommunicator.h>

#include "../Rebalancer.h"

void RebalancerNoMoveTest()
{
	auto rb = Rebalancer();

	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;

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

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}


void RebalancerMoveFromLeftTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaWidth = 2;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int receiveCalls = 0;

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
			return 0;
		},
		[oldLocalHeight, deltaWidth, mpiRank, &receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			switch(receiveCalls)
			{
			case 1:
				{
					assert(source == mpiRank - 1);
					assert(count == oldLocalHeight * deltaWidth);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i;
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
	
	auto newMatrix = new double[(oldLocalWidth + deltaWidth) * oldLocalHeight];
	
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

	newSolutionJ[procJ] -= deltaWidth;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(receiveCalls == 1);

	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < deltaWidth; j++)
		{
			assert(newMatrix[i * (oldLocalWidth + deltaWidth) + j] == -1 - (deltaWidth * i + j));
		}

		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * (oldLocalWidth + deltaWidth) + j + deltaWidth]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}

void RebalancerMoveFromRightTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaWidth = 2;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int receiveCalls = 0;

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
			return 0;
		},
		[oldLocalHeight, deltaWidth, mpiRank, &receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			switch(receiveCalls)
			{
			case 1:
				{
					assert(source == mpiRank + 1);
					assert(count == oldLocalHeight * deltaWidth);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i;
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
	
	auto newMatrix = new double[(oldLocalWidth + deltaWidth) * oldLocalHeight];
	
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

	newSolutionJ[procJ + 1] += deltaWidth;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(receiveCalls == 1);

	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * (oldLocalWidth + deltaWidth) + j]);
		}
		
		for(int j = 0; j < deltaWidth; j++)
		{
			assert(newMatrix[i * (oldLocalWidth + deltaWidth) + j + oldLocalWidth] == -1 - (deltaWidth * i + j));
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}

void RebalancerMoveFromTopTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaHeight = 2;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int receiveCalls = 0;

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
			return 0;
		},
		[oldLocalWidth, deltaHeight, bpNumberJ, mpiRank, &receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			switch(receiveCalls)
			{
			case 1:
				{
					assert(source == mpiRank - (bpNumberJ + 1));
					assert(count == oldLocalWidth * deltaHeight);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i;
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
	
	auto newMatrix = new double[oldLocalWidth * (oldLocalHeight + deltaHeight)];
	
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

	newSolutionI[procI] -= deltaHeight;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(receiveCalls == 1);
	
	for(int j = 0; j < oldLocalWidth; j++)
	{
		for(int i = 0; i < deltaHeight; i++)
		{
			assert(newMatrix[i * oldLocalWidth + j] == -1 - (oldLocalWidth * i + j));
		}

		for(int i = 0; i < oldLocalHeight; i++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[(i + deltaHeight) * oldLocalWidth + j]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}

void RebalancerMoveFromBottomTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaHeight = 2;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int receiveCalls = 0;

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
			return 0;
		},
		[oldLocalWidth, deltaHeight, bpNumberJ, mpiRank, &receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			switch(receiveCalls)
			{
			case 1:
				{
					assert(source == mpiRank + (bpNumberJ + 1));
					assert(count == oldLocalWidth * deltaHeight);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i;
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
	
	auto newMatrix = new double[oldLocalWidth * (oldLocalHeight + deltaHeight)];
	
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

	newSolutionI[procI + 1] += deltaHeight;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(receiveCalls == 1);
	
	for(int j = 0; j < oldLocalWidth; j++)
	{
		for(int i = 0; i < oldLocalHeight; i++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * oldLocalWidth + j]);
		}
		
		for(int i = 0; i < deltaHeight; i++)
		{
			assert(newMatrix[(i + oldLocalHeight) * oldLocalWidth + j] == -1 - (oldLocalWidth * i + j));
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}


void RebalancerMoveToLeftTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaWidth = 2;

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
		[oldLocalHeight, oldLocalWidth, deltaWidth, mpiRank, &sendCalls](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			sendCalls++;

			switch(sendCalls)
			{
			case 1:
				{
					assert(dest == mpiRank - 1);
					assert(count == oldLocalHeight * deltaWidth);
					assert(datatype == MPI_DOUBLE);

					const double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						assert(doublebuf[i] == i / deltaWidth * oldLocalWidth + i % deltaWidth);
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
	
	auto newMatrix = new double[(oldLocalWidth - deltaWidth) * oldLocalHeight];
	
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

	newSolutionJ[procJ] += deltaWidth;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(sendCalls == 1);

	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth - deltaWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j + deltaWidth] == newMatrix[i * (oldLocalWidth - deltaWidth) + j]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}

void RebalancerMoveToRightTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaWidth = 2;

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
		[oldLocalHeight, oldLocalWidth, deltaWidth, mpiRank, &sendCalls](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			sendCalls++;

			switch(sendCalls)
			{
			case 1:
				{
					assert(dest == mpiRank + 1);
					assert(count == oldLocalHeight * deltaWidth);
					assert(datatype == MPI_DOUBLE);

					const double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						assert(doublebuf[i] == i / deltaWidth * oldLocalWidth + i % deltaWidth + oldLocalWidth - deltaWidth);
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
	
	auto newMatrix = new double[(oldLocalWidth - deltaWidth) * oldLocalHeight];
	
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

	newSolutionJ[procJ + 1] -= deltaWidth;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(sendCalls == 1);

	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth - deltaWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * (oldLocalWidth - deltaWidth) + j]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}

void RebalancerMoveToTopTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaHeight = 2;

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
		[oldLocalHeight, oldLocalWidth, deltaHeight, bpNumberJ, mpiRank, &sendCalls](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			sendCalls++;

			switch(sendCalls)
			{
			case 1:
				{
					assert(dest == mpiRank - (bpNumberJ + 1));
					assert(count == oldLocalWidth * deltaHeight);
					assert(datatype == MPI_DOUBLE);

					const double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						assert(doublebuf[i] == i);
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
	
	auto newMatrix = new double[oldLocalWidth * (oldLocalHeight - deltaHeight)];
	
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

	newSolutionI[procI] += deltaHeight;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(sendCalls == 1);

	for(int i = 0; i < oldLocalHeight - deltaHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(oldMatrix[(i + deltaHeight) * oldLocalWidth + j] == newMatrix[i * oldLocalWidth + j]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}

void RebalancerMoveToBottomTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaHeight = 2;

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
		[oldLocalHeight, oldLocalWidth, deltaHeight, bpNumberJ, mpiRank, &sendCalls](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			sendCalls++;

			switch(sendCalls)
			{
			case 1:
				{
					assert(dest == mpiRank + (bpNumberJ + 1));
					assert(count == oldLocalWidth * deltaHeight);
					assert(datatype == MPI_DOUBLE);

					const double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						assert(doublebuf[i] == i + (oldLocalHeight - deltaHeight) * oldLocalWidth);
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
	
	auto newMatrix = new double[oldLocalWidth * (oldLocalHeight - deltaHeight)];
	
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

	newSolutionI[procI + 1] -= deltaHeight;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(sendCalls == 1);

	for(int i = 0; i < oldLocalHeight - deltaHeight; i++)
	{
		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(oldMatrix[i * oldLocalWidth + j] == newMatrix[i * oldLocalWidth + j]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}


void RebalancerMoveFromLeftFromTopTest()
{
	auto rb = Rebalancer();
	
	int oldLocalWidth  = 100;
	int oldLocalHeight = 200;
	
	int bpNumberI = 10;
	int bpNumberJ = 5;

	int mpiRank = 10;
	
	int deltaWidth = 2;
	int deltaHeight = 3;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	int receiveCalls = 0;

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
			return 0;
		},
		[oldLocalHeight, oldLocalWidth, deltaWidth, deltaHeight, bpNumberJ, mpiRank, &receiveCalls](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			receiveCalls++;

			switch(receiveCalls)
			{
			case 1:
				{
					assert(source == mpiRank - 1);
					assert(count == oldLocalHeight * deltaWidth);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i;
					}

					return MPI_SUCCESS;

					break;
				}
			case 2:
				{
					assert(source == mpiRank - (bpNumberJ + 1));
					assert(count == oldLocalWidth * deltaHeight);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i - oldLocalHeight * deltaWidth;
					}

					return MPI_SUCCESS;

					break;
				}
			case 3:
				{
					assert(source == mpiRank - (bpNumberJ + 1) - 1);
					assert(count == deltaWidth * deltaHeight);
					assert(datatype == MPI_DOUBLE);

					double* doublebuf = (double*)buf;
					for(int i = 0; i < count; i++)
					{
						doublebuf[i] = -1 - i - oldLocalHeight * deltaWidth - oldLocalWidth * deltaHeight;
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
	
	auto newMatrix = new double[(oldLocalWidth + deltaWidth) * (oldLocalHeight + deltaHeight)];
	
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
	
	newSolutionJ[procJ] -= deltaWidth;
	newSolutionI[procI] -= deltaHeight;
	
	rb.Rebalance(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	
	assert(receiveCalls == 3);
	
	for(int i = 0; i < deltaHeight; i++)
	{
		for(int j = 0; j < deltaWidth; j++)
		{
			assert(newMatrix[i * (oldLocalWidth + deltaWidth) + j] == -1 - i * deltaWidth - j - oldLocalHeight * deltaWidth - oldLocalWidth * deltaHeight);
		}

		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(newMatrix[i * (oldLocalWidth + deltaWidth) + j + deltaWidth] == -1 - i * oldLocalWidth - j - oldLocalHeight * deltaWidth);
		}
	}

	for(int i = 0; i < oldLocalHeight; i++)
	{
		for(int j = 0; j < deltaWidth; j++)
		{
			assert(newMatrix[(i + deltaHeight) * (oldLocalWidth + deltaWidth) + j] == -1 - (deltaWidth * i + j));
		}

		for(int j = 0; j < oldLocalWidth; j++)
		{
			assert(newMatrix[(i + deltaHeight) * (oldLocalWidth + deltaWidth) + j + deltaWidth] == oldMatrix[i * oldLocalWidth + j]);
		}
	}

	delete[] oldMatrix;
	delete[] newMatrix;
	delete[] oldSolutionI;
	delete[] oldSolutionJ;
	delete[] newSolutionI;
	delete[] newSolutionJ;
}
