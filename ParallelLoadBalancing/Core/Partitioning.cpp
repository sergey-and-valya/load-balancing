#include "Partitioning.h"
#include <memory.h>

Partitioning::Partitioning(std::vector<int> breakPoints)
	: breakPoints(breakPoints)
{
}

int Partitioning::operator[](int breakPointIndex) const
{
	return breakPoints[breakPointIndex];
}

int Partitioning::CountBreakPoints() const
{
	return breakPoints.size();
}