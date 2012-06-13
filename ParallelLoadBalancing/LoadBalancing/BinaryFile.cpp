#include "BinaryFile.h"

BinaryFile::BinaryFile(const char* filename)
{
	fopen_s(&file, filename, "rb");
}

BinaryFile::~BinaryFile()
{
	fclose(file);
}

size_t BinaryFile::Read(void *buffer, size_t elementSize, size_t count)
{
	return fread(buffer, elementSize, count, file);
}

int BinaryFile::Seek(long offset, int origin)
{
	return fseek(file, offset, origin);
}