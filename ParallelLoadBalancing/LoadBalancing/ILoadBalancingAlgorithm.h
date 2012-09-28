#ifndef _ILOADBALANCINGALGORITHM_H
#define _ILOADBALANCINGALGORITHM_H

#include "IMPICommunicator.h"

/**
 * \class   ILoadBalancingAlgorithm
 *
 * \brief   Load balancing algorithm interface.
 *          Makes a decision how should current data be rebalanced among processors.
 */

class ILoadBalancingAlgorithm
{
public:

    /**
     * \fn  virtual void ILoadBalancingAlgorithm::Run( IMPICommunicator& comm,
     *      const int time_matrix[], const int oldSolutionI[], const int oldSolutionJ[],
     *      int bpNumberI, int bpNumberJ, int newSolutionI[], int newSolutionJ[]) = 0;
     *
     * \brief   Runs load balancing algorithm.
     *          Makes a decision how should current data be rebalanced among processors depending on the time matrix.
     *
     * \param [in]   comm          The communicator.
     * \param [in]   time_matrix   The time matrix.
     * \param [in]   oldSolutionI  The old solution by rows. Should have \a bpNumberI + 2 elements. \a solutionI[0] = -1, \a solutionI[\a bpNumberI + 1] = \a rows - 1
     * \param [in]   oldSolutionJ  The old solution by columns. Should have \a bpNumberJ + 2 elements. \a solutionJ[0] = -1, \a solutionJ[\a bpNumberJ + 1] = \a columns - 1
     * \param        bpNumberI     Break point number by rows.
     * \param        bpNumberJ     Break point number by columns.
     * \param [out]  newSolutionI  The new solution by rows. Should have \a bpNumberI + 2 elements. \a solutionI[0] = -1, \a solutionI[\a bpNumberI + 1] = \a rows - 1
     * \param [out]  newSolutionJ  The new solution by columns. Should have \a bpNumberJ + 2 elements. \a solutionJ[0] = -1, \a solutionJ[\a bpNumberJ + 1] = \a columns - 1
     */

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