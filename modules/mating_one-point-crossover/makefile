TARGET = mating_one-point-crossover
BINDIR = ../../bin/modules
OBJDIR = ../../build/unix

CPP = g++
CFLAGS = -g0 -O2 -Wall -Werror -pipe -I ../../include -ftree-vectorize -fPIC

default: $(TARGET).so

$(OBJDIR)/Random.o:
	$(CPP) -c ../../src/Random.cpp $(CFLAGS) -o $@

$(OBJDIR)/%.o: %.cpp
	$(CPP) -c $< $(CFLAGS) -o $@

$(TARGET).so: $(OBJDIR)/Random.o $(OBJDIR)/$(TARGET).o
	$(CPP) -shared -o $(BINDIR)/$@ $^

clean:
	rm -f $(OBJDIR)/$(TARGET).o
