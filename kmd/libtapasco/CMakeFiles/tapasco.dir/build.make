# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stud/lt25geja/juli/tapasco/runtime

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stud/lt25geja/juli/tapasco/workdir/build

# Include any dependencies generated for this target.
include libtapasco/CMakeFiles/tapasco.dir/depend.make

# Include the progress variables for this target.
include libtapasco/CMakeFiles/tapasco.dir/progress.make

# Include the compile flags for this target's objects.
include libtapasco/CMakeFiles/tapasco.dir/flags.make

libtapasco/unused.c:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/stud/lt25geja/juli/tapasco/workdir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Creating dummy file to force build"
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && echo  | tee /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/unused.c

libtapasco/CMakeFiles/tapasco.dir/unused.c.o: libtapasco/CMakeFiles/tapasco.dir/flags.make
libtapasco/CMakeFiles/tapasco.dir/unused.c.o: libtapasco/unused.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stud/lt25geja/juli/tapasco/workdir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object libtapasco/CMakeFiles/tapasco.dir/unused.c.o"
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && /usr/lib64/ccache/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tapasco.dir/unused.c.o   -c /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/unused.c

libtapasco/CMakeFiles/tapasco.dir/unused.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tapasco.dir/unused.c.i"
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && /usr/lib64/ccache/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/unused.c > CMakeFiles/tapasco.dir/unused.c.i

libtapasco/CMakeFiles/tapasco.dir/unused.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tapasco.dir/unused.c.s"
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && /usr/lib64/ccache/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/unused.c -o CMakeFiles/tapasco.dir/unused.c.s

# Object files for target tapasco
tapasco_OBJECTS = \
"CMakeFiles/tapasco.dir/unused.c.o"

# External object files for target tapasco
tapasco_EXTERNAL_OBJECTS =

libtapasco/libtapasco.a: libtapasco/CMakeFiles/tapasco.dir/unused.c.o
libtapasco/libtapasco.a: libtapasco/CMakeFiles/tapasco.dir/build.make
libtapasco/libtapasco.a: libtapasco/CMakeFiles/tapasco.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stud/lt25geja/juli/tapasco/workdir/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libtapasco.a"
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && $(CMAKE_COMMAND) -P CMakeFiles/tapasco.dir/cmake_clean_target.cmake
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tapasco.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Replacing libtapasco.a"
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && /usr/bin/cmake -E copy /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/release/libtapasco.a /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && /usr/bin/cmake -E remove -f /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/unused.c

# Rule to build all files generated by this target.
libtapasco/CMakeFiles/tapasco.dir/build: libtapasco/libtapasco.a

.PHONY : libtapasco/CMakeFiles/tapasco.dir/build

libtapasco/CMakeFiles/tapasco.dir/clean:
	cd /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco && $(CMAKE_COMMAND) -P CMakeFiles/tapasco.dir/cmake_clean.cmake
.PHONY : libtapasco/CMakeFiles/tapasco.dir/clean

libtapasco/CMakeFiles/tapasco.dir/depend: libtapasco/unused.c
	cd /home/stud/lt25geja/juli/tapasco/workdir/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stud/lt25geja/juli/tapasco/runtime /home/stud/lt25geja/juli/tapasco/runtime/libtapasco /home/stud/lt25geja/juli/tapasco/workdir/build /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco /home/stud/lt25geja/juli/tapasco/workdir/build/libtapasco/CMakeFiles/tapasco.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : libtapasco/CMakeFiles/tapasco.dir/depend
