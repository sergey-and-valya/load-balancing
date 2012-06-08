#ifndef _TESTTESTINGSYSTEM_H
#define _TESTTESTINGSYSTEM_H

#include "../../ITestingSystem.h"
#include <functional>

class TestTestingSystem : public ITestingSystem
{
public:
	typedef std::function<void(IMPICommunicator&, IProblemBuilder&)> LoadProblemFunction;
	typedef std::function<bool(IMPICommunicator&, int[], const double[], double[], const int[], const int[], int, int)> RunFunction;

	TestTestingSystem (LoadProblemFunction loadProblemImpl, RunFunction runImpl)
		: m_loadProblemImpl(loadProblemImpl)
		, m_runImpl(runImpl)
	{
	}
	
	void LoadProblem(IMPICommunicator& comm, IProblemBuilder& builder)
	{
		m_loadProblemImpl(comm, builder);
	}

	bool Run(
		IMPICommunicator& comm,
		int time_matrix[],
		const double matrix[],
		double new_matrix[],
		const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
		const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ)
	{
		return m_runImpl(comm, time_matrix, matrix, new_matrix, solutionI, solutionJ, bpNumberI, bpNumberJ);
	}

private:
	LoadProblemFunction m_loadProblemImpl;
	RunFunction m_runImpl;
};

#endif