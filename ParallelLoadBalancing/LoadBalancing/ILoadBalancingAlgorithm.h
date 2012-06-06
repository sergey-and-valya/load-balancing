#ifndef _ILOADBALANCINGALGORITHM_H
#define _ILOADBALANCINGALGORITHM_H

#include "IMPICommunicator.h"

class ILoadBalancingAlgorithm
{
public:
	virtual void Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[]) = 0;
};

#endif