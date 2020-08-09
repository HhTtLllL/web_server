obj = epoll_server.o main.o
CC = g++ 
target = webserver

$(target):$(obj)
	g++ $^ -o $@

%.o:%.c
	g++ -c $< -o $@
clean:
	rm *.o $(target)


