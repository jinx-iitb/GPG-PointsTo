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
CMAKE_COMMAND = /home/jinx/IDE/clion-2020.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/jinx/IDE/clion-2020.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug

# Include any dependencies generated for this target.
include test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/depend.make

# Include the progress variables for this target.
include test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/progress.make

# Include the compile flags for this target's objects.
include test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/flags.make

test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.o: test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/flags.make
test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.o: ../test-slim/spatial/lib/Worklist/Worklist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Worklist.dir/Worklist.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/spatial/lib/Worklist/Worklist.cpp

test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Worklist.dir/Worklist.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/spatial/lib/Worklist/Worklist.cpp > CMakeFiles/Worklist.dir/Worklist.cpp.i

test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Worklist.dir/Worklist.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/spatial/lib/Worklist/Worklist.cpp -o CMakeFiles/Worklist.dir/Worklist.cpp.s

Worklist: test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.o
Worklist: test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/build.make

.PHONY : Worklist

# Rule to build all files generated by this target.
test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/build: Worklist

.PHONY : test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/build

test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/clean:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist && $(CMAKE_COMMAND) -P CMakeFiles/Worklist.dir/cmake_clean.cmake
.PHONY : test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/clean

test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/depend:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/spatial/lib/Worklist /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/depend

