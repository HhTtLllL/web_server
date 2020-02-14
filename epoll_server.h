#ifndef _EPOLL_SERVER_H
#define _EPOLL_SERVER_H

void epoll_run(int port);
int init_listen_fd(int port,int epfd);
void do_accept(int lfd,int epfd);
int get_line(int sock,char* buf,int size);
void do_read(int cfd,int epfd);
void http_request(const char* request,int cfd);
void disconnect(int cfd,int epfd);
void send_respond_head(int cfd,int no,const char* desp,const char* type,long len);
void send_file(int cfd,const char* filename);
void send_dir(int cfd,const char* dirname);
void decode_str(char* to,char* from);
void encode_str(char* to,int tosize,const char* from);
int hexit(char c);
const char* get_file_type(const char* name);

#endif
