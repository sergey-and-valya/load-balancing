#ifndef _ITESTINGSYSTEM_H
#define _ITESTINGSYSTEM_H

#include "IMPICommunicator.h"
#include "IProblemBuilder.h"

class IProblemBuilder;

class ITestingSystem
{
public:
	virtual void LoadProblem(IMPICommunicator& comm, IProblemBuilder& builder) = 0;

	virtual bool Run(
		IMPICommunicator& comm,
		int time_matrix[],
		const double matrix[],
		double new_matrix[],
		const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
		const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ) = 0;
};

#endif