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