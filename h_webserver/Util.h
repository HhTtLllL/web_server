#ifndef __UTIL_H__
#define __UTIL_H__

#include <cstdlib>
#include <string>

ssize_t readn(ing fd, void *buff, size_t n);
ssize_t readn(int fd, std::string& inBuffer, bool &zero);
ssize_t readn(int fd, std::string& inBuffer);

ssize_t writen(int fd, void *buff, size_t n);
ssize_t writen(int fd, std::string& sbuff);


void handle_for_sigpipe();







#endif


