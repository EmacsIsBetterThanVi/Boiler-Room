all: clean main

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: VM.c $(HEADERS)
	$(CC) $(CFLAGS) VM.c -o "$@"

main-debug: VM.c $(HEADERS)
	$(CC) $(CFLAGS) -O0 VM.c -o "$@"

clean:
	rm -f main main-debug
