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

#ifndef _IMPI_H
#define _IMPI_H

#include "IMPICommunicator.h"

/**
 * \class   IMPI
 *
 * \brief   MPI interface. Should be used for initialization and deinitianilization of MPI. Contains world communicator.
 */

class IMPI
{
public:

    /**
     * \fn  virtual int IMPI::Init(int *argc, char ***argv) = 0;
     *
     * \brief   Initialises MPI.
     *
     * \param [in,out]  argc    Program command line argument count.
     * \param [in,out]  argv    Program command line arguments.
     *
     * \return  .
     */

	virtual int Init(int *argc, char ***argv) = 0;

    /**
     * \fn  virtual IMPICommunicator& IMPI::World() = 0;
     *
     * \brief   Gets the world communicator.
     *
     * \return  The world communicator.
     */

    virtual IMPICommunicator& World() = 0;

    /**
     * \fn  virtual void IMPI::Finalize() = 0;
     *
     * \brief   Finalizes MPI.
     */

	virtual void Finalize() = 0;
};

#endif
