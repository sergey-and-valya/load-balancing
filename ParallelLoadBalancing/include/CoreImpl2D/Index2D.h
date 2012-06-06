#ifndef _INDEX2D_H
#define _INDEX2D_H

#include <Core/IIndex.h>

class Index2D : public IIndex
{
public:
	Index2D(int i, int j);
	
	int operator[](int dimension) const;
	int Dimensions() const;

private:
	int i;
	int j;
};

#endif // _INDEX2D_H