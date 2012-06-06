#ifndef _IMATRIX_H
#define _IMATRIX_H

#include "IIndex.h"

template<typename TData>
class IMatrix
{
public:
	virtual TData& operator[](const IIndex& index) = 0;
	virtual int Dimensions() const = 0;
	virtual int SizeInDimension(int dimension) const = 0;
};

#endif // _IMATRIX_H