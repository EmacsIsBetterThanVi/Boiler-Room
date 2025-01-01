all: clean main config ports

CC = clang
override CFLAGS += -g -Wno-everything -pthread -lm

main: VM.c $(HEADERS)
	$(CC) $(CFLAGS) VM.c -o "boiler-room"

main-debug: VM.c $(HEADERS)
	$(CC) $(CFLAGS) -O0 VM.c -o "boiler-room"

clean:
	rm -f main main-debug

ports:
	./buildports
	
config:
	mkdir ~/.local/bin/BoilerRoom -p
	cp init.sh ~/.local/bin/BoilerRoom/