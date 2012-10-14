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

	virtual ~ILoadBalancingAlgorithm() {};
};

#endif
