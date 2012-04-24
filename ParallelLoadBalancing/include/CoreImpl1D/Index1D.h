#ifndef _INDEX1D_H
#define _INDEX1D_H

#include <Core/IDimensional.h>

class Index1D : IDimensional
{
	int n;
public:
	Index1D(int n);
	
	int Dimensions() const { return 1; }
	
	int& operator[](int dimension);
};

#endif // _INDEX1D_H