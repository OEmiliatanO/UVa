CC:=g++
Flag:=-Wall -Wextra

initDir:
	mkdir $(DIR)
	cp ./template/Makefile ./$(DIR)/Makefile
	cp ./template/main.cpp ./$(DIR)/main.cpp

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
