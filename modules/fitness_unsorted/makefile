TARGET = fitness_unsorted
BINDIR = ../../bin/modules
OBJDIR = ../../build/unix

CPP = g++
CFLAGS = -g0 -O3 -Wall -Werror -iquote../../src/Interfaces -fPIC

default: $(TARGET).so

$(TARGET).so:
	$(CPP) -s -shared $(CFLAGS) -o $(BINDIR)/$(TARGET).so $(TARGET).cpp
