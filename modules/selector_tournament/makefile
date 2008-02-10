TARGET = selector_tournament
BIN = ../../bin/modules

CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(TARGET).o:
	$(CPP) -fPIC $(CFLAGS) -c $(TARGET).cpp

$(TARGET).so: $(TARGET).o
	$(CPP) -shared $(CFLAGS) -o $(BIN)/$(TARGET).so $(TARGET).cpp
