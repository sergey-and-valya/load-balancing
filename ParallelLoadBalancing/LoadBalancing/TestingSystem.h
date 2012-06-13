#ifndef _TESTINGSYSTEM_H
#define _TESTINGSYSTEM_H

#include "ITestingSystem.h"
#include "IInputFile.h"

class TestingSystem : public ITestingSystem
{
public:
	TestingSystem(IInputFile& inputFile, int steps);

	void LoadProblem(IMPICommunicator& comm, IProblemBuilder& builder);

	bool Run(
		IMPICommunicator& comm,
		int time_matrix[],
		const double matrix[],
		double new_matrix[],
		const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
		const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ);

private:
	double func(double **arr, bool **flag_arr, int global_i, int global_j);
	
	void CreateArr(const double matrix[], int col, double **arr, int i, int j);

	void CreateArrSide(
		IMPICommunicator& comm,
		int col,
		int row,
		int num_processor_col,
		int num_processor_row,
		const double matrix[],
		double** arr, 
		bool** flag_arr, 
		int i, int j, 
		double* top_row,						
		double* bottom_row,						
		double* left_column,					
		double* right_column,					
		double top_left_corner,					
		double top_right_corner,				
		double bottom_left_corner,				
		double bottom_right_corner
		);

	void Global_Sending(
		IMPICommunicator& comm,
		int col,
		int row,
		int num_processor_col,
		const double matrix[],
		double* top_row,						
		double* bottom_row,						
		double* left_column,					
		double* right_column,					
		double &top_left_corner,					
		double &top_right_corner,				
		double &bottom_left_corner,				
		double &bottom_right_corner);

private:
	IInputFile& inputFile;
	int steps;
	int step;
};

#endif