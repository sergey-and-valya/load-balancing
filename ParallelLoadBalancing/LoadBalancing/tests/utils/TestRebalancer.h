#ifndef _TESTREBALANCER_H
#define _TESTREBALANCER_H

#include "../IRebalancer.h"
#include <functional>

class TestRebalancer : public IRebalancer
{
public:
	typedef std::function<void(IMPICommunicator&, const int[], const int[], const double[], const int[], const int[], double[], int, int)> RebalanceFunction;

	TestRebalancer(RebalanceFunction rebalanceImpl)
		: m_rebalanceImpl(rebalanceImpl)
	{
	}

	void Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ)
	{
		m_rebalanceImpl(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	}

private:
	RebalanceFunction m_rebalanceImpl;
};

#endif