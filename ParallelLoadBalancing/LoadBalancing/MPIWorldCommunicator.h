#ifndef _MPIWORLDCOMMUNICATOR_H
#define _MPIWORLDCOMMUNICATOR_H

#include "IMPICommunicator.h"

class MPIWorldCommunicator : public IMPICommunicator
{
public:
	int Size(int* size);
	int Rank(int* rank);

	int Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag);
	int Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status *status);
};

#endif