#ifndef _ISOLUTION_H
#define _ISOLUTION_H

#include "IPartitioning.h"

class ISolution
{
public:
	virtual const IPartitioning& operator[](int dimension) const = 0;
	virtual int Dimensions() const = 0;
};

#endif // _ISOLUTION_H