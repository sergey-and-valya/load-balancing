#include "Testkit.h"
#include "Assert.h"

#include <stdio.h>
#include <stdlib.h>

static const char* __testname;

void __setTest(const char* testname)
{
	__testname = testname;
}

void __pass()
{
	printf("%-50s passed\n", __testname);
}

void __fail(const char* file, int line)
{
	printf("%-50s failed\n  at %s:%d\n", __testname, file, line);
	exit(0);
} 