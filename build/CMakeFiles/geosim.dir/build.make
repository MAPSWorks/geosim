# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/hollan/dev/openglproj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hollan/dev/openglproj/build

# Include any dependencies generated for this target.
include CMakeFiles/geosim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/geosim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/geosim.dir/flags.make

CMakeFiles/geosim.dir/src/glad.c.o: CMakeFiles/geosim.dir/flags.make
CMakeFiles/geosim.dir/src/glad.c.o: ../src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hollan/dev/openglproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/geosim.dir/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/geosim.dir/src/glad.c.o   -c /home/hollan/dev/openglproj/src/glad.c

CMakeFiles/geosim.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/geosim.dir/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hollan/dev/openglproj/src/glad.c > CMakeFiles/geosim.dir/src/glad.c.i

CMakeFiles/geosim.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/geosim.dir/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hollan/dev/openglproj/src/glad.c -o CMakeFiles/geosim.dir/src/glad.c.s

CMakeFiles/geosim.dir/src/glad.c.o.requires:

.PHONY : CMakeFiles/geosim.dir/src/glad.c.o.requires

CMakeFiles/geosim.dir/src/glad.c.o.provides: CMakeFiles/geosim.dir/src/glad.c.o.requires
	$(MAKE) -f CMakeFiles/geosim.dir/build.make CMakeFiles/geosim.dir/src/glad.c.o.provides.build
.PHONY : CMakeFiles/geosim.dir/src/glad.c.o.provides

CMakeFiles/geosim.dir/src/glad.c.o.provides.build: CMakeFiles/geosim.dir/src/glad.c.o


CMakeFiles/geosim.dir/src/main.cpp.o: CMakeFiles/geosim.dir/flags.make
CMakeFiles/geosim.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hollan/dev/openglproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/geosim.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/geosim.dir/src/main.cpp.o -c /home/hollan/dev/openglproj/src/main.cpp

CMakeFiles/geosim.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/geosim.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hollan/dev/openglproj/src/main.cpp > CMakeFiles/geosim.dir/src/main.cpp.i

CMakeFiles/geosim.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/geosim.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hollan/dev/openglproj/src/main.cpp -o CMakeFiles/geosim.dir/src/main.cpp.s

CMakeFiles/geosim.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/geosim.dir/src/main.cpp.o.requires

CMakeFiles/geosim.dir/src/main.cpp.o.provides: CMakeFiles/geosim.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/geosim.dir/build.make CMakeFiles/geosim.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/geosim.dir/src/main.cpp.o.provides

CMakeFiles/geosim.dir/src/main.cpp.o.provides.build: CMakeFiles/geosim.dir/src/main.cpp.o


CMakeFiles/geosim.dir/src/shader.cpp.o: CMakeFiles/geosim.dir/flags.make
CMakeFiles/geosim.dir/src/shader.cpp.o: ../src/shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hollan/dev/openglproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/geosim.dir/src/shader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/geosim.dir/src/shader.cpp.o -c /home/hollan/dev/openglproj/src/shader.cpp

CMakeFiles/geosim.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/geosim.dir/src/shader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hollan/dev/openglproj/src/shader.cpp > CMakeFiles/geosim.dir/src/shader.cpp.i

CMakeFiles/geosim.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/geosim.dir/src/shader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hollan/dev/openglproj/src/shader.cpp -o CMakeFiles/geosim.dir/src/shader.cpp.s

CMakeFiles/geosim.dir/src/shader.cpp.o.requires:

.PHONY : CMakeFiles/geosim.dir/src/shader.cpp.o.requires

CMakeFiles/geosim.dir/src/shader.cpp.o.provides: CMakeFiles/geosim.dir/src/shader.cpp.o.requires
	$(MAKE) -f CMakeFiles/geosim.dir/build.make CMakeFiles/geosim.dir/src/shader.cpp.o.provides.build
.PHONY : CMakeFiles/geosim.dir/src/shader.cpp.o.provides

CMakeFiles/geosim.dir/src/shader.cpp.o.provides.build: CMakeFiles/geosim.dir/src/shader.cpp.o


CMakeFiles/geosim.dir/src/stb_image.cpp.o: CMakeFiles/geosim.dir/flags.make
CMakeFiles/geosim.dir/src/stb_image.cpp.o: ../src/stb_image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hollan/dev/openglproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/geosim.dir/src/stb_image.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/geosim.dir/src/stb_image.cpp.o -c /home/hollan/dev/openglproj/src/stb_image.cpp

CMakeFiles/geosim.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/geosim.dir/src/stb_image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hollan/dev/openglproj/src/stb_image.cpp > CMakeFiles/geosim.dir/src/stb_image.cpp.i

CMakeFiles/geosim.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/geosim.dir/src/stb_image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hollan/dev/openglproj/src/stb_image.cpp -o CMakeFiles/geosim.dir/src/stb_image.cpp.s

CMakeFiles/geosim.dir/src/stb_image.cpp.o.requires:

.PHONY : CMakeFiles/geosim.dir/src/stb_image.cpp.o.requires

CMakeFiles/geosim.dir/src/stb_image.cpp.o.provides: CMakeFiles/geosim.dir/src/stb_image.cpp.o.requires
	$(MAKE) -f CMakeFiles/geosim.dir/build.make CMakeFiles/geosim.dir/src/stb_image.cpp.o.provides.build
.PHONY : CMakeFiles/geosim.dir/src/stb_image.cpp.o.provides

CMakeFiles/geosim.dir/src/stb_image.cpp.o.provides.build: CMakeFiles/geosim.dir/src/stb_image.cpp.o


# Object files for target geosim
geosim_OBJECTS = \
"CMakeFiles/geosim.dir/src/glad.c.o" \
"CMakeFiles/geosim.dir/src/main.cpp.o" \
"CMakeFiles/geosim.dir/src/shader.cpp.o" \
"CMakeFiles/geosim.dir/src/stb_image.cpp.o"

# External object files for target geosim
geosim_EXTERNAL_OBJECTS =

geosim: CMakeFiles/geosim.dir/src/glad.c.o
geosim: CMakeFiles/geosim.dir/src/main.cpp.o
geosim: CMakeFiles/geosim.dir/src/shader.cpp.o
geosim: CMakeFiles/geosim.dir/src/stb_image.cpp.o
geosim: CMakeFiles/geosim.dir/build.make
geosim: CMakeFiles/geosim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hollan/dev/openglproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable geosim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/geosim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/geosim.dir/build: geosim

.PHONY : CMakeFiles/geosim.dir/build

CMakeFiles/geosim.dir/requires: CMakeFiles/geosim.dir/src/glad.c.o.requires
CMakeFiles/geosim.dir/requires: CMakeFiles/geosim.dir/src/main.cpp.o.requires
CMakeFiles/geosim.dir/requires: CMakeFiles/geosim.dir/src/shader.cpp.o.requires
CMakeFiles/geosim.dir/requires: CMakeFiles/geosim.dir/src/stb_image.cpp.o.requires

.PHONY : CMakeFiles/geosim.dir/requires

CMakeFiles/geosim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/geosim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/geosim.dir/clean

CMakeFiles/geosim.dir/depend:
	cd /home/hollan/dev/openglproj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hollan/dev/openglproj /home/hollan/dev/openglproj /home/hollan/dev/openglproj/build /home/hollan/dev/openglproj/build /home/hollan/dev/openglproj/build/CMakeFiles/geosim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/geosim.dir/depend

