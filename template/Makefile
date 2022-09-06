CC:=g++
Flag:=-Wall

init: ../template/main.cpp
	cp ../template/main.cpp main.cpp

dep: main.cpp
	$(CC) $(Flag) -c main.cpp

all: main.o
	$(CC) -o main main.cpp

clean:
	-rm *.o
