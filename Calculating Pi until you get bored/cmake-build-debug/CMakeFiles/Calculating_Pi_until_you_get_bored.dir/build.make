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
CMAKE_COMMAND = /snap/clion/164/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/164/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Calculating_Pi_until_you_get_bored.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Calculating_Pi_until_you_get_bored.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Calculating_Pi_until_you_get_bored.dir/flags.make

CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.o: CMakeFiles/Calculating_Pi_until_you_get_bored.dir/flags.make
CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.o -c "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/main.c"

CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/main.c" > CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.i

CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/main.c" -o CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.s

# Object files for target Calculating_Pi_until_you_get_bored
Calculating_Pi_until_you_get_bored_OBJECTS = \
"CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.o"

# External object files for target Calculating_Pi_until_you_get_bored
Calculating_Pi_until_you_get_bored_EXTERNAL_OBJECTS =

Calculating_Pi_until_you_get_bored: CMakeFiles/Calculating_Pi_until_you_get_bored.dir/main.c.o
Calculating_Pi_until_you_get_bored: CMakeFiles/Calculating_Pi_until_you_get_bored.dir/build.make
Calculating_Pi_until_you_get_bored: CMakeFiles/Calculating_Pi_until_you_get_bored.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Calculating_Pi_until_you_get_bored"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Calculating_Pi_until_you_get_bored.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Calculating_Pi_until_you_get_bored.dir/build: Calculating_Pi_until_you_get_bored
.PHONY : CMakeFiles/Calculating_Pi_until_you_get_bored.dir/build

CMakeFiles/Calculating_Pi_until_you_get_bored.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Calculating_Pi_until_you_get_bored.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Calculating_Pi_until_you_get_bored.dir/clean

CMakeFiles/Calculating_Pi_until_you_get_bored.dir/depend:
	cd "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored" "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored" "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug" "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug" "/home/andrey/GIT/operating-system-labs-2/Calculating Pi until you get bored/cmake-build-debug/CMakeFiles/Calculating_Pi_until_you_get_bored.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Calculating_Pi_until_you_get_bored.dir/depend

