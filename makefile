obj = epoll_server.o main.o
CC = gcc 
target = webserver

$(target):$(obj)
	gcc $^ -o $@

%.o:%.c
	gcc -c $< -o $@
clean:
	rm *.o $(target)


