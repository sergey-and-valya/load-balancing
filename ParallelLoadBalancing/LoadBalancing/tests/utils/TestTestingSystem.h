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
