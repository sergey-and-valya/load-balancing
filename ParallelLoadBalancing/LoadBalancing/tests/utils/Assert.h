#ifndef _ASSERT_H
#define _ASSERT_H

void __fail(const char* file, int line);

#define assert(x) { if(!(x)) __fail(__FILE__, __LINE__); }

#endif