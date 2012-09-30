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

#ifndef _TESTMPIWORLD_H
#define _TESTMPIWORLD_H

#include "../../IMPICommunicator.h"
#include <functional>

class TestMPIWorld
{
public:
	typedef std::function<void(IMPICommunicator& comm)> RunFunction;

	TestMPIWorld(int mpiCommSize, RunFunction runFunction);

	void RunAndWait();

private:
	int m_mpiCommSize;
	RunFunction m_runFunction;
};

#endif
