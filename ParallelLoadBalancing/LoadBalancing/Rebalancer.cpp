#include "Rebalancer.h"
#include "IMPICommunicator.h"
#include <stdlib.h>
#include <memory.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

void Rebalancer::Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ)
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
	int newTopOffset = max(0, oldSolutionI[procI] - newSolutionI[procI]);
	
	int copiedWidth  = rightOffset  - leftOffset;
	int copiedHeight = bottomOffset - topOffset;

	for(int i = 0; i < copiedHeight; i++)
	{
		for(int j = 0; j < copiedWidth; j++)
		{
			newMatrix[(i + newTopOffset) * newMatrixWidth + j + newLeftOffset] = oldMatrix[(i + topOffset) * oldMatrixWidth + j + leftOffset];
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
			int sendHeight = bottomOffset - topOffset;
			int sendCount = sendWidth * sendHeight;
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionJ[procJ] > oldSolutionJ[procJ])
			{
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[(i + topOffset) * oldMatrixWidth + j];
					}
				}

				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank - 1, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank - 1, 0, &status);
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[(i + newTopOffset) * newMatrixWidth + j] = tmp[i * sendWidth + j];
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
			int sendHeight = bottomOffset - topOffset;
			int sendCount = sendWidth * sendHeight;
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionJ[procJ + 1] > oldSolutionJ[procJ + 1])
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank + 1, 0, &status);
						
				int offset = newMatrixWidth - sendWidth;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[(i + newTopOffset) * newMatrixWidth + j + offset] = tmp[i * sendWidth + j];
					}
				}
			}
			else
			{
				int offset = oldMatrixWidth - sendWidth;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[(i + topOffset) * oldMatrixWidth + j + offset];
					}
				}
						
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank + 1, 0);
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
			int sendWidth = rightOffset - leftOffset;
			int sendCount = sendHeight * sendWidth;
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionI[procI] > oldSolutionI[procI])
			{
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[i * oldMatrixWidth + j + leftOffset];
					}
				}
						
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank - bpNumberJ - 1, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank - bpNumberJ - 1, 0, &status);
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[i * newMatrixWidth + j + newLeftOffset] = tmp[i * sendWidth + j];
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
			int sendWidth = rightOffset - leftOffset;
			int sendCount = sendHeight * sendWidth;
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionI[procI + 1] > oldSolutionI[procI + 1])
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank + bpNumberJ + 1, 0, &status);
						
				int offset = newMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[(i + offset) * newMatrixWidth + j + newLeftOffset] = tmp[i * sendWidth + j];
					}
				}
			}
			else
			{
				int offset = oldMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[(i + offset) * oldMatrixWidth + j + leftOffset];
					}
				}
						
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank + bpNumberJ + 1, 0);
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
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionJ[procJ] > oldSolutionJ[procJ] && newSolutionI[procI] > oldSolutionI[procI])
			{
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[i * oldMatrixWidth + j];
					}
				}
						
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank - bpNumberJ - 2, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank - bpNumberJ - 2, 0, &status);

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[i * newMatrixWidth + j] = tmp[i * sendWidth + j];
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
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionJ[procJ + 1] > oldSolutionJ[procJ + 1] && newSolutionI[procI + 1] > oldSolutionI[procI + 1])
			{
				int offsetJ = oldMatrixWidth - sendWidth;
				int offsetI = oldMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[(i + offsetI) * oldMatrixWidth + j + offsetJ];
					}
				}
						
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank + bpNumberJ + 2, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank + bpNumberJ + 2, 0, &status);
						
				int offsetJ = newMatrixWidth - sendWidth;
				int offsetI = newMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[(i + offsetI) * newMatrixWidth + j + offsetJ] = tmp[i * sendWidth + j];
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
		if((newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]) * (newSolutionI[procI] - oldSolutionI[procI]) > 0)
		{
			int sendWidth = abs(newSolutionJ[procJ + 1] - oldSolutionJ[procJ + 1]);
			int sendHeight = abs(newSolutionI[procI] - oldSolutionI[procI]);
			int sendCount = sendWidth * sendHeight;
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionJ[procJ + 1] > oldSolutionJ[procJ + 1] && newSolutionI[procI] > oldSolutionI[procI])
			{
				int offsetJ = oldMatrixWidth - sendWidth;
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[i * oldMatrixWidth + j + offsetJ];
					}
				}
						
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank - bpNumberJ, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank - bpNumberJ, 0, &status);
						
				int offsetJ = newMatrixWidth - sendWidth;
						
				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[i * newMatrixWidth + j + offsetJ] = tmp[i * sendWidth + j];
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
		if((newSolutionJ[procJ] - oldSolutionJ[procJ]) * (newSolutionI[procI + 1] - oldSolutionI[procI + 1]) > 0)
		{
			int sendWidth = abs(newSolutionJ[procJ] - oldSolutionJ[procJ]);
			int sendHeight = abs(newSolutionI[procI + 1] - oldSolutionI[procI + 1]);
			int sendCount = sendWidth * sendHeight;
			double* tmp = (double*)malloc(sizeof(double) * sendCount);

			if(newSolutionJ[procJ] > oldSolutionJ[procJ] && newSolutionI[procI + 1] > oldSolutionI[procI + 1])
			{
				int offsetI = oldMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						tmp[i * sendWidth + j] = oldMatrix[(i + offsetI) * oldMatrixWidth + j];
					}
				}
				comm.Send(tmp, sendCount, MPI_DOUBLE, mpi_rank + bpNumberJ, 0);
			}
			else
			{
				comm.Recv(tmp, sendCount, MPI_DOUBLE, mpi_rank + bpNumberJ, 0, &status);
						
				int offsetI = newMatrixHeight - sendHeight;

				for(int i = 0; i < sendHeight; i++)
				{
					for(int j = 0; j < sendWidth; j++)
					{
						newMatrix[(i + offsetI) * newMatrixWidth + j] = tmp[i * sendWidth + j];
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