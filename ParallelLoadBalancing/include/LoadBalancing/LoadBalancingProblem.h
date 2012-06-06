#ifndef _LOADBALANCINGPROBLEM_H
#define _LOADBALANCINGPROBLEM_H

#include <Core/IMatrix.h>

class LoadBalancingProblem
{
public:
	virtual std::shared_ptr<IMatrix<double>> Data() const = 0;
	virtual void SetData(std::shared_ptr<IMatrix<double>> data) = 0;

	virtual std::shared_ptr<IMatrix<double>> V() const = 0;
	virtual void SetV(std::shared_ptr<IMatrix<double>> data) = 0;
};

#endif // _LOADBALANCINGPROBLEM_H