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

#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <LoadBalancing/IEnvironment.h>

class Environment : public IEnvironment
{
public:
	Environment(bool printResults)
		: printResults(printResults)
	{
	}

	void Run(IMPICommunicator& comm, IDomainModel& dm, ILoadBalancingAlgorithm& lb, ILoadBalancingCondition& lbc, IRebalancer& rb);

private:
	bool printResults;
};

#endif
