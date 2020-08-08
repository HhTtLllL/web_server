#include "FileUtil.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

using namespace tt;


FileUtil::AppendFile::AppendFile(std::string filename)
	:m_fp(fopen(filename.c_str(),"ae")){
		//用户提供缓冲区
		assert(m_fp);
		setbuffer(m_fp,m_buffer,sizeof(m_buffer));

}

FileUtil::AppendFile::~AppendFile(){
	fclose(m_fp);
}

size_t FileUtil::AppendFile::mywrite(const char* logline, size_t len){
	return fwrite_unlocked(logline, 1, len, m_fp);
}

void FileUtil::AppendFile::append(const char* logline,const size_t len){
	size_t n = mywrite(logline,len);
	size_t remain = len - n;

	while( remain > 0){
		size_t x = mywrite(logline + n, remain);

		if(x == 0){
			int err = ferror(m_fp);
			if(err) fprintf(stderr,"AppendFile::append() failed !\n");
			break;
		}
		n += x;
		remain = len - n;
	}
}

void FileUtil::AppendFile::flush(){ fflush(m_fp); }


