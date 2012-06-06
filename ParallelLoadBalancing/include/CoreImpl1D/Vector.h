#ifndef _VECTOR_H
#define _VECTOR_H

#include <Core/IMatrix.h>
#include <vector>
#include <assert.h>

template<typename TData>
class Vector : public IMatrix<TData>
{
public:
	Vector(std::vector<TData> data)
		: data(data)
	{
	}
	
	TData& operator[](int index)
	{
		return data[index];
	}
	
	TData& operator[](const IIndex& index)
	{
		assert(index.Dimensions() == 1);
		return data[index[0]];
	}

	virtual int Dimensions() const
	{
		return 1;
	}

	virtual int SizeInDimension(int dimension) const
	{
		assert(dimension == 0);
		return data.size();
	}

private:
	std::vector<TData> data;
};

#endif // _VECTOR_H