#ifndef _BINARYFILE_H
#define _BINARYFILE_H

#include "IInputFile.h"
#include <stdio.h>

class BinaryFile : public IInputFile
{
public:
	BinaryFile(const char* filename);
	~BinaryFile();

	size_t Read(void *buffer, size_t elementSize, size_t count);
	int Seek(long offset, int origin);

private:

	FILE* file;
};

#endif