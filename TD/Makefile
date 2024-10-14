# Define prefix for ARM toolchain
PREFIX=arm-none-eabi-

# Define the assembly, linker and debug commands
AS    = $(PREFIX)as
LD    = $(PREFIX)ld
GDB   = $(PREFIX)gdb

# Options for assembly, debug and linker commands
ASFLAGS  = -g
LDFLAGS  = -g
GDBFLAGS = -x se203.gdb

# EXE = test.elf

# List of assembly source files
ASFILES  = $(wildcard *.s)								# Get all .s files in the directory
ELFFILES = $(patsubst %.s,%.elf,$(ASFILES))				# Create corresponding .elf files, each assembly file will have his corresponding .elf file

# Default target to build all .elf files
all: $(ELFFILES)

# Rule to create the .o files since .f files
%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

# Rule to link .o files into .elf files
%.elf:%.o
	$(LD) $(LDFLAGS) $< -o $@

.PHONY: connect debug clean								# Declare that connect, debug and clean are targets, not real files

connect:												# Boot the JLinkGDBServer driver with a specific set up for a device STM32L475VG
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:													# Boot the debugger loading commands since the se203.gdb file
	$(GDB) $(GDBFLAGS)

clean:													# Clean the .elf files generated, this is useful for keep the directory clean before a new execution
	rm -f $(ELFFILES)
