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

#ifndef _IENVIRONMENT_H
#define _IENVIRONMENT_H

#include "IMPICommunicator.h"
#include "ITestingSystem.h"
#include "ILoadBalancingAlgorithm.h"
#include "IRebalancer.h"

/**
 * \class   IEnvironment
 *
 * \brief   Environment interface.
 *          Provides an environment for running testing system with using
 *          load balancing algorithm and rebalancer to rebalance data blocks.
 */

class IEnvironment
{
public:

    /**
     * \fn  virtual void IEnvironment::Run(IMPICommunicator& comm, ITestingSystem& ts,
     *      ILoadBalancingAlgorithm& lb, IRebalancer& rb) = 0;
     *
     * \brief   Runs testing system \a ts on the current processor specified by communicator \a comm.
     *          Runs load balancing algorithm \a lb and rebalances data using rebalancer \a rb via communicator \a comm
     *
     * \param [in,out]  comm    The communicator.
     * \param [in,out]  ts      The testing system.
     * \param [in,out]  lb      The load balancing algorithm.
     * \param [in,out]  rb      The rebalancer.
     */

	virtual void Run(IMPICommunicator& comm, ITestingSystem& ts, ILoadBalancingAlgorithm& lb, IRebalancer& rb) = 0;
};

#endif
