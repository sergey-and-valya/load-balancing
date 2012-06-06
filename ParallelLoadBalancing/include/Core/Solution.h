#ifndef _SOLUTION_H
#define _SOLUTION_H

#include "ISolution.h"
#include "IPartitioning.h"
#include <vector>

class Solution : public ISolution
{
public:
	Solution(std::vector<IPartitioning*>& partitionings)
		: partitionings(partitionings)
	{
	}

	const IPartitioning& operator[](int dimension) const
	{
		return *partitionings[dimension];
	}

	int Dimensions() const
	{
		return partitionings.size();
	}

private:
	std::vector<IPartitioning*> partitionings;
};

#endif // _SOLUTION_H