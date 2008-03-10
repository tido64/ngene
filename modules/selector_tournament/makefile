TARGET = selector_tournament
BINDIR = ../../bin/modules
OBJDIR = ../../obj

CPP = g++
CFLAGS = -O2 -Wall -iquote../../src/Interfaces

default: $(TARGET).so

$(OBJDIR)/Random.o:
	$(CPP) -fPIC -O2 -Wall -c ../../src/Random.cpp -o $@

$(OBJDIR)/%.o: %.cpp
	$(CPP) -fPIC $(CFLAGS) -c $< -o $@

$(TARGET).so: $(OBJDIR)/Random.o $(OBJDIR)/$(TARGET).o
	$(CPP) -shared $(CFLAGS) -o $(BINDIR)/$@ $^
