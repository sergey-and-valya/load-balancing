#include "MPIWorldCommunicator.h"

int MPIWorldCommunicator::Size(int* size)
{
	return MPI_Comm_size(MPI_COMM_WORLD, size);
}

int MPIWorldCommunicator::Rank(int* rank)
{
	return MPI_Comm_rank(MPI_COMM_WORLD, rank);
}

int MPIWorldCommunicator::Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag)
{
	return MPI_Send(buf, count, datatype, dest, tag, MPI_COMM_WORLD);
}

int MPIWorldCommunicator::Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status *status)
{
	return MPI_Recv(buf, count, datatype, source, tag, MPI_COMM_WORLD, status);
}