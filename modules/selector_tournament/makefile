TARGET = selector_tournament
BIN = ..

CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(TARGET).o:
	$(CPP) -fPIC $(CFLAGS) -c $(TARGET).cpp

$(TARGET).so: $(TARGET).o
	$(CPP) -shared $(CFLAGS) -o $(BIN)/$(TARGET).so $(TARGET).cpp
	rm -f $(TARGET).o
