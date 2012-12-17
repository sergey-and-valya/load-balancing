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

#include "DomainModelTest.h"

#include <LoadBalancing/IDomainModel.h>
#include <LoadBalancing/IMPICommunicator.h>

#include "../DomainModel.h"
#include "../Utils.h"

#include "../SampleFunction.h"

#include "utils/MockMPIWorld.h"
#include "utils/MockCommunicator.h"
#include "utils/MockInputFile.h"
#include "utils/MockProblemBuilder.h"
#include "utils/Assert.h"

void DomainModelLoadTest()
{
	const char* filename = "matrix"; 
	FILE* file;
	fopen_s(&file, filename, "rb"); 

	//      7 8
	//      3 3
	//
	//      0 1 4 6
	//      0 1 4 7
	//
	//      5   6  | 7    11   100 | 200  305  40
	//      4   15 | 23   44   5   | 6    8    100
	//      ---------------------------------------
	//      1   0  | 156  346  67  | 5    46   55
	//      500 30 | 56   89   65  | 12   4    8
	//      3   45 | 67   78   888 | 567  16   900
	//      ---------------------------------------
	//      34  67 | 89   60   50  | 40   30   300
	//      67  56 | 44   23   45  | 78   60   90


	int bpNumberI = 2;
	int bpNumberJ = 2;
	
	int expectedSolutionI[] = {-1, 1, 4, 6};
	int expectedSolutionJ[] = {-1, 1, 4, 7};
	
	int mpiRank = 4;

	
	int steps = 10;

	int procI = mpiRank / (bpNumberI + 1);
	int procJ = mpiRank % (bpNumberJ + 1);
	
	int localWidth  = expectedSolutionJ[procJ + 1] - expectedSolutionJ[procJ];
	int localHeight = expectedSolutionI[procI + 1] - expectedSolutionI[procI];
	
	int expectedLocalMatrix[] = {
								 156,  346,  67,
								 56,   89,   65,
								 67,   78,   888
								};

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
	
	bool setBreakPointCountCalled = false;
	bool createSolutionICalled = false;
	bool createSolutionJCalled = false;
	bool createLocalMatrixCalled = false;
	
	int* solutionI = new int[bpNumberI + 2];
	int* solutionJ = new int[bpNumberJ + 2];
	double* localMatrix = new double[localWidth * localHeight];
	
	
	auto pb = MockProblemBuilder(
		[&setBreakPointCountCalled, bpNumberI, bpNumberJ](int actual_bpNumberI, int actual_bpNumberJ)
		{
			assert(!setBreakPointCountCalled);
			assert(bpNumberI == actual_bpNumberI);
			assert(bpNumberJ == actual_bpNumberJ);
			setBreakPointCountCalled = true;
		},
		[&setBreakPointCountCalled, &createSolutionICalled, solutionI]() -> int*
		{
			assert(setBreakPointCountCalled);
			assert(!createSolutionICalled);
			
			createSolutionICalled = true;
			return solutionI;
		},
		[&setBreakPointCountCalled, &createSolutionJCalled, solutionJ]() -> int*
		{
			assert(setBreakPointCountCalled);
			assert(!createSolutionJCalled);
			
			createSolutionJCalled = true;
			return solutionJ;
		},
		[&setBreakPointCountCalled, &createSolutionICalled, &createSolutionJCalled, &createLocalMatrixCalled, localMatrix]() -> double*
		{
			assert(createSolutionICalled);
			assert(createSolutionJCalled);
			assert(!createLocalMatrixCalled);

			createLocalMatrixCalled = true;
			return localMatrix;
		}
	);
	
	auto f = MockInputFile(
		[file](void *buffer, size_t elementSize, size_t count)
		{
			return fread(buffer, elementSize, count, file);
		},
		[file](long offset, int origin)
		{
			return fseek(file, offset, origin);
		}
	);

	SampleFunction func;
	auto dm = DomainModel(f, func, steps);
	
	dm.LoadProblem(comm, pb);
	
	for(int i = 0; i < bpNumberI + 1; i++)
	{
		assert(solutionI[i] == expectedSolutionI[i]);
	}
	
	for(int i = 0; i < bpNumberJ + 1; i++)
	{
		assert(solutionJ[i] == expectedSolutionJ[i]);
	}
	
	for(int i = 0; i < localHeight; i++)
	{
		for(int j = 0; j < localWidth; j++)
		{
			assert(expectedLocalMatrix[i * localWidth + j] == localMatrix[i * localWidth + j]);
		}
	}

	fclose(file);
}

void DomainModelStep()
{
	int steps = 1;

	double matrix[] = {
		5   , 6  , 7   , 11  , 100 , 200 , 305 , 40  ,
		4   , 99 , 23  , 44  , 5   , 6   , 8   , 100 ,
		1   , 0  , 156 , 346 , 67  , 5   , 46  , 55	 ,
		500 , 30 , 56  , 89  , 65  , 12  , 4   , 8	 ,
		3   , 45 , 67  , 78  , 888 , 567 , 16  , 900 ,
		34  , 67 , 89  , 60  , 50  , 40  , 30  , 300 ,
		67  , 56 , 44  , 23  , 45  , 78  , 60  , 90	 ,
	};
	
	int matrixWidth = 8;
	int matrixHeight = 7;

	double* newMatrix_A = new double[matrixWidth * matrixHeight];
	double* newMatrix_B = new double[matrixWidth * matrixHeight];
	
	// ������ A
	//  5    6  | 7    11   100 | 200  305  40
	//  4    15 | 23   44   5   | 6    8    100
	//  ----------------------------------------
	//  1    0  | 156  346  67  | 5    46   55
	//  500  30 | 56   89   65  | 12   4    8
	//  3    45 | 67   78   888 | 567  16   900
	//  ----------------------------------------
	//  34   67 | 89   60   50  | 40   30   300
	//  67   56 | 44   23   45  | 78   60   90
	

	int bpNumberI_A = 2;
	int bpNumberJ_A = 2;
	
	int solutionI_A[] = {-1, 1, 4, 6};
	int solutionJ_A[] = {-1, 1, 4, 7};
	
	

	
	// ������ B
	//  5   | 6   7   | 11   100  200 | 305  40
	//  4   | 15  23  | 44   5    6   | 8    100
	//  1   | 0   156 | 346  67   5   | 46   55
	//  -----------------------------------------
	//  500 | 30  56  | 89   65   12  | 4    8
	//  3   | 45  67  | 78   888  567 | 16   900
	//  34  | 67  89  | 60   50   40  | 30   300
	//  -----------------------------------------
	//  67  | 56  44  | 23   45   78  | 60   90
	
	int bpNumberI_B = 2;
	int bpNumberJ_B = 3;
				  
	int solutionI_B[] = {-1, 2, 5, 6};
	int solutionJ_B[] = {-1, 0, 2, 5, 7};

	auto run = [steps, matrixWidth, matrixHeight](int bpNumberI, int bpNumberJ, int* solutionI, int* solutionJ, double* matrix)
	{
		auto _matrixWidth  = matrixWidth;
		auto _matrixHeight = matrixHeight;

		int mpiCommSize = (bpNumberI + 1) * (bpNumberJ + 1);
		
		auto f = MockInputFile(
			[](void *buffer, size_t elementSize, size_t count) -> size_t
			{
				assert(false);
				return 0;
			},
			[](long offset, int origin) -> int
			{
				assert(false);
				return 0;
			}
		);
		
		auto _steps = steps;
		auto _f = f;

		MockMPIWorld world(mpiCommSize, [mpiCommSize, solutionI, solutionJ, bpNumberI, bpNumberJ, &_f, matrix, _matrixWidth, _matrixHeight, _steps](IMPICommunicator& comm)
		{
			SampleFunction func;
			auto dm = DomainModel(_f, func, _steps);
			int mpiRank;
			comm.Rank(&mpiRank);
				
			int procI = mpiRank / (bpNumberJ + 1);
			int procJ = mpiRank % (bpNumberJ + 1);

			for(int step = 0; step < _steps; step++)
			{
				int localWidth  = solutionJ[procJ + 1] - solutionJ[procJ];
				int localHeight = solutionI[procI + 1] - solutionI[procI];

				int* time_matrix = new int[localWidth * localHeight];
				double* local_matrix = new double[localWidth * localHeight];
				double* new_local_matrix = new double[localWidth * localHeight];
						
				int globalOffsetI = solutionI[procI] + 1;
				int globalOffsetJ = solutionJ[procJ] + 1;

				for(int i = 0; i < localHeight; i++)
				{
					for(int j = 0; j < localWidth; j++)
					{
						local_matrix[i * localWidth + j] = matrix[(globalOffsetI + i) * _matrixWidth + j + globalOffsetJ];
					}
				}

				bool shouldContinue = dm.Run(comm, time_matrix, local_matrix, new_local_matrix, solutionI, solutionJ, bpNumberI, bpNumberJ);
						
				if(step == _steps - 1)
				{
					assert(!shouldContinue);
				}
				else
				{
					assert(shouldContinue);
				}

				for(int i = 0; i < localHeight; i++)
				{
					for(int j = 0; j < localWidth; j++)
					{
						matrix[(globalOffsetI + i) * _matrixWidth + j + globalOffsetJ] = new_local_matrix[i * localWidth + j];
					}
				}

				free(time_matrix);
				free(local_matrix);
				free(new_local_matrix);
				
			}
		});

		world.RunAndWait();
	};

	memcpy(newMatrix_A, matrix, sizeof(double) * matrixWidth * matrixHeight);
	memcpy(newMatrix_B, matrix, sizeof(double) * matrixWidth * matrixHeight);

	run(bpNumberI_A, bpNumberJ_A, solutionI_A, solutionJ_A, newMatrix_A);
	run(bpNumberI_B, bpNumberJ_B, solutionI_B, solutionJ_B, newMatrix_B);
	
	for(int i = 0; i < matrixHeight; i++)
	{
		for(int j = 0; j < matrixWidth; j++)
		{
			assert(newMatrix_A[i * matrixWidth + j] == newMatrix_B[i * matrixWidth + j]);
		}
	}
}
