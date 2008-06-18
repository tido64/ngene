TARGET = gene_unsorted
BINDIR = ../../bin/modules
OBJDIR = ../../obj

CPP = g++
CFLAGS = -g0 -O3 -Wall -iquote../../src/Interfaces -fPIC

default: $(TARGET).so

$(TARGET).so:
	$(CPP) -shared $(CFLAGS) -o $(BINDIR)/$(TARGET).so $(TARGET).cpp
	strip $(BINDIR)/$(TARGET).so
