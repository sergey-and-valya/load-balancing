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
