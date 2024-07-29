all: allocMem readFile 01posix_mq 02posix_mq_unlink 01posix_getattr.c 01posix_send 01posix_recv 01posix_notify

EXE=allocMem readFile 01posix_mq 02posix_mq_unlink 01posix_getattr 01posix_send 01posix_recv 01posix_notify

all: $(EXE)

%: %.c
	gcc -Wall -ggdb  -o $@ $<
clean:
	rm -rfv $(EXE)
