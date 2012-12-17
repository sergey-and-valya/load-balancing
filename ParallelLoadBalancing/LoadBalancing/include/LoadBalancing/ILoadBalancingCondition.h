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

#ifndef _ILOADBALANCINGCONDITION_H
#define _ILOADBALANCINGCONDITION_H

#include "IMPICommunicator.h"

/**
 * \class   ILoadBalancingCondition
 *
 * \brief   Criteria whether run or not load balancing.
 *          Makes a decision if current data should be rebalanced among processors.
 */

class ILoadBalancingCondition
{
public:

    /**
     * \fn  virtual bool ILoadBalancingCondition::ShouldRebalance( IMPICommunicator& comm,
     *      const int time_matrix[], const int solutionI[], const int solutionJ[],
     *      int bpNumberI, int bpNumberJ) = 0;
     *
     * \brief   Runs load balancing algorithm.
     *          Makes a decision how should current data be rebalanced among processors depending on the time matrix.
     *
     * \param [in]   comm          The communicator.
     * \param [in]   time_matrix   The time matrix.
     * \param [in]   solutionI     Current solution by rows. Should have \a bpNumberI + 2 elements. \a solutionI[0] = -1, \a solutionI[\a bpNumberI + 1] = \a rows - 1
     * \param [in]   solutionJ     Current solution by columns. Should have \a bpNumberJ + 2 elements. \a solutionJ[0] = -1, \a solutionJ[\a bpNumberJ + 1] = \a columns - 1
     * \param        bpNumberI     Break point number by rows.
     * \param        bpNumberJ     Break point number by columns.
	 *
	 * \return  true if load balancing should be executed.
     */

	virtual bool ShouldRebalance(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
		const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ) = 0;

    /**
     * \fn  virtual void ILoadBalancingCondition::Reset() = 0;
     *
     * \brief   Reset current ILoadBalancingCondition state to its initial state.
     *
	 */

	virtual void Reset() = 0;

	virtual ~ILoadBalancingCondition() {};
};

#endif
