# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_SOURCE_DIR = /home/antony_c/AJC/PROGRAM_C/PieChartProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antony_c/AJC/PROGRAM_C/PieChartProject/build

# Include any dependencies generated for this target.
include CMakeFiles/PieChart.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PieChart.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PieChart.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PieChart.dir/flags.make

CMakeFiles/PieChart.dir/main.c.o: CMakeFiles/PieChart.dir/flags.make
CMakeFiles/PieChart.dir/main.c.o: /home/antony_c/AJC/PROGRAM_C/PieChartProject/main.c
CMakeFiles/PieChart.dir/main.c.o: CMakeFiles/PieChart.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antony_c/AJC/PROGRAM_C/PieChartProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/PieChart.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PieChart.dir/main.c.o -MF CMakeFiles/PieChart.dir/main.c.o.d -o CMakeFiles/PieChart.dir/main.c.o -c /home/antony_c/AJC/PROGRAM_C/PieChartProject/main.c

CMakeFiles/PieChart.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PieChart.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/antony_c/AJC/PROGRAM_C/PieChartProject/main.c > CMakeFiles/PieChart.dir/main.c.i

CMakeFiles/PieChart.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PieChart.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/antony_c/AJC/PROGRAM_C/PieChartProject/main.c -o CMakeFiles/PieChart.dir/main.c.s

CMakeFiles/PieChart.dir/pie_chart.c.o: CMakeFiles/PieChart.dir/flags.make
CMakeFiles/PieChart.dir/pie_chart.c.o: /home/antony_c/AJC/PROGRAM_C/PieChartProject/pie_chart.c
CMakeFiles/PieChart.dir/pie_chart.c.o: CMakeFiles/PieChart.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/antony_c/AJC/PROGRAM_C/PieChartProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/PieChart.dir/pie_chart.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/PieChart.dir/pie_chart.c.o -MF CMakeFiles/PieChart.dir/pie_chart.c.o.d -o CMakeFiles/PieChart.dir/pie_chart.c.o -c /home/antony_c/AJC/PROGRAM_C/PieChartProject/pie_chart.c

CMakeFiles/PieChart.dir/pie_chart.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/PieChart.dir/pie_chart.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/antony_c/AJC/PROGRAM_C/PieChartProject/pie_chart.c > CMakeFiles/PieChart.dir/pie_chart.c.i

CMakeFiles/PieChart.dir/pie_chart.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/PieChart.dir/pie_chart.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/antony_c/AJC/PROGRAM_C/PieChartProject/pie_chart.c -o CMakeFiles/PieChart.dir/pie_chart.c.s

# Object files for target PieChart
PieChart_OBJECTS = \
"CMakeFiles/PieChart.dir/main.c.o" \
"CMakeFiles/PieChart.dir/pie_chart.c.o"

# External object files for target PieChart
PieChart_EXTERNAL_OBJECTS =

PieChart: CMakeFiles/PieChart.dir/main.c.o
PieChart: CMakeFiles/PieChart.dir/pie_chart.c.o
PieChart: CMakeFiles/PieChart.dir/build.make
PieChart: /usr/lib/x86_64-linux-gnu/libgd.so
PieChart: CMakeFiles/PieChart.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/antony_c/AJC/PROGRAM_C/PieChartProject/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable PieChart"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PieChart.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PieChart.dir/build: PieChart
.PHONY : CMakeFiles/PieChart.dir/build

CMakeFiles/PieChart.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PieChart.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PieChart.dir/clean

CMakeFiles/PieChart.dir/depend:
	cd /home/antony_c/AJC/PROGRAM_C/PieChartProject/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antony_c/AJC/PROGRAM_C/PieChartProject /home/antony_c/AJC/PROGRAM_C/PieChartProject /home/antony_c/AJC/PROGRAM_C/PieChartProject/build /home/antony_c/AJC/PROGRAM_C/PieChartProject/build /home/antony_c/AJC/PROGRAM_C/PieChartProject/build/CMakeFiles/PieChart.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PieChart.dir/depend

