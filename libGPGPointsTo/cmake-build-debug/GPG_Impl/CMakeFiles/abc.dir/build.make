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
include GPG_Impl/CMakeFiles/abc.dir/depend.make

# Include the progress variables for this target.
include GPG_Impl/CMakeFiles/abc.dir/progress.make

# Include the compile flags for this target's objects.
include GPG_Impl/CMakeFiles/abc.dir/flags.make

GPG_Impl/CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.o: ../GPG_Impl/src/FunctionWithGPG.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/FunctionWithGPG.cpp

GPG_Impl/CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/FunctionWithGPG.cpp > CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/FunctionWithGPG.cpp -o CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/Driver.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/Driver.cpp.o: ../GPG_Impl/src/Driver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/Driver.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/Driver.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Driver.cpp

GPG_Impl/CMakeFiles/abc.dir/src/Driver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/Driver.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Driver.cpp > CMakeFiles/abc.dir/src/Driver.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/Driver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/Driver.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Driver.cpp -o CMakeFiles/abc.dir/src/Driver.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/IndirectionList.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/IndirectionList.cpp.o: ../GPG_Impl/src/IndirectionList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/IndirectionList.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/IndirectionList.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/IndirectionList.cpp

GPG_Impl/CMakeFiles/abc.dir/src/IndirectionList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/IndirectionList.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/IndirectionList.cpp > CMakeFiles/abc.dir/src/IndirectionList.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/IndirectionList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/IndirectionList.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/IndirectionList.cpp -o CMakeFiles/abc.dir/src/IndirectionList.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/Util.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/Util.cpp.o: ../GPG_Impl/src/Util.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/Util.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/Util.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Util.cpp

GPG_Impl/CMakeFiles/abc.dir/src/Util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/Util.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Util.cpp > CMakeFiles/abc.dir/src/Util.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/Util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/Util.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Util.cpp -o CMakeFiles/abc.dir/src/Util.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/GPG.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/GPG.cpp.o: ../GPG_Impl/src/GPG.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/GPG.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/GPG.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPG.cpp

GPG_Impl/CMakeFiles/abc.dir/src/GPG.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/GPG.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPG.cpp > CMakeFiles/abc.dir/src/GPG.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/GPG.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/GPG.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPG.cpp -o CMakeFiles/abc.dir/src/GPG.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/GPB.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/GPB.cpp.o: ../GPG_Impl/src/GPB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/GPB.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/GPB.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPB.cpp

GPG_Impl/CMakeFiles/abc.dir/src/GPB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/GPB.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPB.cpp > CMakeFiles/abc.dir/src/GPB.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/GPB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/GPB.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPB.cpp -o CMakeFiles/abc.dir/src/GPB.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/GPU.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/GPU.cpp.o: ../GPG_Impl/src/GPU.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/GPU.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/GPU.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPU.cpp

GPG_Impl/CMakeFiles/abc.dir/src/GPU.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/GPU.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPU.cpp > CMakeFiles/abc.dir/src/GPU.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/GPU.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/GPU.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/GPU.cpp -o CMakeFiles/abc.dir/src/GPU.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/Partition.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/Partition.cpp.o: ../GPG_Impl/src/Partition.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/Partition.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/Partition.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Partition.cpp

GPG_Impl/CMakeFiles/abc.dir/src/Partition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/Partition.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Partition.cpp > CMakeFiles/abc.dir/src/Partition.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/Partition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/Partition.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/Partition.cpp -o CMakeFiles/abc.dir/src/Partition.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/TestCase.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/TestCase.cpp.o: ../GPG_Impl/src/TestCase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/TestCase.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/TestCase.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/TestCase.cpp

GPG_Impl/CMakeFiles/abc.dir/src/TestCase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/TestCase.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/TestCase.cpp > CMakeFiles/abc.dir/src/TestCase.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/TestCase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/TestCase.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/TestCase.cpp -o CMakeFiles/abc.dir/src/TestCase.cpp.s

GPG_Impl/CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.o: GPG_Impl/CMakeFiles/abc.dir/flags.make
GPG_Impl/CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.o: ../GPG_Impl/src/UpdatedCoalescing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object GPG_Impl/CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.o"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.o -c /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/UpdatedCoalescing.cpp

GPG_Impl/CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.i"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/UpdatedCoalescing.cpp > CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.i

GPG_Impl/CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.s"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl/src/UpdatedCoalescing.cpp -o CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.s

# Object files for target abc
abc_OBJECTS = \
"CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.o" \
"CMakeFiles/abc.dir/src/Driver.cpp.o" \
"CMakeFiles/abc.dir/src/IndirectionList.cpp.o" \
"CMakeFiles/abc.dir/src/Util.cpp.o" \
"CMakeFiles/abc.dir/src/GPG.cpp.o" \
"CMakeFiles/abc.dir/src/GPB.cpp.o" \
"CMakeFiles/abc.dir/src/GPU.cpp.o" \
"CMakeFiles/abc.dir/src/Partition.cpp.o" \
"CMakeFiles/abc.dir/src/TestCase.cpp.o" \
"CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.o"

# External object files for target abc
abc_EXTERNAL_OBJECTS =

lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/FunctionWithGPG.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/Driver.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/IndirectionList.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/Util.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/GPG.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/GPB.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/GPU.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/Partition.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/TestCase.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/src/UpdatedCoalescing.cpp.o
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/build.make
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMCore.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMSupport.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMIRReader.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMPasses.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMCodeGen.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMTarget.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMipo.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMIRReader.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMAsmParser.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMInstrumentation.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMScalarOpts.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMAggressiveInstCombine.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMInstCombine.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMVectorize.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMBitWriter.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMLinker.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMTransformUtils.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMAnalysis.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMObject.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMBitReader.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMMCParser.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMMC.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMDebugInfoCodeView.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMDebugInfoMSF.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMTextAPI.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMProfileData.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMCore.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMBinaryFormat.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMRemarks.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMBitstreamReader.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMSupport.a
lib/libabc.so: /usr/lib/llvm-10/lib/libLLVMDemangle.a
lib/libabc.so: GPG_Impl/CMakeFiles/abc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX shared library ../lib/libabc.so"
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/abc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
GPG_Impl/CMakeFiles/abc.dir/build: lib/libabc.so

.PHONY : GPG_Impl/CMakeFiles/abc.dir/build

GPG_Impl/CMakeFiles/abc.dir/clean:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl && $(CMAKE_COMMAND) -P CMakeFiles/abc.dir/cmake_clean.cmake
.PHONY : GPG_Impl/CMakeFiles/abc.dir/clean

GPG_Impl/CMakeFiles/abc.dir/depend:
	cd /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/GPG_Impl /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl /home/jinx/IITB/MTP/MTP-Main/libGPGPointsTo/cmake-build-debug/GPG_Impl/CMakeFiles/abc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : GPG_Impl/CMakeFiles/abc.dir/depend

