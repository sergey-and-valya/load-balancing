#ifndef _VECTOR_H
#define _VECTOR_H

#include <Core/IMatrix.h>

template<typename TData>
class Vector : public IMatrix<TData, int>
{
	int n;
	TData* data;
public:
	Vector(int n)
		: n(n)
	{
		data = new TData[n];
	}

	~Vector()
	{
		delete[] data;
	}
	
	virtual TData& operator[](const int& index)
	{
		return data[index];
	}

	const int& Size() const
	{
		return n;
	}
};

#endif // _VECTOR_H