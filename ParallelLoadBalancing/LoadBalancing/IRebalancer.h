#ifndef _IREBALANCER_H
#define _IREBALANCER_H

#include "IMPICommunicator.h"

class IRebalancer
{
public:
	virtual void Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ) = 0;
};

#endif