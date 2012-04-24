#ifndef _IMATRIX_H
#define _IMATRIX_H

class IDimensional; //IDimensional.h

template<typename TData, typename TIndex = IDimensional, typename TSize = TIndex>
class IMatrix
{
public:
	virtual TData& operator[](const TIndex& index) = 0;
	virtual const TSize& Size() const = 0;
};

#endif // _IMATRIX_H