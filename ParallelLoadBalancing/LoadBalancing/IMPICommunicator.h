#ifndef _IMPICOMMUNICATOR_H
#define _IMPICOMMUNICATOR_H

#ifdef EMULATE_MPI
typedef int MPI_Datatype;
typedef int MPI_Status;

#define MPI_SUCCESS 1
#define MPI_INTEGER 2
#define MPI_INT     MPI_INTEGER
#define MPI_DOUBLE  3
#else
#include <mpi.h>
#endif

class IMPICommunicator
{
public:
	virtual int Size(int* size) = 0;
	virtual int Rank(int* rank) = 0;

	virtual int Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag) = 0;
	virtual int Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status *status) = 0;
};

#endif