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

#ifndef _TESTLOADBALANCING_H
#define _TESTLOADBALANCING_H

#include <LoadBalancing/ILoadBalancingAlgorithm.h>
#include <functional>

class TestLoadBalancing : public ILoadBalancingAlgorithm
{
public:
	typedef std::function<void(IMPICommunicator&, const int[], const int[], const int[], int, int, int[], int[])> RunFunction;

	TestLoadBalancing(RunFunction runImpl)
		: m_runImpl(runImpl)
	{
	}

	void Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[])
	{
		m_runImpl(comm, time_matrix, oldSolutionI, oldSolutionJ, bpNumberI, bpNumberJ, newSolutionI, newSolutionJ);
	}

private:
	RunFunction m_runImpl;
};

#endif
