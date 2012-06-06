#ifndef _IMODIFIEDSOLUTIONBUILDER_H
#define _IMODIFIEDSOLUTIONBUILDER_H

class IModifiedSolutionBuilder
{
public:
	virtual void MoveBreakPoint(int dimension, int breakPointIndex, int deltaPosition) = 0;
};

#endif // _IMODIFIEDSOLUTIONBUILDER_H