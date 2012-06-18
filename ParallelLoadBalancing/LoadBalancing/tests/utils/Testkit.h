#ifndef _TESTKIT_H
#define _TESTKIT_H

void __setTest(const char* testname);
void __pass();

#define TEST(TestProc) { __setTest(#TestProc); (TestProc)(); __pass(); }

#endif