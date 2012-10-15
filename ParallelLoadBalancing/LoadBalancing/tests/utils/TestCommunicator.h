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

#ifndef _TESTCOMMUNICATOR_H
#define _TESTCOMMUNICATOR_H

#include <LoadBalancing/IMPICommunicator.h>
#include <functional>

class TestCommunicator : public IMPICommunicator
{
public:
	typedef std::function<int(int*)> SizeFunction;
	typedef std::function<int(int*)> RankFunction;
	typedef std::function<int(void*, int, MPI_Datatype, int, int)> SendFunction;
	typedef std::function<int(void*, int, MPI_Datatype, int, int, MPI_Status*)> RecvFunction;

	TestCommunicator(SizeFunction sizeImpl, RankFunction rankImpl, SendFunction sendImpl, RecvFunction recvImpl)
		: m_sizeImpl(sizeImpl)
		, m_rankImpl(rankImpl)
		, m_sendImpl(sendImpl)
		, m_recvImpl(recvImpl)
	{
	}

	int Size(int* size)
	{
		return m_sizeImpl(size);
	}

	int Rank(int* rank)
	{
		return m_rankImpl(rank);
	}

	int Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag)
	{
		return m_sendImpl(buf, count, datatype, dest, tag);
	}

	int Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status *status)
	{
		return m_recvImpl(buf, count, datatype, source, tag, status);
	}

private:
	SizeFunction m_sizeImpl;
	RankFunction m_rankImpl;
	SendFunction m_sendImpl;
	RecvFunction m_recvImpl;
};

#endif
