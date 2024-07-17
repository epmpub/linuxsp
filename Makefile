# Specify the output directory
BINDIR = bin

# List of source files
SRC = 19signal.c 20sigaction.c

# The names of the final executables
EXEC = $(BINDIR)/20sigaction $(BINDIR)/19signal

# Default target to compile all executables
all: $(EXEC)

$(EXEC): $(BINDIR)/%: %.c
	gcc -Wall -g -std=gnu99  $< -o $@

# Ensure the output directory exists before compiling
$(EXEC): | $(BINDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC)
