#ifndef _TESTPROBLEMBUILDER_H
#define _TESTPROBLEMBUILDER_H

#include "../../IProblemBuilder.h"
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