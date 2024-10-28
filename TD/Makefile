# Define prefix for ARM toolchain
PREFIX = arm-none-eabi-

# Define the assembly, linker and debug commands
AS     = $(PREFIX)as
LD     = $(PREFIX)ld
GDB    = $(PREFIX)gdb
CC     = $(PREFIX)gcc
OCP    = $(PREFIX)objcopy

# Options for C, assembly, debug and linker commands
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -nostdlib -ffreestanding -DSTM32L475xx -I./CMSIS/Device/ST/STM32L4xx/Include -I./CMSIS/Include -Wall -Werror
CFLAGS = -c -g -O1 $(TARGET_ARCH)
ASFLAGS  = -g
LDFLAGS  = -T ld_ram.lds $(TARGET_ARCH)
GDBFLAGS = -x se203.gdb

# EXE = test.elf

# List of assembly source files
CFILES   = $(wildcard *.c)								# Get all .c files in the directory into an array
ASFILES  = $(wildcard *.s)								# Get all .s files in the directory into an array
OBJFILES = $(patsubst %.c,%.o,$(CFILES))				# Create corresponding .o files since .c files (search the files that finish in .c and replace .c by .o)
OBJFILES += $(patsubst %.s,%.o,$(ASFILES))				# Create corresponding .o files since .s files (search the files that finish in .s and replace .s by .o)
OBJFILES += image.o
#OBJFILES += clocks.o

TARGET   = main											# Name of the final executable

# Default target to build the executable
build: $(TARGET)										# Start point for build the project, the main objective

# Rule to compile the .c files into .o files
%.o:%.c
	$(CC) $(CFLAGS) $< -o $@

# Rule to assemble the .s files into .o files
%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.o : %.raw
	$(OCP) -I binary -O elf32-littlearm -B arm $^ $@

# Rule to link the .o files into the final executable main
$(TARGET): $(OBJFILES)									# Define the main file (TARGET) with the de dependeces (OBJFILES)
	$(CC) $(LDFLAGS) $(OBJFILES) -o $(TARGET)

.PHONY: build connect debug clean						# Declare that build, connect, debug and clean are targets, not real files, this for execute the rules related to this targets without trying to search the files

connect:												# Boot the JLinkGDBServer driver with a specific set up for a device STM32L475VG
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:													# Boot the debugger loading commands since the se203.gdb file
	$(GDB) $(GDBFLAGS) $(TARGET)

clean:													# Clean the .elf files generated, this is useful for keep the directory clean before a new execution
	rm -f $(OBJFILES) $(TARGET)
