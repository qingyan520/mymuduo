# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sjw/mymuduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sjw/mymuduo/build

# Include any dependencies generated for this target.
include CMakeFiles/mymuduo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mymuduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mymuduo.dir/flags.make

CMakeFiles/mymuduo.dir/Channel.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Channel.o: ../Channel.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mymuduo.dir/Channel.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Channel.o -c /home/sjw/mymuduo/Channel.cc

CMakeFiles/mymuduo.dir/Channel.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Channel.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/Channel.cc > CMakeFiles/mymuduo.dir/Channel.i

CMakeFiles/mymuduo.dir/Channel.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Channel.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/Channel.cc -o CMakeFiles/mymuduo.dir/Channel.s

CMakeFiles/mymuduo.dir/Channel.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/Channel.o.requires

CMakeFiles/mymuduo.dir/Channel.o.provides: CMakeFiles/mymuduo.dir/Channel.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/Channel.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/Channel.o.provides

CMakeFiles/mymuduo.dir/Channel.o.provides.build: CMakeFiles/mymuduo.dir/Channel.o


CMakeFiles/mymuduo.dir/Poller.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Poller.o: ../Poller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/mymuduo.dir/Poller.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Poller.o -c /home/sjw/mymuduo/Poller.cc

CMakeFiles/mymuduo.dir/Poller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Poller.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/Poller.cc > CMakeFiles/mymuduo.dir/Poller.i

CMakeFiles/mymuduo.dir/Poller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Poller.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/Poller.cc -o CMakeFiles/mymuduo.dir/Poller.s

CMakeFiles/mymuduo.dir/Poller.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/Poller.o.requires

CMakeFiles/mymuduo.dir/Poller.o.provides: CMakeFiles/mymuduo.dir/Poller.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/Poller.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/Poller.o.provides

CMakeFiles/mymuduo.dir/Poller.o.provides.build: CMakeFiles/mymuduo.dir/Poller.o


CMakeFiles/mymuduo.dir/Main.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Main.o: ../Main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/mymuduo.dir/Main.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Main.o -c /home/sjw/mymuduo/Main.cc

CMakeFiles/mymuduo.dir/Main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Main.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/Main.cc > CMakeFiles/mymuduo.dir/Main.i

CMakeFiles/mymuduo.dir/Main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Main.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/Main.cc -o CMakeFiles/mymuduo.dir/Main.s

CMakeFiles/mymuduo.dir/Main.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/Main.o.requires

CMakeFiles/mymuduo.dir/Main.o.provides: CMakeFiles/mymuduo.dir/Main.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/Main.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/Main.o.provides

CMakeFiles/mymuduo.dir/Main.o.provides.build: CMakeFiles/mymuduo.dir/Main.o


CMakeFiles/mymuduo.dir/EventLoop.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EventLoop.o: ../EventLoop.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/mymuduo.dir/EventLoop.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/EventLoop.o -c /home/sjw/mymuduo/EventLoop.cc

CMakeFiles/mymuduo.dir/EventLoop.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EventLoop.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/EventLoop.cc > CMakeFiles/mymuduo.dir/EventLoop.i

CMakeFiles/mymuduo.dir/EventLoop.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EventLoop.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/EventLoop.cc -o CMakeFiles/mymuduo.dir/EventLoop.s

CMakeFiles/mymuduo.dir/EventLoop.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/EventLoop.o.requires

CMakeFiles/mymuduo.dir/EventLoop.o.provides: CMakeFiles/mymuduo.dir/EventLoop.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/EventLoop.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/EventLoop.o.provides

CMakeFiles/mymuduo.dir/EventLoop.o.provides.build: CMakeFiles/mymuduo.dir/EventLoop.o


CMakeFiles/mymuduo.dir/CurrentThread.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/CurrentThread.o: ../CurrentThread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/mymuduo.dir/CurrentThread.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/CurrentThread.o -c /home/sjw/mymuduo/CurrentThread.cc

CMakeFiles/mymuduo.dir/CurrentThread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/CurrentThread.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/CurrentThread.cc > CMakeFiles/mymuduo.dir/CurrentThread.i

CMakeFiles/mymuduo.dir/CurrentThread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/CurrentThread.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/CurrentThread.cc -o CMakeFiles/mymuduo.dir/CurrentThread.s

CMakeFiles/mymuduo.dir/CurrentThread.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/CurrentThread.o.requires

CMakeFiles/mymuduo.dir/CurrentThread.o.provides: CMakeFiles/mymuduo.dir/CurrentThread.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/CurrentThread.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/CurrentThread.o.provides

CMakeFiles/mymuduo.dir/CurrentThread.o.provides.build: CMakeFiles/mymuduo.dir/CurrentThread.o


CMakeFiles/mymuduo.dir/EpollPoller.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/EpollPoller.o: ../EpollPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/mymuduo.dir/EpollPoller.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/EpollPoller.o -c /home/sjw/mymuduo/EpollPoller.cc

CMakeFiles/mymuduo.dir/EpollPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/EpollPoller.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/EpollPoller.cc > CMakeFiles/mymuduo.dir/EpollPoller.i

CMakeFiles/mymuduo.dir/EpollPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/EpollPoller.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/EpollPoller.cc -o CMakeFiles/mymuduo.dir/EpollPoller.s

CMakeFiles/mymuduo.dir/EpollPoller.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/EpollPoller.o.requires

CMakeFiles/mymuduo.dir/EpollPoller.o.provides: CMakeFiles/mymuduo.dir/EpollPoller.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/EpollPoller.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/EpollPoller.o.provides

CMakeFiles/mymuduo.dir/EpollPoller.o.provides.build: CMakeFiles/mymuduo.dir/EpollPoller.o


CMakeFiles/mymuduo.dir/DefaultPoller.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/DefaultPoller.o: ../DefaultPoller.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/mymuduo.dir/DefaultPoller.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/DefaultPoller.o -c /home/sjw/mymuduo/DefaultPoller.cc

CMakeFiles/mymuduo.dir/DefaultPoller.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/DefaultPoller.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/DefaultPoller.cc > CMakeFiles/mymuduo.dir/DefaultPoller.i

CMakeFiles/mymuduo.dir/DefaultPoller.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/DefaultPoller.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/DefaultPoller.cc -o CMakeFiles/mymuduo.dir/DefaultPoller.s

CMakeFiles/mymuduo.dir/DefaultPoller.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/DefaultPoller.o.requires

CMakeFiles/mymuduo.dir/DefaultPoller.o.provides: CMakeFiles/mymuduo.dir/DefaultPoller.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/DefaultPoller.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/DefaultPoller.o.provides

CMakeFiles/mymuduo.dir/DefaultPoller.o.provides.build: CMakeFiles/mymuduo.dir/DefaultPoller.o


CMakeFiles/mymuduo.dir/Thread.o: CMakeFiles/mymuduo.dir/flags.make
CMakeFiles/mymuduo.dir/Thread.o: ../Thread.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/mymuduo.dir/Thread.o"
	/opt/rh/devtoolset-7/root/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mymuduo.dir/Thread.o -c /home/sjw/mymuduo/Thread.cc

CMakeFiles/mymuduo.dir/Thread.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mymuduo.dir/Thread.i"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sjw/mymuduo/Thread.cc > CMakeFiles/mymuduo.dir/Thread.i

CMakeFiles/mymuduo.dir/Thread.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mymuduo.dir/Thread.s"
	/opt/rh/devtoolset-7/root/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sjw/mymuduo/Thread.cc -o CMakeFiles/mymuduo.dir/Thread.s

CMakeFiles/mymuduo.dir/Thread.o.requires:

.PHONY : CMakeFiles/mymuduo.dir/Thread.o.requires

CMakeFiles/mymuduo.dir/Thread.o.provides: CMakeFiles/mymuduo.dir/Thread.o.requires
	$(MAKE) -f CMakeFiles/mymuduo.dir/build.make CMakeFiles/mymuduo.dir/Thread.o.provides.build
.PHONY : CMakeFiles/mymuduo.dir/Thread.o.provides

CMakeFiles/mymuduo.dir/Thread.o.provides.build: CMakeFiles/mymuduo.dir/Thread.o


# Object files for target mymuduo
mymuduo_OBJECTS = \
"CMakeFiles/mymuduo.dir/Channel.o" \
"CMakeFiles/mymuduo.dir/Poller.o" \
"CMakeFiles/mymuduo.dir/Main.o" \
"CMakeFiles/mymuduo.dir/EventLoop.o" \
"CMakeFiles/mymuduo.dir/CurrentThread.o" \
"CMakeFiles/mymuduo.dir/EpollPoller.o" \
"CMakeFiles/mymuduo.dir/DefaultPoller.o" \
"CMakeFiles/mymuduo.dir/Thread.o"

# External object files for target mymuduo
mymuduo_EXTERNAL_OBJECTS =

../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Channel.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Poller.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Main.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EventLoop.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/CurrentThread.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/EpollPoller.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/DefaultPoller.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/Thread.o
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/build.make
../lib/libmymuduo.so: CMakeFiles/mymuduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sjw/mymuduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX shared library ../lib/libmymuduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mymuduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mymuduo.dir/build: ../lib/libmymuduo.so

.PHONY : CMakeFiles/mymuduo.dir/build

CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/Channel.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/Poller.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/Main.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/EventLoop.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/CurrentThread.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/EpollPoller.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/DefaultPoller.o.requires
CMakeFiles/mymuduo.dir/requires: CMakeFiles/mymuduo.dir/Thread.o.requires

.PHONY : CMakeFiles/mymuduo.dir/requires

CMakeFiles/mymuduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mymuduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mymuduo.dir/clean

CMakeFiles/mymuduo.dir/depend:
	cd /home/sjw/mymuduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sjw/mymuduo /home/sjw/mymuduo /home/sjw/mymuduo/build /home/sjw/mymuduo/build /home/sjw/mymuduo/build/CMakeFiles/mymuduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mymuduo.dir/depend

