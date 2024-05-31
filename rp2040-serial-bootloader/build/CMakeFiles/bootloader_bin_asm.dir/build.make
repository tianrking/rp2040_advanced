# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build

# Utility rule file for bootloader_bin_asm.

# Include any custom commands dependencies for this target.
include CMakeFiles/bootloader_bin_asm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bootloader_bin_asm.dir/progress.make

CMakeFiles/bootloader_bin_asm: bootloader_bin.S

bootloader_bin.S: bootloader.bin
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating bootloader_bin.S"
	/usr/bin/python3.12 /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/mkasm.py /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/bootloader.bin /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/bootloader_bin.S

bootloader.bin: bootloader.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating bootloader.bin"
	/opt/gcc-arm-none-eabi-9-2020-q2-update/bin/arm-none-eabi-objcopy -Obinary /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/bootloader.elf /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/bootloader.bin

bootloader_bin_asm: CMakeFiles/bootloader_bin_asm
bootloader_bin_asm: bootloader.bin
bootloader_bin_asm: bootloader_bin.S
bootloader_bin_asm: CMakeFiles/bootloader_bin_asm.dir/build.make
.PHONY : bootloader_bin_asm

# Rule to build all files generated by this target.
CMakeFiles/bootloader_bin_asm.dir/build: bootloader_bin_asm
.PHONY : CMakeFiles/bootloader_bin_asm.dir/build

CMakeFiles/bootloader_bin_asm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bootloader_bin_asm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bootloader_bin_asm.dir/clean

CMakeFiles/bootloader_bin_asm.dir/depend:
	cd /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build /home/w0x7ce/Desktop/RP2040_BOOTLOADER/rp2040-serial-bootloader/build/CMakeFiles/bootloader_bin_asm.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/bootloader_bin_asm.dir/depend
