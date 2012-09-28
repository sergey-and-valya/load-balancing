#ifndef _ITESTINGSYSTEM_H
#define _ITESTINGSYSTEM_H

#include "IMPICommunicator.h"
#include "IProblemBuilder.h"

class IProblemBuilder;

/**
 * \class   ITestingSystem
 *
 * \brief   Testing system interface.
 *          Responsible for loading problem on current processor and performing next iteration of calculating function.
 */

class ITestingSystem
{
public:

    /**
     * \fn  virtual void ITestingSystem::LoadProblem(IMPICommunicator& comm,
     *      IProblemBuilder& builder) = 0;
     *
     * \brief   Loads a problem.
     *
     * \param   comm    The communicator.
     * \param   builder The builder providing buffers for solution and matrix data.
     */

	virtual void LoadProblem(IMPICommunicator& comm, IProblemBuilder& builder) = 0;

    /**
     * \fn  virtual bool ITestingSystem::Run( IMPICommunicator& comm, int time_matrix[],
     *      const double matrix[], double new_matrix[], const int solutionI[], const int solutionJ[],
     *      int bpNumberI, int bpNumberJ) = 0;
     *
     * \brief   Runs.
     *
     * \param [in,out]  comm         The communicator.
     * \param [out]  time_matrix     The time matrix to be calculated.
     * \param [in]   matrix          The current matrix data stored on the current processor.
     * \param [out]  new_matrix      The new matrix data to be calculated and stored on the current processor.
     * \param [in]   solutionI       The current solution by rows. Should have \a bpNumberI + 2 elements. \a solutionI[0] = -1, \a solutionI[\a bpNumberI + 1] = \a rows - 1
     * \param [in]   solutionJ       The current solution by columns. Should have \a bpNumberJ + 2 elements. \a solutionJ[0] = -1, \a solutionJ[\a bpNumberJ + 1] = \a columns - 1
     * \param   bpNumberI            Break point number by rows.
     * \param   bpNumberJ            Break point number by columns.
     *
     * \return  true if it can do one more step.
     */

	virtual bool Run(
		IMPICommunicator& comm,
		int time_matrix[],
		const double matrix[],
		double new_matrix[],
		const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
		const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ) = 0;
};

#endif