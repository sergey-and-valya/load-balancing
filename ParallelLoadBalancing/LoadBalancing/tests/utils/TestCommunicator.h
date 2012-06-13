#ifndef _TESTCOMMUNICATOR_H
#define _TESTCOMMUNICATOR_H

#include "../../IMPICommunicator.h"
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