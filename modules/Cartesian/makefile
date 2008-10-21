TARGET = gene_cartesian.so
BINDIR = ../../bin/modules
OBJDIR = build/unix
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/Cartesian.o \
	$(OBJDIR)/Algorithm.o \
	$(OBJDIR)/Random.o \
	$(OBJDIR)/gene_cartesian.o

CPP = g++
CFLAGS = -g -O0 -Wall -Werror -fPIC
LDFLAGS = -shared

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: ../../src/%.cpp
	$(CPP) -g0 -O3 -Wall -Werror -fPIC -s -c $< -o $@

fitness: $(OBJDIR)/fitness_cartesian.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/fitness_cartesian.so $^

mutator: $(OBJDIR)/Random.o $(OBJDIR)/mutator_cartesian.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/mutator_cartesian.so $^

all: $(EXEC) fitness mutator

clean:
	rm -f $(OBJ) $(OBJDIR)/mutator_cartesian.o
