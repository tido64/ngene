TARGET = gene_nbryo.so
BINDIR = ../../bin/modules
OBJDIR = obj
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/Cell.o \
$(OBJDIR)/CellFactory.o \
$(OBJDIR)/ConfigManager.o \
$(OBJDIR)/Coordinates.o \
$(OBJDIR)/Gene.o \
$(OBJDIR)/Hormones.o \
$(OBJDIR)/Organism.o \
$(OBJDIR)/Protein.o \
$(OBJDIR)/Random.o \
$(OBJDIR)/Ribosome.o \
$(OBJDIR)/Synthesizer.o \
$(OBJDIR)/gene_nbryo.o

CPP = g++
CFLAGS = -g -O2 -Wall -fPIC
LDFLAGS = -shared

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) -shared $(LDFLAGS) -o $@ $^

$(OBJDIR)/Random.o:
	$(CPP) -g0 -O3 -Wall -fPIC -c ../../src/Random.cpp -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

fitness: $(OBJDIR)/Coordinates.o $(OBJDIR)/fitness_nbryo.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/fitness_nbryo.so $^

mutator: $(OBJDIR)/Gene.o $(OBJDIR)/Random.o $(OBJDIR)/mutator_nbryo.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/mutator_nbryo.so $^

all: $(EXEC) fitness mutator

clean:
	rm -f $(OBJ) $(OBJDIR)/fitness_nbryo.o $(OBJDIR)/mutator_nbryo.o
