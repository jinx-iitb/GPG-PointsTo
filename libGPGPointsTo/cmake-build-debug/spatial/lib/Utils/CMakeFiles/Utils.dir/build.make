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
include spatial/lib/Utils/CMakeFiles/Utils.dir/depend.make

# Include the progress variables for this target.
include spatial/lib/Utils/CMakeFiles/Utils.dir/progress.make

# Include the compile flags for this target's objects.
include spatial/lib/Utils/CMakeFiles/Utils.dir/flags.make

spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.o: spatial/lib/Utils/CMakeFiles/Utils.dir/flags.make
spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.o: ../spatial/lib/Utils/CFGUtils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/CFGUtils.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils/CFGUtils.cpp

spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/CFGUtils.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils/CFGUtils.cpp > CMakeFiles/Utils.dir/CFGUtils.cpp.i

spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/CFGUtils.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils/CFGUtils.cpp -o CMakeFiles/Utils.dir/CFGUtils.cpp.s

spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o: spatial/lib/Utils/CMakeFiles/Utils.dir/flags.make
spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o: ../spatial/lib/Utils/ReplaceIRVar.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils/ReplaceIRVar.cpp

spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Utils.dir/ReplaceIRVar.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils/ReplaceIRVar.cpp > CMakeFiles/Utils.dir/ReplaceIRVar.cpp.i

spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Utils.dir/ReplaceIRVar.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils/ReplaceIRVar.cpp -o CMakeFiles/Utils.dir/ReplaceIRVar.cpp.s

Utils: spatial/lib/Utils/CMakeFiles/Utils.dir/CFGUtils.cpp.o
Utils: spatial/lib/Utils/CMakeFiles/Utils.dir/ReplaceIRVar.cpp.o
Utils: spatial/lib/Utils/CMakeFiles/Utils.dir/build.make

.PHONY : Utils

# Rule to build all files generated by this target.
spatial/lib/Utils/CMakeFiles/Utils.dir/build: Utils

.PHONY : spatial/lib/Utils/CMakeFiles/Utils.dir/build

spatial/lib/Utils/CMakeFiles/Utils.dir/clean:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils && $(CMAKE_COMMAND) -P CMakeFiles/Utils.dir/cmake_clean.cmake
.PHONY : spatial/lib/Utils/CMakeFiles/Utils.dir/clean

spatial/lib/Utils/CMakeFiles/Utils.dir/depend:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/spatial/lib/Utils /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/spatial/lib/Utils/CMakeFiles/Utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : spatial/lib/Utils/CMakeFiles/Utils.dir/depend

