# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/169/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/169/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/test.out.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/test.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.out.dir/flags.make

CMakeFiles/test.out.dir/test/main.cpp.o: CMakeFiles/test.out.dir/flags.make
CMakeFiles/test.out.dir/test/main.cpp.o: ../test/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.out.dir/test/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test.out.dir/test/main.cpp.o -c /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/test/main.cpp

CMakeFiles/test.out.dir/test/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.out.dir/test/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/test/main.cpp > CMakeFiles/test.out.dir/test/main.cpp.i

CMakeFiles/test.out.dir/test/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.out.dir/test/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/test/main.cpp -o CMakeFiles/test.out.dir/test/main.cpp.s

# Object files for target test.out
test_out_OBJECTS = \
"CMakeFiles/test.out.dir/test/main.cpp.o"

# External object files for target test.out
test_out_EXTERNAL_OBJECTS =

test.out: CMakeFiles/test.out.dir/test/main.cpp.o
test.out: CMakeFiles/test.out.dir/build.make
test.out: libdynamic_task.so
test.out: /usr/local/lib/libgtest.a
test.out: CMakeFiles/test.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.out.dir/build: test.out
.PHONY : CMakeFiles/test.out.dir/build

CMakeFiles/test.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.out.dir/clean

CMakeFiles/test.out.dir/depend:
	cd /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug/CMakeFiles/test.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.out.dir/depend
