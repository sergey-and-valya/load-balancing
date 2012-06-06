#ifndef _IPARTITIONING_H
#define _IPARTITIONING_H

#include "IIndex.h"

class IPartitioning
{
public:
	virtual int operator[](int breakPointIndex) const = 0;
	virtual int CountBreakPoints() const = 0;
};

#endif // _IPARTITIONING_H