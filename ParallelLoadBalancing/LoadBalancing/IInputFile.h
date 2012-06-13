#ifndef _IINPUTFILE_H
#define _IINPUTFILE_H

class IInputFile
{
public:
	virtual size_t Read(void *buffer, size_t elementSize, size_t count) = 0;
	virtual int Seek(long offset, int origin) = 0;
};

#endif