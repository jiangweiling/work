# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/zhengyuhong/cmake/t1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhengyuhong/cmake/t1

# Include any dependencies generated for this target.
include CMakeFiles/hello.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello.dir/flags.make

CMakeFiles/hello.dir/src/main.c.o: CMakeFiles/hello.dir/flags.make
CMakeFiles/hello.dir/src/main.c.o: src/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zhengyuhong/cmake/t1/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/hello.dir/src/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/hello.dir/src/main.c.o   -c /home/zhengyuhong/cmake/t1/src/main.c

CMakeFiles/hello.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello.dir/src/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/zhengyuhong/cmake/t1/src/main.c > CMakeFiles/hello.dir/src/main.c.i

CMakeFiles/hello.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello.dir/src/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/zhengyuhong/cmake/t1/src/main.c -o CMakeFiles/hello.dir/src/main.c.s

CMakeFiles/hello.dir/src/main.c.o.requires:
.PHONY : CMakeFiles/hello.dir/src/main.c.o.requires

CMakeFiles/hello.dir/src/main.c.o.provides: CMakeFiles/hello.dir/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/hello.dir/build.make CMakeFiles/hello.dir/src/main.c.o.provides.build
.PHONY : CMakeFiles/hello.dir/src/main.c.o.provides

CMakeFiles/hello.dir/src/main.c.o.provides.build: CMakeFiles/hello.dir/src/main.c.o

# Object files for target hello
hello_OBJECTS = \
"CMakeFiles/hello.dir/src/main.c.o"

# External object files for target hello
hello_EXTERNAL_OBJECTS =

hello: CMakeFiles/hello.dir/src/main.c.o
hello: CMakeFiles/hello.dir/build.make
hello: CMakeFiles/hello.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable hello"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello.dir/build: hello
.PHONY : CMakeFiles/hello.dir/build

CMakeFiles/hello.dir/requires: CMakeFiles/hello.dir/src/main.c.o.requires
.PHONY : CMakeFiles/hello.dir/requires

CMakeFiles/hello.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello.dir/clean

CMakeFiles/hello.dir/depend:
	cd /home/zhengyuhong/cmake/t1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhengyuhong/cmake/t1 /home/zhengyuhong/cmake/t1 /home/zhengyuhong/cmake/t1 /home/zhengyuhong/cmake/t1 /home/zhengyuhong/cmake/t1/CMakeFiles/hello.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello.dir/depend

