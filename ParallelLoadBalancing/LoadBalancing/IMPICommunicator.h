#ifndef _IMPICOMMUNICATOR_H
#define _IMPICOMMUNICATOR_H

#include <mpi.h>

class IMPICommunicator
{
public:
	virtual int Size(int* size) = 0;
	virtual int Rank(int* rank) = 0;

	virtual int Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag) = 0;
	virtual int Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status *status) = 0;
};

#endif