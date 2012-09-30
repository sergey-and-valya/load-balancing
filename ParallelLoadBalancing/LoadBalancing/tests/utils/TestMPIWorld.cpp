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
		e.reset();
		Message message(data, size);
		message.sender = this;
		send(target->buffer, message);
		e.wait();
	}

	void Receive(TestMPIProcessor* source, void* data, int size)
	{
		std::vector<Message> tmpBuffer;

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
				[_mpiRank, _mpiCommSize, _processors](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
				{
					assert(buf != 0);
					assert(count > 0);				
					assert(dest != _mpiRank);
					assert(dest >= 0);
					assert(dest < _mpiCommSize);
                    
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
				[_mpiRank, _mpiCommSize, _processors](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
				{
					assert(buf != 0);
					assert(count > 0);				
					assert(source != _mpiRank);
					assert(source >= 0);
					assert(source < _mpiCommSize);
                    
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
