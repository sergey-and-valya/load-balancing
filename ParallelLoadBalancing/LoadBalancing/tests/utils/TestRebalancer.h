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

#ifndef _TESTREBALANCER_H
#define _TESTREBALANCER_H

#include <LoadBalancing/IRebalancer.h>
#include <functional>

class TestRebalancer : public IRebalancer
{
public:
	typedef std::function<void(IMPICommunicator&, const int[], const int[], const double[], const int[], const int[], double[], int, int)> RebalanceFunction;

	TestRebalancer(RebalanceFunction rebalanceImpl)
		: m_rebalanceImpl(rebalanceImpl)
	{
	}

	void Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const double oldMatrix[], const int newSolutionI[], const int newSolutionJ[], double newMatrix[], int bpNumberI, int bpNumberJ)
	{
		m_rebalanceImpl(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ);
	}

private:
	RebalanceFunction m_rebalanceImpl;
};

#endif
