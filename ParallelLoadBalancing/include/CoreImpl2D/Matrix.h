#ifndef _MATRIX_H
#define _MATRIX_H

#include <Core/IMatrix.h>
#include <vector>
#include <assert.h>

template<typename TData>
class Vector : public IMatrix<TData>
{
public:
	Vector(std::vector<TData> data, int m, int n)
		: data(data),
		m(m),
		n(n)
	{
	}
	
	TData& operator[](const IIndex& index)
	{
		assert(index.Dimensions() == 2);
		return data[index[0] * n + index[1]];
	}
	
	virtual int Dimensions() const
	{
		return 2;
	}

	virtual int SizeInDimension(int dimension) const
	{
		assert(dimension == 0 || dimension == 1);
		
		if(dimension == 0)
			return m;

		return n;
	}

private:
	std::vector<TData> data;
	int n;
	int m;
};

#endif // _MATRIX_H