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

#ifndef _SAMPLELOADBALANCINGALGORITHM_H
#define _SAMPLELOADBALANCINGALGORITHM_H

#include <LoadBalancing/ILoadBalancingAlgorithm.h>

class SampleLoadBalancingAlgorithm : public ILoadBalancingAlgorithm
{
public:
	SampleLoadBalancingAlgorithm(int parameter1, int parameter2);

	void Run(
		IMPICommunicator& comm,
		const int time_matrix[],
		const int oldSolutionI[], // bpNumberI + 2, oldSolutionI[0] = -1, oldSolutionI[bpNumberI + 1] = m - 1
		const int oldSolutionJ[], // bpNumberJ + 2, oldSolutionJ[0] = -1, oldSolutionJ[bpNumberJ + 1] = n - 1
		int bpNumberI,
		int bpNumberJ,
		int newSolutionI[],
		int newSolutionJ[]);

	int parameter1;
	int parameter2;
};

#endif
