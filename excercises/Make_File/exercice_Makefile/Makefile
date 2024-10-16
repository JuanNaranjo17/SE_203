# Define prefix for ARM toolchain
PREFIX = arm-none-eabi-

# Define the compilation command
CC     = $(PREFIX)gcc

# Options for C compile and linker commands
CFLAGS       = -Wall -Werror -g -Og -mthumb -c -MMD
STUBS_CFLAGS = -g -O2 -mthumb -c
LDFLAGS      = -L/opt/mylibs -mthumb

# Files
CFILES      = main.c t1.c t2.c 			    			# Define the .c files for obtain the executable
LIBFILES    = libs/stubs.c							    # Define the .c files into the library for obtain the executable
OBJFILESC   = $(patsubst %.c,%.o,$(CFILES))				# Create corresponding .o files since .c files (search the files that finish in .c and replace .c by .o)
OBJFILESLIB = $(patsubst %.c,%.o,$(LIBFILES))			# Create corresponding .o files since .c lib files (search the files that finish in .c and replace .c by .o)

# Dependency files
DEPS = $(patsubst %.o,%.d,$(OBJFILESC)) $(patsubst %.o,%.d,$(OBJFILESLIB))

TARGET   = hello										# Name of the final executable

# Default target to build the executable
build: $(TARGET)										# Start point for build the project, the main objective

# Rule to compile the .c files into .o files
%.o:%.c
	$(CC) $(CFLAGS) -o $@ $<

# Rule to compile the stubs.c file within the folder libs into .o files
libs/stubs.o: libs/stubs.c
	$(CC) $(STUBS_CFLAGS) -o $@ $<


# Rule to link the .o files into the final executable main
$(TARGET): $(OBJFILESC)	$(OBJFILESLIB)					# Define the hello file (TARGET) with the de dependeces (OBJFILES) (OBGFILESLIB)
	$(CC) $(LDFLAGS) $(OBJFILESC) $(OBJFILESLIB) -lm -o $(TARGET)

# Include the dependency files
-include $(DEPS)

.PHONY: build clean										# Declare that build and clean are targets, not real files, this for execute the rules related to this targets without trying to search the files

clean:													# Clean all the object files and the executable files generated, this is useful for keep the directory clean before a new execution
	rm -f $(OBJFILESC) $(OBJFILESLIB) $(TARGET) $(DEPS)