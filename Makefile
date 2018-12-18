CC      = g++
CFLAGS  = -g -pthread -O3 -std=c++11 -Wall

OBJECTS = DataParser.o Handler.o Simulator.o Threader.o

all: Program

%.o: %.cpp
	$(CC) -c $< $(CFLAGS)
	
Program: $(OBJECTS) Main.o
	$(CC) $(OBJECTS) Main.o -pthread -o thetaY

clean: 
	rm -f *.o $(PROGRAM)