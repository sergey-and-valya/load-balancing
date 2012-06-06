#ifndef _SPLITTED_MATRIX_H
#define _SPLITTED_MATRIX_H

#include <Core/IMatrix.h>
#include <Core/ISolution.h>

template<typename TData, typename TIndex = const IIndex&>
class SplittedMatrix : public IMatrix<TData, TIndex>
{
public:
	SplittedMatrix(IMatrix<TData, TIndex>& matrix, ISolution);
	
	TData& operator[](const IIndex& index)
	{
	}

	int Dimensions() const
	{
	}

	int SizeInDimension(int dimension) const = 0;

private:
	int m;
	int n;
};

#endif // _SPLITTED_MATRIX_H