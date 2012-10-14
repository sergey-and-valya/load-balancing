#include "SampleFunction.h"
#include <math.h>
#include <stdlib.h>

#define SIZE_BLOCK 3
#define PI 3.141592653589793238462643
#define LIMIT(arr, limit) ((arr > 10.0) ? 10.0 : arr)

double SampleFunction::operator()(const Values& values, int i, int j)
{
	double sum = 0.0;
	double coef[SIZE_BLOCK][SIZE_BLOCK];

	coef[0][0] =  1 / 4  * (i - 1) * (i - 2) * (j - 1) * (j - 2) * (j + 1);
	coef[0][1] = -1 / 4  * i * (i + 1) * (i - 2) * (j - 1) * (j - 2) * (j + 1);
	coef[0][2] = -1 / 4  * j * (i - 1) * (i - 2) * (i + 1) * (j + 1) * (j - 2);
	coef[1][0] = -1 / 12 * i * (i - 1) * (i - 2) * (j - 1) * (j - 2) * (j + 1);
	coef[1][1] = -1 / 12 * j * (i - 1) * (i - 2) * (i + 1) * (j - 1) * (j - 2);
	coef[1][2] =  1 / 36 * i * j * (i - 1) * (i - 2) * (j - 1) * (j + 2);
	coef[2][0] = -1 / 36 * i * j * (i - 1) * (i - 2) * (j - 1) * (j + 1);
	coef[2][1] =  1 / 12 * i * j * (i - 1) * (i - 2) * (j + 1) * (j - 2);
	coef[2][2] = -1 / 12 * i * j * (i + 1) * (i - 2) * (j - 1) * (j + 1);
		
	int count_elem = 0;
	for (int k = 0; k < SIZE_BLOCK; k++)
		for (int l = 0; l < SIZE_BLOCK; l++)
			if (values.HasValue(k, l))
			{
				count_elem ++;						
			}

	int count = 1 + (LIMIT(values.Value(SIZE_BLOCK / 2, SIZE_BLOCK / 2) / 2.0, 1.0)) * 3;
	
	for (int m = 0; m < count; m++)
		for (int k = 0; k < SIZE_BLOCK; k++)
			for (int l = 0; l < SIZE_BLOCK; l++)
				if (values.HasValue(k, l))
				{
					double value = values.Value(k, l);
					sum += abs(cos(coef[k][l] * tanh(sin(PI * LIMIT(value, 10.0))) + sinh(LIMIT(value, 10.0)) + cosh(LIMIT(value, 10.0)) + tanh(LIMIT(LIMIT(PI * value, 10.0), 10))));
				}

	sum /= count_elem;	
	return sum;
}
