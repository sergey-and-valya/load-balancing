#include "Index2D.h"
#include <assert.h>

Index2D::Index2D(int i, int j)
		: i(i),
		j(j)
{
}

int Index2D::operator[](int dimension) const
{
	assert(0 <= dimension && dimension < 2);
	if(dimension == 0)
		return i;

	return j;
}

int Index2D::Dimensions() const
{
	return 2;
}