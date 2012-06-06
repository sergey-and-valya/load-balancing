#ifndef _ASSERT_H
#define _ASSERT_H

#include <stdlib.h>

#define assert(x) { if(!(x)) { printf("test failed at %s:%d\n", __FILE__, __LINE__); exit(0); } }

#endif