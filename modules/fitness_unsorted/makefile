TARGET = fitness_unsorted
BINDIR = ../../bin/modules
OBJDIR = ../../build/unix

CPP = g++
CFLAGS = -g0 -O2 -Wall -Werror -pipe -I ../../include -ftree-vectorize -fPIC

default: $(TARGET).so

$(TARGET).so:
	$(CPP) $(CFLAGS) -shared -o $(BINDIR)/$(TARGET).so $(TARGET).cpp
