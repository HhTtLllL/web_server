# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/tt/web_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tt/web_server/build

# Include any dependencies generated for this target.
include h_webserver/base/CMakeFiles/libserver_base.dir/depend.make

# Include the progress variables for this target.
include h_webserver/base/CMakeFiles/libserver_base.dir/progress.make

# Include the compile flags for this target's objects.
include h_webserver/base/CMakeFiles/libserver_base.dir/flags.make

h_webserver/base/CMakeFiles/libserver_base.dir/AsyncLogging.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/AsyncLogging.cc.o: ../h_webserver/base/AsyncLogging.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/AsyncLogging.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/AsyncLogging.cc.o -c /home/tt/web_server/h_webserver/base/AsyncLogging.cc

h_webserver/base/CMakeFiles/libserver_base.dir/AsyncLogging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/AsyncLogging.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/AsyncLogging.cc > CMakeFiles/libserver_base.dir/AsyncLogging.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/AsyncLogging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/AsyncLogging.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/AsyncLogging.cc -o CMakeFiles/libserver_base.dir/AsyncLogging.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/CountDownLatch.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/CountDownLatch.cc.o: ../h_webserver/base/CountDownLatch.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/CountDownLatch.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/CountDownLatch.cc.o -c /home/tt/web_server/h_webserver/base/CountDownLatch.cc

h_webserver/base/CMakeFiles/libserver_base.dir/CountDownLatch.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/CountDownLatch.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/CountDownLatch.cc > CMakeFiles/libserver_base.dir/CountDownLatch.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/CountDownLatch.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/CountDownLatch.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/CountDownLatch.cc -o CMakeFiles/libserver_base.dir/CountDownLatch.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/FileUtil.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/FileUtil.cc.o: ../h_webserver/base/FileUtil.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/FileUtil.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/FileUtil.cc.o -c /home/tt/web_server/h_webserver/base/FileUtil.cc

h_webserver/base/CMakeFiles/libserver_base.dir/FileUtil.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/FileUtil.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/FileUtil.cc > CMakeFiles/libserver_base.dir/FileUtil.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/FileUtil.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/FileUtil.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/FileUtil.cc -o CMakeFiles/libserver_base.dir/FileUtil.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/LogFile.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/LogFile.cc.o: ../h_webserver/base/LogFile.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/LogFile.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/LogFile.cc.o -c /home/tt/web_server/h_webserver/base/LogFile.cc

h_webserver/base/CMakeFiles/libserver_base.dir/LogFile.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/LogFile.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/LogFile.cc > CMakeFiles/libserver_base.dir/LogFile.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/LogFile.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/LogFile.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/LogFile.cc -o CMakeFiles/libserver_base.dir/LogFile.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/Logging.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/Logging.cc.o: ../h_webserver/base/Logging.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/Logging.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/Logging.cc.o -c /home/tt/web_server/h_webserver/base/Logging.cc

h_webserver/base/CMakeFiles/libserver_base.dir/Logging.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/Logging.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/Logging.cc > CMakeFiles/libserver_base.dir/Logging.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/Logging.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/Logging.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/Logging.cc -o CMakeFiles/libserver_base.dir/Logging.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/LogStream.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/LogStream.cc.o: ../h_webserver/base/LogStream.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/LogStream.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/LogStream.cc.o -c /home/tt/web_server/h_webserver/base/LogStream.cc

h_webserver/base/CMakeFiles/libserver_base.dir/LogStream.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/LogStream.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/LogStream.cc > CMakeFiles/libserver_base.dir/LogStream.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/LogStream.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/LogStream.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/LogStream.cc -o CMakeFiles/libserver_base.dir/LogStream.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/Thread.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/Thread.cc.o: ../h_webserver/base/Thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/Thread.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/Thread.cc.o -c /home/tt/web_server/h_webserver/base/Thread.cc

h_webserver/base/CMakeFiles/libserver_base.dir/Thread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/Thread.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/Thread.cc > CMakeFiles/libserver_base.dir/Thread.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/Thread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/Thread.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/Thread.cc -o CMakeFiles/libserver_base.dir/Thread.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/CurrentThread.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/CurrentThread.cc.o: ../h_webserver/base/CurrentThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/CurrentThread.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/CurrentThread.cc.o -c /home/tt/web_server/h_webserver/base/CurrentThread.cc

h_webserver/base/CMakeFiles/libserver_base.dir/CurrentThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/CurrentThread.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/CurrentThread.cc > CMakeFiles/libserver_base.dir/CurrentThread.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/CurrentThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/CurrentThread.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/CurrentThread.cc -o CMakeFiles/libserver_base.dir/CurrentThread.cc.s

h_webserver/base/CMakeFiles/libserver_base.dir/Condition.cc.o: h_webserver/base/CMakeFiles/libserver_base.dir/flags.make
h_webserver/base/CMakeFiles/libserver_base.dir/Condition.cc.o: ../h_webserver/base/Condition.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object h_webserver/base/CMakeFiles/libserver_base.dir/Condition.cc.o"
	cd /home/tt/web_server/build/h_webserver/base && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/libserver_base.dir/Condition.cc.o -c /home/tt/web_server/h_webserver/base/Condition.cc

h_webserver/base/CMakeFiles/libserver_base.dir/Condition.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/libserver_base.dir/Condition.cc.i"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/base/Condition.cc > CMakeFiles/libserver_base.dir/Condition.cc.i

h_webserver/base/CMakeFiles/libserver_base.dir/Condition.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/libserver_base.dir/Condition.cc.s"
	cd /home/tt/web_server/build/h_webserver/base && g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/base/Condition.cc -o CMakeFiles/libserver_base.dir/Condition.cc.s

# Object files for target libserver_base
libserver_base_OBJECTS = \
"CMakeFiles/libserver_base.dir/AsyncLogging.cc.o" \
"CMakeFiles/libserver_base.dir/CountDownLatch.cc.o" \
"CMakeFiles/libserver_base.dir/FileUtil.cc.o" \
"CMakeFiles/libserver_base.dir/LogFile.cc.o" \
"CMakeFiles/libserver_base.dir/Logging.cc.o" \
"CMakeFiles/libserver_base.dir/LogStream.cc.o" \
"CMakeFiles/libserver_base.dir/Thread.cc.o" \
"CMakeFiles/libserver_base.dir/CurrentThread.cc.o" \
"CMakeFiles/libserver_base.dir/Condition.cc.o"

# External object files for target libserver_base
libserver_base_EXTERNAL_OBJECTS =

h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/AsyncLogging.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/CountDownLatch.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/FileUtil.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/LogFile.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/Logging.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/LogStream.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/Thread.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/CurrentThread.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/Condition.cc.o
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/build.make
h_webserver/base/libserver_base.a: h_webserver/base/CMakeFiles/libserver_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tt/web_server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX static library libserver_base.a"
	cd /home/tt/web_server/build/h_webserver/base && $(CMAKE_COMMAND) -P CMakeFiles/libserver_base.dir/cmake_clean_target.cmake
	cd /home/tt/web_server/build/h_webserver/base && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/libserver_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
h_webserver/base/CMakeFiles/libserver_base.dir/build: h_webserver/base/libserver_base.a

.PHONY : h_webserver/base/CMakeFiles/libserver_base.dir/build

h_webserver/base/CMakeFiles/libserver_base.dir/clean:
	cd /home/tt/web_server/build/h_webserver/base && $(CMAKE_COMMAND) -P CMakeFiles/libserver_base.dir/cmake_clean.cmake
.PHONY : h_webserver/base/CMakeFiles/libserver_base.dir/clean

h_webserver/base/CMakeFiles/libserver_base.dir/depend:
	cd /home/tt/web_server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tt/web_server /home/tt/web_server/h_webserver/base /home/tt/web_server/build /home/tt/web_server/build/h_webserver/base /home/tt/web_server/build/h_webserver/base/CMakeFiles/libserver_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : h_webserver/base/CMakeFiles/libserver_base.dir/depend

