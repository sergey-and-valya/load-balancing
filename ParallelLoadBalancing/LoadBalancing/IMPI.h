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