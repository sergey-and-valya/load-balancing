#include "TestingSystemTest.h"

#include "../ITestingSystem.h"
#include "../IMPICommunicator.h"

#include "../TestingSystem.h"

#include "utils/TestCommunicator.h"
#include "utils/Assert.h"


void TestingSystemTest()
{
	int bpNumberI = 5;
	int bpNumberJ = 6;
	int mpiRank = 10;

	int procI = mpiRank / (bpNumberJ + 1);
	int procJ = mpiRank % (bpNumberJ + 1);

	auto comm = TestCommunicator(
		[bpNumberI, bpNumberJ](int* size) -> int
		{
			*size = (bpNumberI + 1) * (bpNumberJ + 1);
			return MPI_SUCCESS;
		},
		[mpiRank](int* rank) -> int
		{
			*rank = mpiRank;
			return MPI_SUCCESS;
		},
		[](void* buf, int count, MPI_Datatype datatype, int dest, int tag) -> int
		{
			return MPI_SUCCESS;
		},
		[](void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Status* status) -> int
		{
			return MPI_SUCCESS;
		}
	);

	auto ts = TestingSystem("C:\\StartMatrix\\matrix", 10);
	
	//ts.LoadProblem(comm, );
}
