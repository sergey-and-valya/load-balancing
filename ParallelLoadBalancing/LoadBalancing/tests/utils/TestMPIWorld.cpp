#include "TestMPIWorld.h"

#include "../../IMPICommunicator.h"
#include "TestCommunicator.h"
#include "Assert.h"

#include <agents.h>

using namespace Concurrency;


class TestMPIProcessor : public agent
{
private:
	struct Message
	{
		Message(void* data, int size)
			: data(data)
			, size(size)
		{
		}

		void* data;
		int size;
		TestMPIProcessor* sender;
	};

public:
	typedef std::function<void()> RunFunction;

	TestMPIProcessor(RunFunction runImpl)
		: m_runImpl(runImpl)
	{
	}

	void run()
	{
		m_runImpl();

		done();
	}

	void Send(TestMPIProcessor* target, void* data, int size)
	{
		assert(this != target);
		assert(data != 0);
		assert(size > 0);
		e.reset();
		Message message(data, size);
		message.sender = this;
		send(target->buffer, message);
		e.wait();
	}

	void Receive(TestMPIProcessor* source, void* data, int size)
	{
		std::vector<Message> tmpBuffer;
		assert(this != source);
		assert(data != 0);
		assert(size > 0);

		while(true)
		{
			Message message = receive(buffer);
			if(message.sender == source)
			{
				assert(message.size == size);
				memcpy(data, message.data, size);
				source->e.set();
				break;
			}
			else
			{
				tmpBuffer.push_back(message);
			}
		}

		for(auto p = tmpBuffer.begin(); p < tmpBuffer.end(); p++)
		{
			buffer.enqueue(*p);
		}
	}
	
private:
	RunFunction m_runImpl;
	unbounded_buffer<Message> buffer;
	event e;
};


TestMPIWorld::TestMPIWorld(int mpiCommSize, TestMPIWorld::RunFunction runFunction)
	: m_mpiCommSize(mpiCommSize)
	, m_runFunction(runFunction)
{
}

void TestMPIWorld::RunAndWait()
{
	auto processors = new TestMPIProcessor*[m_mpiCommSize];
	
	for(int mpiRank = 0; mpiRank < m_mpiCommSize; mpiRank++)
	{
		processors[mpiRank] = new TestMPIProcessor([this, processors, mpiRank]()
		{
			auto _mpiCommSize = m_mpiCommSize;
			auto _mpiRank = mpiRank;
			auto _processors = processors;

			auto comm = TestCommunicator(
				[_mpiCommSize](int* size) -> int
				{
					*size = _mpiCommSize;
					return MPI_SUCCESS;
				},
				[_mpiRank](int* rank) -> int
				{
					*rank = _mpiRank;
					return MPI_SUCCESS;
				},
				[_mpiRank, _processors](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
				{
                    int size;

                    switch(datatype)
                    {
                    case MPI_INTEGER:
                        size = sizeof(int);
                        break;
                    case MPI_DOUBLE:
                        size = sizeof(double);
                        break;
                    default:
                        assert(false);
                        break;
                    }

					_processors[_mpiRank]->Send(_processors[dest], buf, count * size);
								
					return MPI_SUCCESS;
				},
				[_mpiRank, _processors](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
				{
                    int size;

                    switch(datatype)
                    {
                    case MPI_INTEGER:
                        size = sizeof(int);
                        break;
                    case MPI_DOUBLE:
                        size = sizeof(double);
                        break;
                    default:
                        assert(false);
                        break;
                    }

					_processors[_mpiRank]->Receive(_processors[source], buf, count * size);
								
					return MPI_SUCCESS;
				}
			);

			m_runFunction(comm);
		});
	}

	for(int mpiRank = 0; mpiRank < m_mpiCommSize; mpiRank++)
	{
		processors[mpiRank]->start();
	}
		
	for(int mpiRank = 0; mpiRank < m_mpiCommSize; mpiRank++)
	{
		agent::wait(processors[mpiRank]);
	}
		
	for(int mpiRank = 0; mpiRank < m_mpiCommSize; mpiRank++)
	{
		delete processors[mpiRank];
	}

	delete[] processors;
}
