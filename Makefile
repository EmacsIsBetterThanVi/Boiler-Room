all: clean main config ports

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

main: VM.c $(HEADERS)
	$(CC) $(CFLAGS) VM.c -o "boiler-room"

main-debug: VM.c $(HEADERS)
	$(CC) $(CFLAGS) -O0 VM.c -o "debug"

clean:
	rm -f boiler-room debug

ports:
	./buildports	
config:
	mkdir -p ~/.local/bin/BoilerRoom
	cp init.sh ~/.local/bin/BoilerRoom/
