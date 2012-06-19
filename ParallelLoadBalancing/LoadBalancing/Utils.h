#ifndef _UTILS_H
#define _UTILS_H

#include "IMPICommunicator.h"

void PrintDistributedMatrix(IMPICommunicator& comm, int bpNumberI, int bpNumberJ, const double localMatrix[], int localWidth, int localHeight);

#endif