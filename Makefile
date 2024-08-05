all: timerfd01.c

EXE=timerfd01

all: $(EXE)

%: %.c
	gcc -Wall -ggdb  -o $@ $<
clean:
	rm -rfv $(EXE)
