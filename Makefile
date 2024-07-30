all: echosrv_pthread.c echocli.c 

EXE=echosrv_pthread echocli

all: $(EXE)

%: %.c
	gcc -Wall -ggdb  -o $@ $<
clean:
	rm -rfv $(EXE)
