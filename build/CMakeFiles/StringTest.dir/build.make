# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/po4k/homework_2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/po4k/homework_2/build

# Include any dependencies generated for this target.
include CMakeFiles/StringTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/StringTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/StringTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StringTest.dir/flags.make

CMakeFiles/StringTest.dir/codegen:
.PHONY : CMakeFiles/StringTest.dir/codegen

CMakeFiles/StringTest.dir/homework_2.cpp.o: CMakeFiles/StringTest.dir/flags.make
CMakeFiles/StringTest.dir/homework_2.cpp.o: /home/po4k/homework_2/homework_2.cpp
CMakeFiles/StringTest.dir/homework_2.cpp.o: CMakeFiles/StringTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/po4k/homework_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StringTest.dir/homework_2.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StringTest.dir/homework_2.cpp.o -MF CMakeFiles/StringTest.dir/homework_2.cpp.o.d -o CMakeFiles/StringTest.dir/homework_2.cpp.o -c /home/po4k/homework_2/homework_2.cpp

CMakeFiles/StringTest.dir/homework_2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/StringTest.dir/homework_2.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/po4k/homework_2/homework_2.cpp > CMakeFiles/StringTest.dir/homework_2.cpp.i

CMakeFiles/StringTest.dir/homework_2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/StringTest.dir/homework_2.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/po4k/homework_2/homework_2.cpp -o CMakeFiles/StringTest.dir/homework_2.cpp.s

CMakeFiles/StringTest.dir/StringTest.cpp.o: CMakeFiles/StringTest.dir/flags.make
CMakeFiles/StringTest.dir/StringTest.cpp.o: /home/po4k/homework_2/StringTest.cpp
CMakeFiles/StringTest.dir/StringTest.cpp.o: CMakeFiles/StringTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/po4k/homework_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/StringTest.dir/StringTest.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/StringTest.dir/StringTest.cpp.o -MF CMakeFiles/StringTest.dir/StringTest.cpp.o.d -o CMakeFiles/StringTest.dir/StringTest.cpp.o -c /home/po4k/homework_2/StringTest.cpp

CMakeFiles/StringTest.dir/StringTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/StringTest.dir/StringTest.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/po4k/homework_2/StringTest.cpp > CMakeFiles/StringTest.dir/StringTest.cpp.i

CMakeFiles/StringTest.dir/StringTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/StringTest.dir/StringTest.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/po4k/homework_2/StringTest.cpp -o CMakeFiles/StringTest.dir/StringTest.cpp.s

# Object files for target StringTest
StringTest_OBJECTS = \
"CMakeFiles/StringTest.dir/homework_2.cpp.o" \
"CMakeFiles/StringTest.dir/StringTest.cpp.o"

# External object files for target StringTest
StringTest_EXTERNAL_OBJECTS =

StringTest: CMakeFiles/StringTest.dir/homework_2.cpp.o
StringTest: CMakeFiles/StringTest.dir/StringTest.cpp.o
StringTest: CMakeFiles/StringTest.dir/build.make
StringTest: CMakeFiles/StringTest.dir/compiler_depend.ts
StringTest: /usr/lib/x86_64-linux-gnu/libgtest.a
StringTest: CMakeFiles/StringTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/po4k/homework_2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable StringTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StringTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StringTest.dir/build: StringTest
.PHONY : CMakeFiles/StringTest.dir/build

CMakeFiles/StringTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StringTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StringTest.dir/clean

CMakeFiles/StringTest.dir/depend:
	cd /home/po4k/homework_2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/po4k/homework_2 /home/po4k/homework_2 /home/po4k/homework_2/build /home/po4k/homework_2/build /home/po4k/homework_2/build/CMakeFiles/StringTest.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/StringTest.dir/depend

