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
