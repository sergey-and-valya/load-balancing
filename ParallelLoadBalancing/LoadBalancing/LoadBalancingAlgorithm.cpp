#include "LoadBalancingAlgorithm.h"

#include <memory.h>

LoadBalancingAlgorithm::LoadBalancingAlgorithm(int accuracy)
	: accuracy(accuracy)
{
}

void LoadBalancingAlgorithm::Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[])
{
	int processID = 0;
	MPI_Status status;
	int size;
	int *repVIb;
	repVIb = new int[accuracy - 1];
	int *repVIa;			    
	repVIa = new int[accuracy - 1];
	int *repVJa;			    
	repVJa = new int[accuracy - 1];
	int *repVJb;			    
	repVJb = new int[accuracy - 1];
	
	memset(repVIa, 0, sizeof(int) * (accuracy - 1));
	memset(repVIb, 0, sizeof(int) * (accuracy - 1));
	memset(repVJa, 0, sizeof(int) * (accuracy - 1));
	memset(repVJb, 0, sizeof(int) * (accuracy - 1));

	int sum = 0;
	comm.Rank(&processID);
	comm.Size(&size);

	if (processID == 0)
	{
		int **sumV = new int*[bpNumberI+1];
		for(int i = 0; i < bpNumberI + 1; i++)
			sumV[i] = new int[bpNumberJ + 1]; //- загруженность всех блоков

		int ***replacedVIAfter;
		int ***replacedVJAfter;
		int ***replacedVIBefore;
		int ***replacedVJBefore;

		replacedVIAfter = new int**[bpNumberI+2];
		for(int i = 0; i < bpNumberI+2; i++)
		{
			replacedVIAfter[i]=new int*[bpNumberJ+1];
			for(int j = 0; j < bpNumberJ+1; j++)
				replacedVIAfter[i][j]= new int[accuracy-1];
		}

		replacedVIBefore = new int**[bpNumberI+2]; 
		for(int i = 0; i < bpNumberI+2; i++)
		{
			replacedVIBefore[i]=new int*[bpNumberJ+1];
			for(int j = 0; j < bpNumberJ+1; j++)
				replacedVIBefore[i][j]= new int[accuracy-1];
		}

		replacedVJAfter = new int**[bpNumberJ+2]; 
		for(int i = 0; i < bpNumberJ+2; i++)
		{
			replacedVJAfter[i]=new int*[bpNumberI+1];
			for(int j = 0; j < bpNumberI+1; j++)
				replacedVJAfter[i][j]= new int[accuracy-1];
		}

		replacedVJBefore = new int**[bpNumberJ+2]; 
		for(int i = 0; i < bpNumberJ+2; i++)
		{
			replacedVJBefore[i]=new int*[bpNumberI+1];
			for(int j = 0; j < bpNumberI+1; j++)
				replacedVJBefore[i][j]= new int[accuracy-1];
		}

		int sizeI = oldSolutionI[1] - oldSolutionI[0];
		int sizeJ = oldSolutionJ[1] - oldSolutionJ[0];
		sum = 0;
		for (int i = 0; i < sizeI; i++)
			for (int j = 0; j < sizeJ; j++)
				sum += (int)time_matrix[i * sizeJ + j];
		sumV[0][0] = sum;

		int stepI = sizeI / accuracy;
		int stepJ = sizeJ / accuracy;
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < accuracy - 1; i++)
		{
			for(int j = i * stepI; j < (i + 1) * (stepI); j++)
				for(int k = 0; k < sizeJ; k++)
				{
					sum1 += (int)time_matrix[j * sizeJ + k];
					sum2 += (int)time_matrix[(sizeI - j) * sizeJ + k]; 
				}//расчет repVIb, repVJb, repVIa, repVJb
				repVIa[i] = sum1;
				repVIb[i] = sum2;
		}
		for (int i = 1; i < accuracy - 1; i++)
		{
			repVIa[i] += repVIa[i - 1];
			repVIb[i] += repVIb[i - 1];
		}

		for (int i = 0; i < accuracy - 1; i++)
		{
			for(int j = i * stepJ; j < (i + 1) * (stepJ); j++)
				for(int k = 0; k < sizeI; k++)
				{
					sum1 += (int)time_matrix[j * sizeI + k];
					sum2 += (int)time_matrix[(sizeJ-j) * sizeI + k];
				}
				repVJa[i] = sum1;
				repVJb[i] = sum2;
		}
		for (int i = 1; i < accuracy - 1; i++)
		{
			repVJa[i] += repVJa[i - 1];
			repVJb[i] += repVJb[i - 1];
		}
		replacedVIAfter[0][0] = repVIa;
		replacedVIBefore[1][0] = repVIb;
		replacedVJAfter[0][0] = repVJa;
		replacedVJBefore[1][0] = repVJb;

		// Receiving
		for(int i = 1; i < size; i++)
		{
			int  procI = i / (bpNumberJ + 1);
			int procJ = i % (bpNumberJ + 1);
			comm.Recv(&sum, 1, MPI_INT, i, 0, &status);
			sumV[procI][procJ] = sum;
			comm.Recv(repVIa, accuracy-1, MPI_INT, i, 0, &status);
			replacedVIAfter[procI][procJ];
			comm.Recv(repVIb, accuracy-1, MPI_INT, i, 0, &status);
			replacedVIBefore[procI+1][procJ];
			comm.Recv(repVJa, accuracy-1, MPI_INT, i, 0, &status);
			replacedVJAfter[procJ][procI];
			comm.Recv(repVJb, accuracy-1, MPI_INT, i, 0, &status);
			replacedVJBefore[procJ+1][procI];
		}

		// по строкам
		EvaluateSumV(bpNumberI,	bpNumberJ, oldSolutionI, &newSolutionI, replacedVIAfter, replacedVIBefore, sumV);

		// по столбцам
		EvaluateSumV(bpNumberJ,	bpNumberI, oldSolutionJ, &newSolutionJ, replacedVJAfter, replacedVJBefore, sumV);
		for(int i = 1; i < size; i++)
		{
			comm.Send(newSolutionI, bpNumberI + 2, MPI_INT, i, 0);
			comm.Send(newSolutionJ, bpNumberJ + 2, MPI_INT, i, 0);			
		}
	}
	else
	{
		int procI = processID / (bpNumberJ + 1);
		int procJ = processID % (bpNumberJ + 1);
		int sizeI = oldSolutionI[procI + 1] - oldSolutionI[procI];
		int sizeJ = oldSolutionJ[procJ + 1] - oldSolutionJ[procJ];
		int stepI=sizeI/accuracy;
		int stepJ=sizeJ/accuracy;
	
		for (int i = 0; i < accuracy - 1; i++)
		{
			int sum1 = 0; int sum2 = 0;
			for(int j = i * stepI; j < (i + 1) * (stepI); j++)
				for(int k = 0; k < sizeJ; k++)
				{
					sum1 += (int)time_matrix[j * sizeJ + k];
					sum2 += (int)time_matrix[(sizeI - j - 1) * sizeJ + k]; 
				}
				repVIa[i] = sum1;
				repVIb[i] = sum2;
		}
		for (int i = 1; i < accuracy - 1; i++)
		{
			repVIa[i] += repVIa[i - 1];
			repVIb[i] += repVIb[i - 1];
		}

		for (int i = 0; i < accuracy - 1; i++)
		{
			int sum1 = 0; int sum2 = 0;
			for(int j = i * stepJ; j < (i + 1) * (stepJ); j++)
				for(int k = 0; k < sizeI; k++)
				{
					sum1 += (int)time_matrix[j * sizeI + k];
					sum2 += (int)time_matrix[(sizeJ - j - 1) * sizeI + k]; 
				}
				repVJa[i] = sum1;
				repVJb[i] = sum2;
		}
		for (int i = 1; i < accuracy - 1; i++)
		{
			repVJa[i] += repVJa[i - 1];
			repVJb[i] += repVJb[i - 1];
		}
		

	  // Sending
		for (int i = 0; i < sizeI; i++)
			for (int j = 0; j < sizeJ; j++)
				sum += (int)time_matrix[i * sizeJ + j];

		comm.Send(&sum, 1, MPI_INT, 0, 0);
		comm.Send(repVIa, accuracy-1, MPI_INT, 0, 0);
		comm.Send(repVIb, accuracy-1, MPI_INT, 0, 0);
		comm.Send(repVJa, accuracy-1, MPI_INT, 0, 0);
		comm.Send(repVJb, accuracy-1, MPI_INT, 0, 0);
		comm.Recv(newSolutionI, bpNumberI + 2, MPI_INT, 0, 0, &status);
		comm.Recv(newSolutionJ, bpNumberJ + 2, MPI_INT, 0, 0, &status);
		return;
	}
}

void LoadBalancingAlgorithm::Init(
	int ***replacedVIAfter,
	int ***replacedVJAfter,
	int ***replacedVIBefore,
	int ***replacedVJBefore,
	int bpNumberI,
	int bpNumberJ)
{
	
}

void LoadBalancingAlgorithm::EvaluateSumV(
	int bpNumber1,
	int bpNumber2,
	const int oldSolution[],
	int *newSolution[],
	int ***replacedVAfter,
	int ***replacedVBefore,
	int **sumV)
{
	for(int i = 1; i <= bpNumber1; i++)
	{
		int sizebefore = oldSolution[i] - oldSolution[i - 1];
		int sizeafter = oldSolution[i+1] + oldSolution[i];
		int step=0;
		int maxbefore = 0, maxafter = 0;

		for(int j = 0; j < bpNumber2 + 1; j++)
		{
			if (sumV[i-1][j] > maxbefore)
				maxbefore = sumV[i-1][j]; 
			if (sumV[i][j] > maxafter)
				maxafter = sumV[i][j]; 
		}

		if(maxbefore > maxafter)
		{
			step = sizebefore / accuracy;
			if(step > 0)
			{
				int numSteps=0;
				for(int j=1; j < accuracy; j++)
				{
					int curMax=0;
					for(int k = 0; k<bpNumber2+1; k++)
					{
						if (sumV[i-1][k] - replacedVBefore[i][k][j] > curMax)
							curMax = sumV[i-1][k] - replacedVBefore[i][k][j]; 
						if (sumV[i][k] + replacedVBefore[i][k][j] > curMax)
							curMax = sumV[i][k] + replacedVBefore[i][k][j];
					}
					if(curMax < maxbefore)
					{
						maxbefore=curMax;
						numSteps=j;
					}
					else
						break;
				}
				newSolution[i] -= numSteps * step;
				for(int k = 0; k < bpNumber2 + 1; k++)
				{
					sumV[i - 1][k] -= replacedVBefore[i][k][numSteps]; 
					sumV[i][k] += replacedVBefore[i][k][numSteps];
				}
			}
		}

		if(maxafter > maxbefore) 
		{
			step = sizeafter / accuracy;
			if(step > 0)
			{
				int numSteps = 0;
				for(int j=1; j < accuracy; j++)
				{
					int curMax=0;
					for(int k = 0; k<bpNumber2+1; k++)
					{
						if (sumV[i-1][k] + replacedVAfter[i][k][j]> curMax)
							curMax = sumV[i-1][k] + replacedVAfter[i][k][j]; 
						if (sumV[i][k]- replacedVAfter[i][k][j] > curMax)
							curMax = sumV[i][k] - replacedVAfter[i][k][j];
					}
					if(curMax < maxafter)
					{
						maxafter=curMax;
						numSteps=j;
					}
					else
						break;
				}
				newSolution[i] += numSteps*step;
				for(int k = 0; k<bpNumber2+1; k++)
				{
					sumV[i-1][k] += replacedVAfter[i][k][numSteps]; 
					sumV[i][k] -= replacedVAfter[i][k][numSteps];
				}
			}
		}
	}
}