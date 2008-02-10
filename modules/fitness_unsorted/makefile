TARGET = fitness_unsorted
BIN = ../../bin/modules
CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(TARGET).o:
	$(CPP) -fPIC -c $(TARGET).cpp

$(TARGET).so: $(TARGET).o
	$(CPP) -shared $(CFLAGS) -o $(BIN)/$(TARGET).so $(TARGET).cpp
