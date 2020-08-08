# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tt/web_server/h_webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tt/web_server

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/tt/web_server/CMakeFiles /home/tt/web_server/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/tt/web_server/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named h_webserver

# Build rule for target.
h_webserver: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 h_webserver
.PHONY : h_webserver

# fast build rule for target.
h_webserver/fast:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/build
.PHONY : h_webserver/fast

#=============================================================================
# Target rules for targets named libserver_base

# Build rule for target.
libserver_base: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 libserver_base
.PHONY : libserver_base

# fast build rule for target.
libserver_base/fast:
	$(MAKE) -f base/CMakeFiles/libserver_base.dir/build.make base/CMakeFiles/libserver_base.dir/build
.PHONY : libserver_base/fast

#=============================================================================
# Target rules for targets named LoggingTest

# Build rule for target.
LoggingTest: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 LoggingTest
.PHONY : LoggingTest

# fast build rule for target.
LoggingTest/fast:
	$(MAKE) -f base/tests/CMakeFiles/LoggingTest.dir/build.make base/tests/CMakeFiles/LoggingTest.dir/build
.PHONY : LoggingTest/fast

#=============================================================================
# Target rules for targets named HTTPClient

# Build rule for target.
HTTPClient: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 HTTPClient
.PHONY : HTTPClient

# fast build rule for target.
HTTPClient/fast:
	$(MAKE) -f tests/CMakeFiles/HTTPClient.dir/build.make tests/CMakeFiles/HTTPClient.dir/build
.PHONY : HTTPClient/fast

Channel.o: Channel.cc.o

.PHONY : Channel.o

# target to build an object file
Channel.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Channel.cc.o
.PHONY : Channel.cc.o

Channel.i: Channel.cc.i

.PHONY : Channel.i

# target to preprocess a source file
Channel.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Channel.cc.i
.PHONY : Channel.cc.i

Channel.s: Channel.cc.s

.PHONY : Channel.s

# target to generate assembly for a file
Channel.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Channel.cc.s
.PHONY : Channel.cc.s

Epoll.o: Epoll.cc.o

.PHONY : Epoll.o

# target to build an object file
Epoll.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Epoll.cc.o
.PHONY : Epoll.cc.o

Epoll.i: Epoll.cc.i

.PHONY : Epoll.i

# target to preprocess a source file
Epoll.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Epoll.cc.i
.PHONY : Epoll.cc.i

Epoll.s: Epoll.cc.s

.PHONY : Epoll.s

# target to generate assembly for a file
Epoll.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Epoll.cc.s
.PHONY : Epoll.cc.s

EventLoop.o: EventLoop.cc.o

.PHONY : EventLoop.o

# target to build an object file
EventLoop.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoop.cc.o
.PHONY : EventLoop.cc.o

EventLoop.i: EventLoop.cc.i

.PHONY : EventLoop.i

# target to preprocess a source file
EventLoop.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoop.cc.i
.PHONY : EventLoop.cc.i

EventLoop.s: EventLoop.cc.s

.PHONY : EventLoop.s

# target to generate assembly for a file
EventLoop.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoop.cc.s
.PHONY : EventLoop.cc.s

EventLoopThread.o: EventLoopThread.cc.o

.PHONY : EventLoopThread.o

# target to build an object file
EventLoopThread.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoopThread.cc.o
.PHONY : EventLoopThread.cc.o

EventLoopThread.i: EventLoopThread.cc.i

.PHONY : EventLoopThread.i

# target to preprocess a source file
EventLoopThread.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoopThread.cc.i
.PHONY : EventLoopThread.cc.i

EventLoopThread.s: EventLoopThread.cc.s

.PHONY : EventLoopThread.s

# target to generate assembly for a file
EventLoopThread.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoopThread.cc.s
.PHONY : EventLoopThread.cc.s

EventLoopThreadPool.o: EventLoopThreadPool.cc.o

.PHONY : EventLoopThreadPool.o

# target to build an object file
EventLoopThreadPool.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoopThreadPool.cc.o
.PHONY : EventLoopThreadPool.cc.o

EventLoopThreadPool.i: EventLoopThreadPool.cc.i

.PHONY : EventLoopThreadPool.i

# target to preprocess a source file
EventLoopThreadPool.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoopThreadPool.cc.i
.PHONY : EventLoopThreadPool.cc.i

EventLoopThreadPool.s: EventLoopThreadPool.cc.s

.PHONY : EventLoopThreadPool.s

# target to generate assembly for a file
EventLoopThreadPool.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/EventLoopThreadPool.cc.s
.PHONY : EventLoopThreadPool.cc.s

HttpData.o: HttpData.cc.o

.PHONY : HttpData.o

# target to build an object file
HttpData.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/HttpData.cc.o
.PHONY : HttpData.cc.o

HttpData.i: HttpData.cc.i

.PHONY : HttpData.i

# target to preprocess a source file
HttpData.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/HttpData.cc.i
.PHONY : HttpData.cc.i

HttpData.s: HttpData.cc.s

.PHONY : HttpData.s

# target to generate assembly for a file
HttpData.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/HttpData.cc.s
.PHONY : HttpData.cc.s

Main.o: Main.cc.o

.PHONY : Main.o

# target to build an object file
Main.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Main.cc.o
.PHONY : Main.cc.o

Main.i: Main.cc.i

.PHONY : Main.i

# target to preprocess a source file
Main.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Main.cc.i
.PHONY : Main.cc.i

Main.s: Main.cc.s

.PHONY : Main.s

# target to generate assembly for a file
Main.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Main.cc.s
.PHONY : Main.cc.s

Server.o: Server.cc.o

.PHONY : Server.o

# target to build an object file
Server.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Server.cc.o
.PHONY : Server.cc.o

Server.i: Server.cc.i

.PHONY : Server.i

# target to preprocess a source file
Server.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Server.cc.i
.PHONY : Server.cc.i

Server.s: Server.cc.s

.PHONY : Server.s

# target to generate assembly for a file
Server.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Server.cc.s
.PHONY : Server.cc.s

Timer.o: Timer.cc.o

.PHONY : Timer.o

# target to build an object file
Timer.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Timer.cc.o
.PHONY : Timer.cc.o

Timer.i: Timer.cc.i

.PHONY : Timer.i

# target to preprocess a source file
Timer.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Timer.cc.i
.PHONY : Timer.cc.i

Timer.s: Timer.cc.s

.PHONY : Timer.s

# target to generate assembly for a file
Timer.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Timer.cc.s
.PHONY : Timer.cc.s

Util.o: Util.cc.o

.PHONY : Util.o

# target to build an object file
Util.cc.o:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Util.cc.o
.PHONY : Util.cc.o

Util.i: Util.cc.i

.PHONY : Util.i

# target to preprocess a source file
Util.cc.i:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Util.cc.i
.PHONY : Util.cc.i

Util.s: Util.cc.s

.PHONY : Util.s

# target to generate assembly for a file
Util.cc.s:
	$(MAKE) -f CMakeFiles/h_webserver.dir/build.make CMakeFiles/h_webserver.dir/Util.cc.s
.PHONY : Util.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... h_webserver"
	@echo "... edit_cache"
	@echo "... libserver_base"
	@echo "... LoggingTest"
	@echo "... HTTPClient"
	@echo "... Channel.o"
	@echo "... Channel.i"
	@echo "... Channel.s"
	@echo "... Epoll.o"
	@echo "... Epoll.i"
	@echo "... Epoll.s"
	@echo "... EventLoop.o"
	@echo "... EventLoop.i"
	@echo "... EventLoop.s"
	@echo "... EventLoopThread.o"
	@echo "... EventLoopThread.i"
	@echo "... EventLoopThread.s"
	@echo "... EventLoopThreadPool.o"
	@echo "... EventLoopThreadPool.i"
	@echo "... EventLoopThreadPool.s"
	@echo "... HttpData.o"
	@echo "... HttpData.i"
	@echo "... HttpData.s"
	@echo "... Main.o"
	@echo "... Main.i"
	@echo "... Main.s"
	@echo "... Server.o"
	@echo "... Server.i"
	@echo "... Server.s"
	@echo "... Timer.o"
	@echo "... Timer.i"
	@echo "... Timer.s"
	@echo "... Util.o"
	@echo "... Util.i"
	@echo "... Util.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
