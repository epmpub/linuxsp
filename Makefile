all: allocMem readFile

EXE=allocMem readFile

all: $(EXE)

%: %.c
	gcc -Wall -ggdb  -o $@ $<
clean:
	rm -rfv $(EXE)
