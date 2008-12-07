TARGET = gene_cartesian.so
BINDIR = ../../bin/modules
OBJDIR = build/unix
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/Cartesian.o \
	$(OBJDIR)/gene_cartesian.o

CPP = g++
CFLAGS = -g -O2 -Wall -Werror -pipe -I ../../include -ftree-vectorize -fPIC
LDFLAGS = -shared

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) -c $< $(CFLAGS) -o $@

fitness: $(OBJDIR)/fitness_cartesian.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/fitness_cartesian.so $^

mating: $(OBJDIR)/mating_cartesian.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/mating_cartesian.so $^

mutator: $(OBJDIR)/mutator_cartesian.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/mutator_cartesian.so $^

all: $(EXEC) fitness mutator

clean:
	rm -f $(OBJ) $(OBJDIR)/fitness_cartesian.o $(OBJDIR)/mating_cartesian.o $(OBJDIR)/mutator_cartesian.o
