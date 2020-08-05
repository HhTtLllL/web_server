#pragma once

#include "noncopyable.h"
#include <string>

namespace tt{

namespace FilUtil{

class AppendFile : noncopyable{

public:
	explicit AppendFile(std::string filename);
	~AppendFile();

	void append(const char* logline, const size_t len);
	void flush();

private:
	size_t write(const char* logline,size_t len);
	File* m_fp;
	char m_buffer[64*1024];

}

} //FileUtil

} //tt
