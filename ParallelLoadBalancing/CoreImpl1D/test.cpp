#include "Index1D.h"
#include "Vector.h"

void a()
{
	int g;
	Index1D i = Index1D(10);
	i.Dimensions();
	g = i[0];
	
	std::vector<int> v;
	v.push_back(10);

	Vector<int> m = Vector<int>(v);
	g = m.Dimensions();
	g = m.SizeInDimension(10);
	m[i] = 10;
	g = m[i];
}