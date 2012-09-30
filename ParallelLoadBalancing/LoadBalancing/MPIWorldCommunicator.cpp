// ****************************************************************************
// LOAD BALANCING
// Copyright (C) 2012 Gerasimov, Smoryakova, Katerov, Afanasov, Kulakovich, Sobolev
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ****************************************************************************

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
