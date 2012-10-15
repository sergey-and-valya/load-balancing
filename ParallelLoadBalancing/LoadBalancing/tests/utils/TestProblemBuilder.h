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

#ifndef _TESTPROBLEMBUILDER_H
#define _TESTPROBLEMBUILDER_H

#include <LoadBalancing/IProblemBuilder.h>
#include <functional>

class TestProblemBuilder : public IProblemBuilder
{
public:
	typedef std::function<void(int, int)> SetBreakPointCountFunction;
	typedef std::function<int*()>		  CreateSolutionIFunction;
	typedef std::function<int*()>		  CreateSolutionJFunction;
	typedef std::function<double*()>	  CreateLocalMatrixFunction;

	TestProblemBuilder(SetBreakPointCountFunction  setBreakPointCountImpl,
					   CreateSolutionIFunction     createSolutionIImpl,
					   CreateSolutionJFunction     createSolutionJImpl,
					   CreateLocalMatrixFunction   createLocalMatrixImpl)
		: m_setBreakPointCountImpl(setBreakPointCountImpl)
	 	, m_createSolutionIImpl(createSolutionIImpl)
		, m_createSolutionJImpl(createSolutionJImpl)
	 	, m_createLocalMatrixImpl(createLocalMatrixImpl)
	{
	}

	void SetBreakPointCount(int bpNumberI, int bpNumberJ)
	{
		m_setBreakPointCountImpl(bpNumberI, bpNumberJ);
	}

	int* CreateSolutionI()
	{
		return m_createSolutionIImpl();
	}

	int* CreateSolutionJ()
	{
		return m_createSolutionJImpl();
	}
	
	double* CreateLocalMatrix()
	{
		return m_createLocalMatrixImpl();
	}

private:
	SetBreakPointCountFunction  m_setBreakPointCountImpl;
	CreateSolutionIFunction     m_createSolutionIImpl;
	CreateSolutionJFunction     m_createSolutionJImpl;
	CreateLocalMatrixFunction   m_createLocalMatrixImpl;
};

#endif
