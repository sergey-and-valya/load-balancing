#include "Index1D.h"
#include <assert.h>

Index1D::Index1D(int i)
		: i(i)
{
}

int Index1D::operator[](int dimension) const
{
	assert(dimension == 0);
	return i;
}

int Index1D::Dimensions() const
{
	return 1;
}