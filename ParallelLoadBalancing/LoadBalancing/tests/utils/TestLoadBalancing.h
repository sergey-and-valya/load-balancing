#ifndef _TESTLOADBALANCING_H
#define _TESTLOADBALANCING_H

#include "../../ILoadBalancingAlgorithm.h"
#include <functional>

class TestLoadBalancing : public ILoadBalancingAlgorithm
{
public:
	typedef std::function<void(IMPICommunicator&, const int[], const int[], const int[], int, int, int[], int[])> RunFunction;

	TestLoadBalancing(RunFunction runImpl)
		: m_runImpl(runImpl)
	{
	}

	void Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[])
	{
		m_runImpl(comm, time_matrix, oldSolutionI, oldSolutionJ, bpNumberI, bpNumberJ, newSolutionI, newSolutionJ);
	}

private:
	RunFunction m_runImpl;
};

#endif