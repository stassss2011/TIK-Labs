# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /home/stas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6015.37/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/stas/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.6015.37/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stas/CLionProjects/tik_lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stas/CLionProjects/tik_lab1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/tik_lab1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tik_lab1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tik_lab1.dir/flags.make

CMakeFiles/tik_lab1.dir/main.cpp.o: CMakeFiles/tik_lab1.dir/flags.make
CMakeFiles/tik_lab1.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stas/CLionProjects/tik_lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tik_lab1.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tik_lab1.dir/main.cpp.o -c /home/stas/CLionProjects/tik_lab1/main.cpp

CMakeFiles/tik_lab1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tik_lab1.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stas/CLionProjects/tik_lab1/main.cpp > CMakeFiles/tik_lab1.dir/main.cpp.i

CMakeFiles/tik_lab1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tik_lab1.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stas/CLionProjects/tik_lab1/main.cpp -o CMakeFiles/tik_lab1.dir/main.cpp.s

# Object files for target tik_lab1
tik_lab1_OBJECTS = \
"CMakeFiles/tik_lab1.dir/main.cpp.o"

# External object files for target tik_lab1
tik_lab1_EXTERNAL_OBJECTS =

tik_lab1: CMakeFiles/tik_lab1.dir/main.cpp.o
tik_lab1: CMakeFiles/tik_lab1.dir/build.make
tik_lab1: CMakeFiles/tik_lab1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stas/CLionProjects/tik_lab1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tik_lab1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tik_lab1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tik_lab1.dir/build: tik_lab1

.PHONY : CMakeFiles/tik_lab1.dir/build

CMakeFiles/tik_lab1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tik_lab1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tik_lab1.dir/clean

CMakeFiles/tik_lab1.dir/depend:
	cd /home/stas/CLionProjects/tik_lab1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stas/CLionProjects/tik_lab1 /home/stas/CLionProjects/tik_lab1 /home/stas/CLionProjects/tik_lab1/cmake-build-debug /home/stas/CLionProjects/tik_lab1/cmake-build-debug /home/stas/CLionProjects/tik_lab1/cmake-build-debug/CMakeFiles/tik_lab1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tik_lab1.dir/depend

