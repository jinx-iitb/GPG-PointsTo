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
include test-slim/CMakeFiles/TransformIR.dir/depend.make

# Include the progress variables for this target.
include test-slim/CMakeFiles/TransformIR.dir/progress.make

# Include the compile flags for this target's objects.
include test-slim/CMakeFiles/TransformIR.dir/flags.make

test-slim/CMakeFiles/TransformIR.dir/TransformIR.cpp.o: test-slim/CMakeFiles/TransformIR.dir/flags.make
test-slim/CMakeFiles/TransformIR.dir/TransformIR.cpp.o: ../test-slim/TransformIR.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test-slim/CMakeFiles/TransformIR.dir/TransformIR.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TransformIR.dir/TransformIR.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/TransformIR.cpp

test-slim/CMakeFiles/TransformIR.dir/TransformIR.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TransformIR.dir/TransformIR.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/TransformIR.cpp > CMakeFiles/TransformIR.dir/TransformIR.cpp.i

test-slim/CMakeFiles/TransformIR.dir/TransformIR.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TransformIR.dir/TransformIR.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/TransformIR.cpp -o CMakeFiles/TransformIR.dir/TransformIR.cpp.s

TransformIR: test-slim/CMakeFiles/TransformIR.dir/TransformIR.cpp.o
TransformIR: test-slim/CMakeFiles/TransformIR.dir/build.make

.PHONY : TransformIR

# Rule to build all files generated by this target.
test-slim/CMakeFiles/TransformIR.dir/build: TransformIR

.PHONY : test-slim/CMakeFiles/TransformIR.dir/build

test-slim/CMakeFiles/TransformIR.dir/clean:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim && $(CMAKE_COMMAND) -P CMakeFiles/TransformIR.dir/cmake_clean.cmake
.PHONY : test-slim/CMakeFiles/TransformIR.dir/clean

test-slim/CMakeFiles/TransformIR.dir/depend:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/CMakeFiles/TransformIR.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test-slim/CMakeFiles/TransformIR.dir/depend

