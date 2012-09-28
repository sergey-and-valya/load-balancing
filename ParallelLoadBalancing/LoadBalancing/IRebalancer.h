#ifndef _IREBALANCER_H
#define _IREBALANCER_H

#include "IMPICommunicator.h"

/**
 * \class   IRebalancer
 *
 * \brief   Rebalancer interface.
 *          Responsible for moving blocks of matrix from/to surroundings
 */

class IRebalancer
{
public:

    /**
     * \fn  virtual void IRebalancer::Rebalance(IMPICommunicator& comm, const int oldSolutionI[],
     *      const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[],
     *      const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ) = 0;
     *
     * \brief   Performs rebalancing on the current processor (determined by \a comm.Rank()).
     *          Exchanges blocks of data with surroundings via communicator \a comm to distribute
     *          data according to the new solution.
     *
     * \param  [in]      comm          The communicator.
     * \param  [in]      oldSolutionI  Old solution solution by rows. Should have \a bpNumberI + 2 elements. \a solutionI[0] = -1, \a solutionI[\a bpNumberI + 1] = \a rows - 1
     * \param  [in]      oldSolutionJ  Old solution solution by columns. Should have \a bpNumberJ + 2 elements. \a solutionJ[0] = -1, \a solutionJ[\a bpNumberJ + 1] = \a columns - 1
     * \param  [in]      oldMatrix     Old matrix values stored at the current processor.
     * \param  [in]      newSolutionI  New solution solution by rows. Should have \a bpNumberI + 2 elements. \a solutionI[0] = -1, \a solutionI[\a bpNumberI + 1] = \a rows - 1
     * \param  [in]      newSolutionJ  New solution solution by columns. Should have \a bpNumberJ + 2 elements. \a solutionJ[0] = -1, \a solutionJ[\a bpNumberJ + 1] = \a columns - 1
     * \param  [out]     newMatrix     New matrix values to be stored at the current processor.
     * \param            bpNumberI     Break point number by rows.
     * \param            bpNumberJ     Break point number by columns.
     */

	virtual void Rebalance(IMPICommunicator& comm, 
                           const int oldSolutionI[],
                           const int oldSolutionJ[],
                           const double oldMatrix[],
                           const int newSolutionI[],
                           const int newSolutionJ[],
                           double newMatrix[],
                           int bpNumberI,
                           int bpNumberJ) = 0;
};

#endif