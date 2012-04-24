#ifndef _ISOLUTION_H
#define _ISOLUTION_H

class IDimensional; //IDimensional.h

template<typename TPartitioning = IDimensional, typename TSize = IDimensional>
class ISolution
{
public:
	virtual const TPartitioning& operator[](int dimension) const = 0;
	virtual const TSize& Size() const = 0;
};

#endif // _ISOLUTION_H