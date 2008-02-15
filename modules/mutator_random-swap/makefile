TARGET = mutator_random-swap
BIN = ../../bin/modules

CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

Random.o:
	$(CPP) -fPIC -O2 -Wall -c ../../src/Random.cpp

$(TARGET).o:
	$(CPP) -fPIC $(CFLAGS) -c $(TARGET).cpp

$(TARGET).so: Random.o $(TARGET).o
	$(CPP) -shared $(CFLAGS) -o $(BIN)/$(TARGET).so $^
