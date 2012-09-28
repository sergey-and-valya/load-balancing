#ifndef _IPROBLEMBUILDER_H
#define _IPROBLEMBUILDER_H

/**
 * \class   IProblemBuilder
 *
 * \brief   Problem builder interface. Incapsulates the way the matrix data and solution buffers are allocated at the current processor.
 */

class IProblemBuilder
{
public:

    /**
     * \fn  virtual void IProblemBuilder::SetBreakPointCount(int bpNumberI, int bpNumberJ) = 0;
     *
     * \brief   Sets break point count.
     *
     * \param   bpNumberI   Break point number by rows.
     * \param   bpNumberJ   Break point number by columns.
     */

	virtual void SetBreakPointCount(int bpNumberI, int bpNumberJ) = 0;

    /**
     * \fn  virtual int* IProblemBuilder::CreateSolutionI() = 0;
     *
     * \brief   Creates buffer for solution by rows.
     *
     * \return  Created buffer.
     */

	virtual int* CreateSolutionI() = 0;

    /**
     * \fn  virtual int* IProblemBuilder::CreateSolutionJ() = 0;
     *
     * \brief   Creates buffer for solution by columns.
     *
     * \return  Created buffer.
     */

    virtual int* CreateSolutionJ() = 0;

    /**
     * \fn  virtual double* IProblemBuilder::CreateLocalMatrix() = 0;
     *
     * \brief   Creates buffer for soring matrix data on the current processor.
     *
     * \return  Created buffer.
     */

	virtual double* CreateLocalMatrix() = 0;
};

#endif