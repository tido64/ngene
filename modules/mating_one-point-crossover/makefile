TARGET = mating_one-point-crossover
BINDIR = ../../bin/modules
OBJDIR = ../../obj

CPP = g++
CFLAGS = -g0 -O3 -Wall -Werror -iquote../../src/Interfaces -fPIC

default: $(TARGET).so

$(OBJDIR)/Random.o:
	$(CPP) $(CFLAGS) -c ../../src/Random.cpp -o $@

$(OBJDIR)/%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(TARGET).so: $(OBJDIR)/Random.o $(OBJDIR)/$(TARGET).o
	$(CPP) -s -shared -o $(BINDIR)/$@ $^
