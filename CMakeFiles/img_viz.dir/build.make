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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/david/Projects/img_viz

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/david/Projects/img_viz

# Include any dependencies generated for this target.
include CMakeFiles/img_viz.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/img_viz.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/img_viz.dir/flags.make

CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.o: CMakeFiles/img_viz.dir/flags.make
CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.o: img_viz_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Projects/img_viz/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.o -c /home/david/Projects/img_viz/img_viz_autogen/mocs_compilation.cpp

CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Projects/img_viz/img_viz_autogen/mocs_compilation.cpp > CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.i

CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Projects/img_viz/img_viz_autogen/mocs_compilation.cpp -o CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.s

CMakeFiles/img_viz.dir/src/main.cpp.o: CMakeFiles/img_viz.dir/flags.make
CMakeFiles/img_viz.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Projects/img_viz/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/img_viz.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/img_viz.dir/src/main.cpp.o -c /home/david/Projects/img_viz/src/main.cpp

CMakeFiles/img_viz.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/img_viz.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Projects/img_viz/src/main.cpp > CMakeFiles/img_viz.dir/src/main.cpp.i

CMakeFiles/img_viz.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/img_viz.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Projects/img_viz/src/main.cpp -o CMakeFiles/img_viz.dir/src/main.cpp.s

CMakeFiles/img_viz.dir/src/mainwindow.cpp.o: CMakeFiles/img_viz.dir/flags.make
CMakeFiles/img_viz.dir/src/mainwindow.cpp.o: src/mainwindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/david/Projects/img_viz/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/img_viz.dir/src/mainwindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/img_viz.dir/src/mainwindow.cpp.o -c /home/david/Projects/img_viz/src/mainwindow.cpp

CMakeFiles/img_viz.dir/src/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/img_viz.dir/src/mainwindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/david/Projects/img_viz/src/mainwindow.cpp > CMakeFiles/img_viz.dir/src/mainwindow.cpp.i

CMakeFiles/img_viz.dir/src/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/img_viz.dir/src/mainwindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/david/Projects/img_viz/src/mainwindow.cpp -o CMakeFiles/img_viz.dir/src/mainwindow.cpp.s

# Object files for target img_viz
img_viz_OBJECTS = \
"CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/img_viz.dir/src/main.cpp.o" \
"CMakeFiles/img_viz.dir/src/mainwindow.cpp.o"

# External object files for target img_viz
img_viz_EXTERNAL_OBJECTS =

img_viz: CMakeFiles/img_viz.dir/img_viz_autogen/mocs_compilation.cpp.o
img_viz: CMakeFiles/img_viz.dir/src/main.cpp.o
img_viz: CMakeFiles/img_viz.dir/src/mainwindow.cpp.o
img_viz: CMakeFiles/img_viz.dir/build.make
img_viz: /usr/lib/libQt5Widgets.so.5.13.0
img_viz: /usr/lib/libQt5Gui.so.5.13.0
img_viz: /usr/lib/libQt5Core.so.5.13.0
img_viz: CMakeFiles/img_viz.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/david/Projects/img_viz/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable img_viz"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/img_viz.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/img_viz.dir/build: img_viz

.PHONY : CMakeFiles/img_viz.dir/build

CMakeFiles/img_viz.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/img_viz.dir/cmake_clean.cmake
.PHONY : CMakeFiles/img_viz.dir/clean

CMakeFiles/img_viz.dir/depend:
	cd /home/david/Projects/img_viz && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/david/Projects/img_viz /home/david/Projects/img_viz /home/david/Projects/img_viz /home/david/Projects/img_viz /home/david/Projects/img_viz/CMakeFiles/img_viz.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/img_viz.dir/depend

