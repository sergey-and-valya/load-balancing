#ifndef _IINDEX_H
#define _IINDEX_H

class IIndex
{
public:
	virtual int operator[](int dimension) const = 0;
	virtual int Dimensions() const = 0;
};

#endif // _IINDEX_H