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
include CMakeFiles/main.out.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/main.out.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.out.dir/flags.make

CMakeFiles/main.out.dir/project/cmd/src/main.c.o: CMakeFiles/main.out.dir/flags.make
CMakeFiles/main.out.dir/project/cmd/src/main.c.o: ../project/cmd/src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.out.dir/project/cmd/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/main.out.dir/project/cmd/src/main.c.o -c /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/project/cmd/src/main.c

CMakeFiles/main.out.dir/project/cmd/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.out.dir/project/cmd/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/project/cmd/src/main.c > CMakeFiles/main.out.dir/project/cmd/src/main.c.i

CMakeFiles/main.out.dir/project/cmd/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.out.dir/project/cmd/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/project/cmd/src/main.c -o CMakeFiles/main.out.dir/project/cmd/src/main.c.s

# Object files for target main.out
main_out_OBJECTS = \
"CMakeFiles/main.out.dir/project/cmd/src/main.c.o"

# External object files for target main.out
main_out_EXTERNAL_OBJECTS =

main.out: CMakeFiles/main.out.dir/project/cmd/src/main.c.o
main.out: CMakeFiles/main.out.dir/build.make
main.out: libmenu.a
main.out: libdynamic_task.so
main.out: CMakeFiles/main.out.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable main.out"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main.out.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.out.dir/build: main.out
.PHONY : CMakeFiles/main.out.dir/build

CMakeFiles/main.out.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main.out.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main.out.dir/clean

CMakeFiles/main.out.dir/depend:
	cd /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug /home/andrew/Technopark/Cxx/cpp-hw-2-hw_processing/cmake-build-debug/CMakeFiles/main.out.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.out.dir/depend
