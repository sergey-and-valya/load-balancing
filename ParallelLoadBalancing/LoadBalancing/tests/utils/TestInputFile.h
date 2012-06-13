#ifndef _TESTINPUTFILE_H
#define _TESTINPUTFILE_H

#include "../../IInputFile.h"
#include <functional>

class TestInputFile : public IInputFile
{
public:
	typedef std::function<size_t(void*, size_t, size_t)> ReadFunction;
	typedef std::function<int(long, int)> SeekFunction;

	TestInputFile(ReadFunction readImpl, SeekFunction seekImpl)
		: m_readImpl(readImpl)
		, m_seekImpl(seekImpl)
	{
	}

	
	size_t Read(void *buffer, size_t elementSize, size_t count)
	{
		return m_readImpl(buffer, elementSize, count);
	}

	int Seek(long offset, int origin)
	{
		return m_seekImpl(offset, origin);
	}

private:
	ReadFunction m_readImpl;
	SeekFunction m_seekImpl;
};

#endif