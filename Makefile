# Specify the output directory
BINDIR = bin

# List of source files
SRC = 19signal.c 20sigaction.c 20sa_mask.c 21sigaction_recv.c 21sigaction_send.c 21sigaction_rtmin.c

# The names of the final executables
EXEC = $(BINDIR)/20sigaction $(BINDIR)/19signal $(BINDIR)/20sa_mask $(BINDIR)/21sigaction_send  $(BINDIR)/21sigaction_rtmin

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
