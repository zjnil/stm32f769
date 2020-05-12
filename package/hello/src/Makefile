CC=g++
CFLAGS=-std=c++11

.PHONY: clean

all: hello

hello: main.o capp.o
	$(CC) $(CFLAGS) -o '$@' main.o capp.o -lSDLmain -lSDL -lasound

%.o: %.cpp
	$(CC) $(CFLAGS) -c '$<'

clean:
	rm *.o hello