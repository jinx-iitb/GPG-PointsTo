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
include test-slim/spatial/lib/CMakeFiles/Spatial.dir/depend.make

# Include the progress variables for this target.
include test-slim/spatial/lib/CMakeFiles/Spatial.dir/progress.make

# Include the compile flags for this target's objects.
include test-slim/spatial/lib/CMakeFiles/Spatial.dir/flags.make

# Object files for target Spatial
Spatial_OBJECTS =

# External object files for target Spatial
Spatial_EXTERNAL_OBJECTS = \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Token/CMakeFiles/Token.dir/Token.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Token/CMakeFiles/Token.dir/TokenWrapper.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Benchmark/CMakeFiles/Benchmark.dir/PointsToBenchmark.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Benchmark/CMakeFiles/Benchmark.dir/PTABenchmark.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/InstInfo/CMakeFiles/InstInfo.dir/InstInfo.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/InstModel/CMakeFiles/InstModel.dir/InstModel.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/InstModel/GenericInstModel/CMakeFiles/GenericInstModel.dir/GenericInstModel.cpp.o" \
"/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/InstModel/LFCPAInstModel/CMakeFiles/LFCPAInstModel.dir/LFCPAInstModel.cpp.o"

lib/libSpatial.so.0: test-slim/spatial/lib/Token/CMakeFiles/Token.dir/Token.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/Token/CMakeFiles/Token.dir/TokenWrapper.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/Benchmark/CMakeFiles/Benchmark.dir/PointsToBenchmark.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/Benchmark/CMakeFiles/Benchmark.dir/PTABenchmark.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/Worklist/CMakeFiles/Worklist.dir/Worklist.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/InstInfo/CMakeFiles/InstInfo.dir/InstInfo.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/InstModel/CMakeFiles/InstModel.dir/InstModel.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/InstModel/GenericInstModel/CMakeFiles/GenericInstModel.dir/GenericInstModel.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/InstModel/LFCPAInstModel/CMakeFiles/LFCPAInstModel.dir/LFCPAInstModel.cpp.o
lib/libSpatial.so.0: test-slim/spatial/lib/CMakeFiles/Spatial.dir/build.make
lib/libSpatial.so.0: test-slim/spatial/lib/CMakeFiles/Spatial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX shared library ../../../lib/libSpatial.so"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Spatial.dir/link.txt --verbose=$(VERBOSE)
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib && $(CMAKE_COMMAND) -E cmake_symlink_library ../../../lib/libSpatial.so.0 ../../../lib/libSpatial.so.0 ../../../lib/libSpatial.so

lib/libSpatial.so: lib/libSpatial.so.0
	@$(CMAKE_COMMAND) -E touch_nocreate lib/libSpatial.so

# Rule to build all files generated by this target.
test-slim/spatial/lib/CMakeFiles/Spatial.dir/build: lib/libSpatial.so

.PHONY : test-slim/spatial/lib/CMakeFiles/Spatial.dir/build

test-slim/spatial/lib/CMakeFiles/Spatial.dir/clean:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib && $(CMAKE_COMMAND) -P CMakeFiles/Spatial.dir/cmake_clean.cmake
.PHONY : test-slim/spatial/lib/CMakeFiles/Spatial.dir/clean

test-slim/spatial/lib/CMakeFiles/Spatial.dir/depend:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/test-slim/spatial/lib /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/test-slim/spatial/lib/CMakeFiles/Spatial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test-slim/spatial/lib/CMakeFiles/Spatial.dir/depend
