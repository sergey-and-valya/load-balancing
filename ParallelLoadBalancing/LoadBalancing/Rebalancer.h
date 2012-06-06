#ifndef _REBALANCER_H
#define _REBALANCER_H

#include "IRebalancer.h"

class Rebalancer : public IRebalancer
{
public:
	void Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ);
};

#endif