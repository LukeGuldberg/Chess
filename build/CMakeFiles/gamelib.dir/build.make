# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.25

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\lukeg\code\Capstone\CHESS\Chess

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\lukeg\code\Capstone\CHESS\Chess\build

# Include any dependencies generated for this target.
include CMakeFiles/gamelib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gamelib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gamelib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gamelib.dir/flags.make

CMakeFiles/gamelib.dir/chessboard.cpp.obj: CMakeFiles/gamelib.dir/flags.make
CMakeFiles/gamelib.dir/chessboard.cpp.obj: CMakeFiles/gamelib.dir/includes_CXX.rsp
CMakeFiles/gamelib.dir/chessboard.cpp.obj: C:/Users/lukeg/code/Capstone/CHESS/Chess/chessboard.cpp
CMakeFiles/gamelib.dir/chessboard.cpp.obj: CMakeFiles/gamelib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukeg\code\Capstone\CHESS\Chess\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gamelib.dir/chessboard.cpp.obj"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gamelib.dir/chessboard.cpp.obj -MF CMakeFiles\gamelib.dir\chessboard.cpp.obj.d -o CMakeFiles\gamelib.dir\chessboard.cpp.obj -c C:\Users\lukeg\code\Capstone\CHESS\Chess\chessboard.cpp

CMakeFiles/gamelib.dir/chessboard.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gamelib.dir/chessboard.cpp.i"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukeg\code\Capstone\CHESS\Chess\chessboard.cpp > CMakeFiles\gamelib.dir\chessboard.cpp.i

CMakeFiles/gamelib.dir/chessboard.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gamelib.dir/chessboard.cpp.s"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\lukeg\code\Capstone\CHESS\Chess\chessboard.cpp -o CMakeFiles\gamelib.dir\chessboard.cpp.s

CMakeFiles/gamelib.dir/graphics.cpp.obj: CMakeFiles/gamelib.dir/flags.make
CMakeFiles/gamelib.dir/graphics.cpp.obj: CMakeFiles/gamelib.dir/includes_CXX.rsp
CMakeFiles/gamelib.dir/graphics.cpp.obj: C:/Users/lukeg/code/Capstone/CHESS/Chess/graphics.cpp
CMakeFiles/gamelib.dir/graphics.cpp.obj: CMakeFiles/gamelib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukeg\code\Capstone\CHESS\Chess\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gamelib.dir/graphics.cpp.obj"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gamelib.dir/graphics.cpp.obj -MF CMakeFiles\gamelib.dir\graphics.cpp.obj.d -o CMakeFiles\gamelib.dir\graphics.cpp.obj -c C:\Users\lukeg\code\Capstone\CHESS\Chess\graphics.cpp

CMakeFiles/gamelib.dir/graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gamelib.dir/graphics.cpp.i"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukeg\code\Capstone\CHESS\Chess\graphics.cpp > CMakeFiles\gamelib.dir\graphics.cpp.i

CMakeFiles/gamelib.dir/graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gamelib.dir/graphics.cpp.s"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\lukeg\code\Capstone\CHESS\Chess\graphics.cpp -o CMakeFiles\gamelib.dir\graphics.cpp.s

CMakeFiles/gamelib.dir/piece.cpp.obj: CMakeFiles/gamelib.dir/flags.make
CMakeFiles/gamelib.dir/piece.cpp.obj: CMakeFiles/gamelib.dir/includes_CXX.rsp
CMakeFiles/gamelib.dir/piece.cpp.obj: C:/Users/lukeg/code/Capstone/CHESS/Chess/piece.cpp
CMakeFiles/gamelib.dir/piece.cpp.obj: CMakeFiles/gamelib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\lukeg\code\Capstone\CHESS\Chess\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gamelib.dir/piece.cpp.obj"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gamelib.dir/piece.cpp.obj -MF CMakeFiles\gamelib.dir\piece.cpp.obj.d -o CMakeFiles\gamelib.dir\piece.cpp.obj -c C:\Users\lukeg\code\Capstone\CHESS\Chess\piece.cpp

CMakeFiles/gamelib.dir/piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gamelib.dir/piece.cpp.i"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\lukeg\code\Capstone\CHESS\Chess\piece.cpp > CMakeFiles\gamelib.dir\piece.cpp.i

CMakeFiles/gamelib.dir/piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gamelib.dir/piece.cpp.s"
	C:\msys64\mingw64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\lukeg\code\Capstone\CHESS\Chess\piece.cpp -o CMakeFiles\gamelib.dir\piece.cpp.s

# Object files for target gamelib
gamelib_OBJECTS = \
"CMakeFiles/gamelib.dir/chessboard.cpp.obj" \
"CMakeFiles/gamelib.dir/graphics.cpp.obj" \
"CMakeFiles/gamelib.dir/piece.cpp.obj"

# External object files for target gamelib
gamelib_EXTERNAL_OBJECTS =

libgamelib.a: CMakeFiles/gamelib.dir/chessboard.cpp.obj
libgamelib.a: CMakeFiles/gamelib.dir/graphics.cpp.obj
libgamelib.a: CMakeFiles/gamelib.dir/piece.cpp.obj
libgamelib.a: CMakeFiles/gamelib.dir/build.make
libgamelib.a: CMakeFiles/gamelib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\lukeg\code\Capstone\CHESS\Chess\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libgamelib.a"
	$(CMAKE_COMMAND) -P CMakeFiles\gamelib.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gamelib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gamelib.dir/build: libgamelib.a
.PHONY : CMakeFiles/gamelib.dir/build

CMakeFiles/gamelib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\gamelib.dir\cmake_clean.cmake
.PHONY : CMakeFiles/gamelib.dir/clean

CMakeFiles/gamelib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\lukeg\code\Capstone\CHESS\Chess C:\Users\lukeg\code\Capstone\CHESS\Chess C:\Users\lukeg\code\Capstone\CHESS\Chess\build C:\Users\lukeg\code\Capstone\CHESS\Chess\build C:\Users\lukeg\code\Capstone\CHESS\Chess\build\CMakeFiles\gamelib.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gamelib.dir/depend

