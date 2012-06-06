#ifndef _IPROBLEMBUILDER_H
#define _IPROBLEMBUILDER_H

class IProblemBuilder
{
public:
	virtual void SetBreakPointCount(int bpNumberI, int bpNumberJ) = 0;

	virtual int* CreateSolutionI() = 0;
	virtual int* CreateSolutionJ() = 0;
	
	virtual double* CreateLocalMatrix() = 0;
};

#endif