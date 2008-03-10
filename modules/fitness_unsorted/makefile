TARGET = fitness_unsorted
BINDIR = ../../bin/modules
OBJDIR = ../../obj

CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(TARGET).so:
	$(CPP) -shared $(CFLAGS) -o $(BINDIR)/$(TARGET).so $(TARGET).cpp
