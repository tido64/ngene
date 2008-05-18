TARGET = mutator_random-swap
BINDIR = ../../bin/modules
OBJDIR = ../../obj

CPP = g++
CFLAGS = -g0 -O3 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(OBJDIR)/Random.o:
	$(CPP) -fPIC $(CFLAGS) -c ../../src/Random.cpp -o $@

$(OBJDIR)/%.o: %.cpp
	$(CPP) -fPIC $(CFLAGS) -c $< -o $@

$(TARGET).so: $(OBJDIR)/Random.o $(OBJDIR)/$(TARGET).o
	$(CPP) -shared -o $(BINDIR)/$@ $^
