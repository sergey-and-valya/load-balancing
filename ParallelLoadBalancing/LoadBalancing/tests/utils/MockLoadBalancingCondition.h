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

#ifndef _MOCKLOADBALANCINGCONDITION_H
#define _MOCKLOADBALANCINGCONDITION_H

#include <LoadBalancing/ILoadBalancingCondition.h>
#include <functional>

class MockLoadBalancingCondition : public ILoadBalancingCondition
{
public:
	typedef std::function<bool(IMPICommunicator&, const int[], const int[], const int[], int, int)> ShouldRebalanceFunction;
	typedef std::function<void()> ResetFunction;

	MockLoadBalancingCondition(ShouldRebalanceFunction shouldRebalanceImpl, ResetFunction resetImpl)
		: m_shouldRebalanceImpl(shouldRebalanceImpl)
		, m_resetImpl(resetImpl)
	{
	}
	
	bool ShouldRebalance(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int solutionI[], // bpNumberI + 2, solutionI[0] = -1, solutionI[bpNumberI + 1] = m - 1
		const int solutionJ[], // bpNumberJ + 2, solutionJ[0] = -1, solutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ)
	{
		return m_shouldRebalanceImpl(comm, time_matrix, solutionI, solutionJ, bpNumberI, bpNumberJ);
	}
	
	void Reset()
	{
		m_resetImpl();
	}

private:
	ShouldRebalanceFunction m_shouldRebalanceImpl;
	ResetFunction m_resetImpl;
};

#endif
