TARGET = selector_tournament
BINDIR = ../../bin/modules
OBJDIR = ../../obj

CPP = g++
CFLAGS = -g0 -O3 -Wall -iquote../../src/Interfaces -fPIC

default: $(TARGET).so

$(OBJDIR)/Random.o:
	$(CPP) $(CFLAGS) -c ../../src/Random.cpp -o $@

$(OBJDIR)/%.o: %.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(TARGET).so: $(OBJDIR)/Random.o $(OBJDIR)/$(TARGET).o
	$(CPP) -shared -o $(BINDIR)/$@ $^
	strip $(BINDIR)/$@
