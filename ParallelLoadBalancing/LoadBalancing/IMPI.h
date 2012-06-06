#ifndef _IMPI_H
#define _IMPI_H

#include "mpi.h"
#include "IMPICommunicator.h"

class IMPI
{
public:
	virtual int Init(int *argc, char ***argv) = 0;
	virtual IMPICommunicator& World() = 0;
	virtual void Finalize() = 0;
};

#endif