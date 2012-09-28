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