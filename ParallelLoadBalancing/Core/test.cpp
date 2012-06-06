#include "IMatrix.h"
#include "IIndex.h"
#include "IPartitioning.h"
#include "ISolution.h"
#include "Solution.h"
#include "Partitioning.h"

void a()
{
	int g;
	IIndex* pi;
	IIndex& i = *pi;

	i.Dimensions();
	g = i[0];
	
	IMatrix<int>* pm;
	IMatrix<int>& m = *pm;
	g = m.Dimensions();
	g = m.SizeInDimension(10);
	m[i] = 10;
	g = m[i];

	IPartitioning* pp;
	IPartitioning& p = *pp;

	g = p.CountBreakPoints();
	g = p[10];

	ISolution* ps;
	ISolution& s = *ps;

	g = s.Dimensions();
	g = s[0].CountBreakPoints();
	g = s[0][0];
	
	std::vector<int> breakpoints;
	breakpoints.push_back(10);
	breakpoints.push_back(20);
	breakpoints.push_back(30);

	std::vector<IPartitioning*> partitionings;
	partitionings.push_back(new Partitioning(breakpoints));
	
	Solution sol(partitionings);

	s.Dimensions();
	g = s[10][1];
}