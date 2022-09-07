CC:=g++
Flag:=-Wall -Wextra

init: ../template/main.cpp
	cp ../template/main.cpp main.cpp

dep: main.cpp
	$(CC) $(Flag) -c main.cpp

debug: main.cpp
	$(CC) $(Flag) -D DEBUGing -c main.cpp

all: main.o
	$(CC) -o main main.o

clean:
	-rm *.o
