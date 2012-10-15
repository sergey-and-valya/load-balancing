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

#ifndef _TESTINGSYSTEM_H
#define _TESTINGSYSTEM_H

#include <LoadBalancing/IDomainModel.h>
#include <LoadBalancing/IInputFile.h>
#include <LoadBalancing/IFunction.h>

class DomainModel : public IDomainModel
{
public:
	DomainModel(IInputFile& inputFile, IFunction& func, int steps);

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
	void CreateArrSide(
		IMPICommunicator& comm,
		int col,
		int row,
		int num_processor_col,
		int num_processor_row,
		const double matrix[],
		Values* values,
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
	IFunction& func;
	int steps;
	int step;
};

#endif
