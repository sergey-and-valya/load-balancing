#ifndef _PARTITIONING_H
#define _PARTITIONING_H

#include "IPartitioning.h"
#include <vector>

class Partitioning : public IPartitioning
{
public:
	Partitioning(std::vector<int> breakPoints);

	int operator[](int breakPointIndex) const;
	int CountBreakPoints() const;

private:
	std::vector<int> breakPoints;
};

#endif // _PARTITIONING_H