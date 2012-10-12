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
