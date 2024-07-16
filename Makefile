# Specify the output directory
BINDIR = bin

# List of source files
SRC = lseek.c lseek2.c copyFile1.c copyFile2.c sendFile.c

# The names of the final executables
EXEC = $(BINDIR)/lseek $(BINDIR)/lseek2 $(BINDIR)/copyFile1 $(BINDIR)/copyFile2 $(BINDIR)/sendFile

# Default target to compile all executables
all: $(EXEC)

$(EXEC): $(BINDIR)/%: %.c
	gcc -Wall -g $< -o $@

# Ensure the output directory exists before compiling
$(EXEC): | $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)
