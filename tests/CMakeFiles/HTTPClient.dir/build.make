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
CMAKE_SOURCE_DIR = /home/tt/web_server/h_webserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tt/web_server

# Include any dependencies generated for this target.
include tests/CMakeFiles/HTTPClient.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/HTTPClient.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/HTTPClient.dir/flags.make

tests/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o: tests/CMakeFiles/HTTPClient.dir/flags.make
tests/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o: h_webserver/tests/HTTPClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tt/web_server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o"
	cd /home/tt/web_server/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o -c /home/tt/web_server/h_webserver/tests/HTTPClient.cpp

tests/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HTTPClient.dir/HTTPClient.cpp.i"
	cd /home/tt/web_server/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tt/web_server/h_webserver/tests/HTTPClient.cpp > CMakeFiles/HTTPClient.dir/HTTPClient.cpp.i

tests/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HTTPClient.dir/HTTPClient.cpp.s"
	cd /home/tt/web_server/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tt/web_server/h_webserver/tests/HTTPClient.cpp -o CMakeFiles/HTTPClient.dir/HTTPClient.cpp.s

# Object files for target HTTPClient
HTTPClient_OBJECTS = \
"CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o"

# External object files for target HTTPClient
HTTPClient_EXTERNAL_OBJECTS =

tests/HTTPClient: tests/CMakeFiles/HTTPClient.dir/HTTPClient.cpp.o
tests/HTTPClient: tests/CMakeFiles/HTTPClient.dir/build.make
tests/HTTPClient: tests/CMakeFiles/HTTPClient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tt/web_server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HTTPClient"
	cd /home/tt/web_server/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HTTPClient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/HTTPClient.dir/build: tests/HTTPClient

.PHONY : tests/CMakeFiles/HTTPClient.dir/build

tests/CMakeFiles/HTTPClient.dir/clean:
	cd /home/tt/web_server/tests && $(CMAKE_COMMAND) -P CMakeFiles/HTTPClient.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/HTTPClient.dir/clean

tests/CMakeFiles/HTTPClient.dir/depend:
	cd /home/tt/web_server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tt/web_server/h_webserver /home/tt/web_server/h_webserver/tests /home/tt/web_server /home/tt/web_server/tests /home/tt/web_server/tests/CMakeFiles/HTTPClient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/HTTPClient.dir/depend

