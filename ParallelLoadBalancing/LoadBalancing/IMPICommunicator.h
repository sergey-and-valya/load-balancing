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

/**
 * \class   IMPICommunicator
 *
 * \brief   MPI communicator interface.
 *          Encapsulates mpi-specific information.
 *          Allows exchanging data with specific processors.
 */

class IMPICommunicator
{
public:

    /**
     * \fn  virtual int IMPICommunicator::Size(int* size) = 0;
     *
     * \brief   retrieves size of the communicator.
     *
     * \param [out]  size    The pointer to a size to be returned.
     *
     * \return Status of operation. MPI_SUCCESS if no errors.
     */

	virtual int Size(int* size) = 0;

    /**
     * \fn  virtual int IMPICommunicator::Rank(int* rank) = 0;
     *
     * \brief   retrieves rank of the current processor.
     *
     * \param [out]  rank    The pointer to a rank to be returned.
     *
     * \return Status of operation. MPI_SUCCESS if no errors.
     */

	virtual int Rank(int* rank) = 0;

    /**
     * \fn  virtual int IMPICommunicator::Send(void* buf, int count, MPI_Datatype datatype, int dest,
     *      int tag) = 0;
     *
     * \brief   Sends data from the current processor to the specified one.
     *
     * \param [in]  buf     The buffer of elements to be sent.
     * \param   count       Number of elements in the buffer.
     * \param   datatype    The datatype of buffer elements.
     * \param   dest        Destination processor's rank.
     * \param   tag         The additional tag.
     *
     * \return Status of operation. MPI_SUCCESS if no errors.
     */

	virtual int Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag) = 0;

    /**
     * \fn  virtual int IMPICommunicator::Recv(void* buf, int count, MPI_Datatype datatype,
     *      int source, int tag, MPI_Status *status) = 0;
     *
     * \brief   Receives data from the specified processor.
     *
     * \param [out]  buf        The buffer of elements to be received.
     * \param   count           Number of elements in the buffer.
     * \param   datatype        The datatype of buffer elements.
     * \param   source          Source processor's rank.
     * \param   tag             The additional tag.
     * \param [out]  status     If not null, pointer to a status.
     *
     * \return Status of operation. MPI_SUCCESS if no errors.
     */

    virtual int Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status *status) = 0;
};

#endif
