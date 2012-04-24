#ifndef _IDIMENSIONAL_H
#define _IDIMENSIONAL_H

class IDimensional
{
public:
	virtual int Dimensions() const = 0;
	virtual int& operator[](int dimension) = 0;
};

#endif // _IDIMENSIONAL_H