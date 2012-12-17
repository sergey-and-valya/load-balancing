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

#include "Rebalancer.h"
#include <LoadBalancing/IMPICommunicator.h>
#include <stdlib.h>
#include <memory.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

#define copy(x, i, y, j, size) memcpy(static_cast<char*>(x) + (i) * (size), static_cast<const char*>(y) + (j) * (size), (size))

void Rebalancer::Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const void* oldMatrix, const int newSolutionI[], const int newSolutionJ[], void* newMatrix, int bpNumberI, int bpNumberJ, MPI_Datatype datatype, size_t elementSize)
{
	MPI_Status status;

	int mpi_size;
	int mpi_rank;

	comm.Size(&mpi_size);
	comm.Rank(&mpi_rank);
	
	int procI = mpi_rank / (bpNumberJ + 1);
	int procJ = mpi_rank % (bpNumberJ + 1);
	
	int oldMatrixWidth  = oldSolutionJ[procJ + 1] - oldSolutionJ[procJ];
	int oldMatrixHeight = oldSolutionI[procI + 1] - oldSolutionI[procI];
	int newMatrixWidth  = newSolutionJ[procJ + 1] - newSolutionJ[procJ];
	int newMatrixHeight = newSolutionI[procI + 1] - newSolutionI[procI];
	
	int leftOffset = max(0, newSolutionJ[procJ] - oldSolutionJ[procJ]);
	int topOffset  = max(0, newSolutionI[procI] - oldSolutionI[procI]);
	int rightOffset  = oldMatrixWidth  - max(0, oldSolutionJ[procJ + 1] - newSolutionJ[procJ + 1]);
	int bottomOffset = oldMatrixHeight - max(0, oldSolutionI[procI + 1] - newSolutionI[procI + 1]);
	int newLeftOffset = max(0, oldSolutionJ[procJ] - newSolutionJ[procJ]);
	int newTopOffset  = max(0, oldSolutionI[procI] - newSolutionI[procI]);
	
	int copiedWidth  = rightOffset  - leftOffset;
	int copiedHeight = bottomOffset - topOffset;

	for(int i = 0; i < copiedHeight; i++)
	{
		for(int j = 0; j < copiedWidth; j++)
		{
			copy(
				newMatrix, (i + newTopOffset) * newMatrixWidth + j + newLeftOffset,
				oldMatrix, (i + topOffset) * oldMatrixWidth + j + leftOffset,
				elementSize);
		}
	}

	//horizontal exchange
	{
		if(procJ % 2 == 0)
		{
			goto exchange_left;
		}
		else
		{
			goto exchange_right;
		}

exchange_left:
		if(newSolutionJ[procJ] != oldSolutionJ[procJ])
		{
			int sendWidth = abs(newSolutionJ[procJ] - oldSolutionJ[procJ]);
			int sendCount = sendWidth * copiedHeight;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionJ[procJ] > oldSolutionJ[procJ])
			{
				for(int i = 0; i < copiedHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							tmp, i * sendWidth + j,
							oldMatrix, (i + topOffset) * oldMatrixWidth + j,
							elementSize);
					}
				}

				comm.Send(tmp, sendCount, datatype, mpi_rank - 1, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank - 1, 0, &status);
						
				for(int i = 0; i < copiedHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							newMatrix, (i + newTopOffset) * newMatrixWidth + j,
							tmp, i * sendWidth + j,
							elementSize);
					}
				}
			}

			free(tmp);
		}

		if(procJ % 2 == 0)
		{
			goto exchange_right;
		}
		else
		{
			goto end_horizontal_exchange;
		}

exchange_right:
		if(newSolutionJ[procJ + 1] != oldSolutionJ[procJ + 1])
		{
			int sendWidth = abs(newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]);
			int sendCount = sendWidth * copiedHeight;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionJ[procJ + 1] > oldSolutionJ[procJ + 1])
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank + 1, 0, &status);
						
				int offset = newMatrixWidth - sendWidth;

				for(int i = 0; i < copiedHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							newMatrix, (i + newTopOffset) * newMatrixWidth + j + offset,
							tmp, i * sendWidth + j,
							elementSize);
					}
				}
			}
			else
			{
				int offset = oldMatrixWidth - sendWidth;

				for(int i = 0; i < copiedHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							tmp, i * sendWidth + j,
							oldMatrix, (i + topOffset) * oldMatrixWidth + j + offset,
							elementSize);
					}
				}
						
				comm.Send(tmp, sendCount, datatype, mpi_rank + 1, 0);
			}

			free(tmp);
		}

		if(procJ % 2 == 0)
		{
			goto end_horizontal_exchange;
		}
		else
		{
			goto exchange_left;
		}

end_horizontal_exchange:;
	}
			
	//vertical exchange
	{
		if(procI % 2 == 0)
		{
			goto exchange_top;
		}
		else
		{
			goto exchange_bottom;
		}

exchange_top:
		if(newSolutionI[procI] != oldSolutionI[procI])
		{
			int sendHeight = abs(newSolutionI[procI] - oldSolutionI[procI]);
			int sendCount = sendHeight * copiedWidth;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionI[procI] > oldSolutionI[procI])
			{
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < copiedWidth; j++)
					{
						copy(
							tmp, i * copiedWidth + j,
							oldMatrix, i * oldMatrixWidth + j + leftOffset,
							elementSize);
					}
				}
						
				comm.Send(tmp, sendCount, datatype, mpi_rank - bpNumberJ - 1, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank - bpNumberJ - 1, 0, &status);
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < copiedWidth; j++)
					{
						copy(
							newMatrix, i * newMatrixWidth + j + newLeftOffset,
							tmp, i * copiedWidth + j,
							elementSize);
					}
				}
			}

			free(tmp);
		}

		if(procI % 2 == 0)
		{
			goto exchange_bottom;
		}
		else
		{
			goto end_vertical_exchange;
		}

exchange_bottom:
		if(newSolutionI[procI + 1] != oldSolutionI[procI + 1])
		{
			int sendHeight = abs(newSolutionI[procI + 1] - oldSolutionI[procI + 1]);
			int sendCount = sendHeight * copiedWidth;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionI[procI + 1] > oldSolutionI[procI + 1])
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank + bpNumberJ + 1, 0, &status);
						
				int offset = newMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < copiedWidth; j++)
					{
						copy(
							newMatrix, (i + offset) * newMatrixWidth + j + newLeftOffset,
							tmp, i * copiedWidth + j,
							elementSize);
					}
				}
			}
			else
			{
				int offset = oldMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < copiedWidth; j++)
					{
						copy(
							tmp, i * copiedWidth + j,
							oldMatrix, (i + offset) * oldMatrixWidth + j + leftOffset,
							elementSize);
					}
				}
						
				comm.Send(tmp, sendCount, datatype, mpi_rank + bpNumberJ + 1, 0);
			}

			free(tmp);
		}

		if(procI % 2 == 0)
		{
			goto end_vertical_exchange;
		}
		else
		{
			goto exchange_top;
		}

end_vertical_exchange:;
	}
			
			
	//left top - right bottom diagonal exchange
	{
		if(procJ % 2 == 0)
		{
			goto exchange_left_top;
		}
		else
		{
			goto exchange_right_bottom;
		}

exchange_left_top:
		if((newSolutionJ[procJ] - oldSolutionJ[procJ]) * (newSolutionI[procI] - oldSolutionI[procI]) > 0)
		{
			int sendWidth = abs(newSolutionJ[procJ] - oldSolutionJ[procJ]);
			int sendHeight = abs(newSolutionI[procI] - oldSolutionI[procI]);
			int sendCount = sendWidth * sendHeight;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionJ[procJ] > oldSolutionJ[procJ] && newSolutionI[procI] > oldSolutionI[procI])
			{
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							tmp, i * sendWidth + j,
							oldMatrix, i * oldMatrixWidth + j,
							elementSize);
					}
				}
						
				comm.Send(tmp, sendCount, datatype, mpi_rank - bpNumberJ - 2, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank - bpNumberJ - 2, 0, &status);

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							newMatrix, i * newMatrixWidth + j,
							tmp, i * sendWidth + j,
							elementSize);
					}
				}
			}
					
			free(tmp);
		}

		if(procJ % 2 == 0)
		{
			goto exchange_right_bottom;
		}
		else
		{
			goto end_lefttop_rightbottom_exchange;
		}

exchange_right_bottom:
		if((newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]) * (newSolutionI[procI + 1] - oldSolutionI[procI + 1]) > 0)
		{
			int sendWidth = abs(newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]);
			int sendHeight = abs(newSolutionI[procI + 1] - oldSolutionI[procI + 1]);
			int sendCount = sendWidth * sendHeight;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionJ[procJ + 1] < oldSolutionJ[procJ + 1] && newSolutionI[procI + 1] < oldSolutionI[procI + 1])
			{
				int offsetJ = oldMatrixWidth - sendWidth;
				int offsetI = oldMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							tmp, i * sendWidth + j,
							oldMatrix, (i + offsetI) * oldMatrixWidth + j + offsetJ,
							elementSize);
					}
				}
						
				comm.Send(tmp, sendCount, datatype, mpi_rank + bpNumberJ + 2, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank + bpNumberJ + 2, 0, &status);
						
				int offsetJ = newMatrixWidth - sendWidth;
				int offsetI = newMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							newMatrix, (i + offsetI) * newMatrixWidth + j + offsetJ,
							tmp, i * sendWidth + j,
							elementSize);
					}
				}
			}
					
			free(tmp);
		}

		if(procJ % 2 == 0)
		{
			goto end_lefttop_rightbottom_exchange;
		}
		else
		{
			goto exchange_left_top;
		}

end_lefttop_rightbottom_exchange:;
	}

			
	//right top - left bottom diagonal exchange
	{
		if(procJ % 2 == 0)
		{
			goto exchange_right_top;
		}
		else
		{
			goto exchange_left_bottom;
		}

exchange_right_top:
		if((newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]) * (newSolutionI[procI] - oldSolutionI[procI]) < 0)
		{
			int sendWidth = abs(newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]);
			int sendHeight = abs(newSolutionI[procI] - oldSolutionI[procI]);
			int sendCount = sendWidth * sendHeight;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionJ[procJ + 1] < oldSolutionJ[procJ + 1] && newSolutionI[procI] > oldSolutionI[procI])
			{
				int offsetJ = oldMatrixWidth - sendWidth;
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							tmp, i * sendWidth + j,
							oldMatrix, i * oldMatrixWidth + j + offsetJ,
							elementSize);
					}
				}
						
				comm.Send(tmp, sendCount, datatype, mpi_rank - bpNumberJ, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank - bpNumberJ, 0, &status);
						
				int offsetJ = newMatrixWidth - sendWidth;
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							newMatrix, i * newMatrixWidth + j + offsetJ,
							tmp, i * sendWidth + j,
							elementSize);
					}
				}
			}
					
			free(tmp);
		}

		if(procJ % 2 == 0)
		{
			goto exchange_left_bottom;
		}
		else
		{
			goto end_righttop_leftbottom_exchange;
		}

exchange_left_bottom:
		if((newSolutionJ[procJ] - oldSolutionJ[procJ]) * (newSolutionI[procI + 1] - oldSolutionI[procI + 1]) < 0)
		{
			int sendWidth = abs(newSolutionJ[procJ] - oldSolutionJ[procJ]);
			int sendHeight = abs(newSolutionI[procI + 1] - oldSolutionI[procI + 1]);
			int sendCount = sendWidth * sendHeight;
			void* tmp = malloc(elementSize * sendCount);

			if(newSolutionJ[procJ] > oldSolutionJ[procJ] && newSolutionI[procI + 1] < oldSolutionI[procI + 1])
			{
				int offsetI = oldMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							tmp, i * sendWidth + j,
							oldMatrix, (i + offsetI) * oldMatrixWidth + j,
							elementSize);
					}
				}
				comm.Send(tmp, sendCount, datatype, mpi_rank + bpNumberJ, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, datatype, mpi_rank + bpNumberJ, 0, &status);
						
				int offsetI = newMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						copy(
							newMatrix, (i + offsetI) * newMatrixWidth + j,
							tmp, i * sendWidth + j,
							elementSize);
					}
				}
			}
					
			free(tmp);
		}

		if(procJ % 2 == 0)
		{
			goto end_righttop_leftbottom_exchange;
		}
		else
		{
			goto exchange_right_top;
		}

end_righttop_leftbottom_exchange:;
	}
}
