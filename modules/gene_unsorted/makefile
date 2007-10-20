TARGET = gene_unsorted
BIN = ..
CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(TARGET).o: $(TARGET).h
	$(CPP) -fPIC -c $(TARGET).cpp

$(TARGET).so: $(TARGET).o
	$(CPP) -shared $(CFLAGS) -o $(BIN)/$(TARGET).so $(TARGET).cpp
	rm -f $(TARGET).o
