#ifndef _LOADBALANCINGALGORITHM_H
#define _LOADBALANCINGALGORITHM_H

#include "ILoadBalancingAlgorithm.h"

class LoadBalancingAlgorithm : public ILoadBalancingAlgorithm
{
public:
	LoadBalancingAlgorithm(int accuracy);

	void Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[]);

	int accuracy;
};

#endif