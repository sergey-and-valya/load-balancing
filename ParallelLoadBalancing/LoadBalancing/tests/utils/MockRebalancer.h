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

#ifndef _MOCKREBALANCER_H
#define _MOCKREBALANCER_H

#include <LoadBalancing/IRebalancer.h>
#include <functional>

class MockRebalancer : public IRebalancer
{
public:
	typedef std::function<void(IMPICommunicator&, const int[], const int[], const void*, const int[], const int[], void*, int, int, MPI_Datatype)> RebalanceFunction;

	MockRebalancer(RebalanceFunction rebalanceImpl)
		: m_rebalanceImpl(rebalanceImpl)
	{
	}

	void Rebalance(IMPICommunicator& comm, const int oldSolutionI[], const int oldSolutionJ[], const void* oldMatrix, const int newSolutionI[], const int newSolutionJ[], void* newMatrix, int bpNumberI, int bpNumberJ, MPI_Datatype datatype, size_t elementSize)
	{
		m_rebalanceImpl(comm, oldSolutionI, oldSolutionJ, oldMatrix, newSolutionI, newSolutionJ, newMatrix, bpNumberI, bpNumberJ, datatype);
	}

private:
	RebalanceFunction m_rebalanceImpl;
};

#endif
