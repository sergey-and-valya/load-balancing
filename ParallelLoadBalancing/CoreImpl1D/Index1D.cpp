#include "Index1D.h"

Index1D::Index1D(int n)
		: n(n)
{
}

int& Index1D::operator[](int dimension)
{
	return n;
}