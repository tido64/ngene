TARGET = gene_artdev3d.so
BINDIR = ../../bin/modules
OBJDIR = build/unix
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/ArtDev3D.o \
	$(OBJDIR)/ConfigManager.o \
	$(OBJDIR)/Gene.o \
	$(OBJDIR)/gene_artdevn.o \
	$(OBJDIR)/Random.o

CPP = g++
CFLAGS = -g -O2 -Wall -Werror -fPIC
LDFLAGS = -shared

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

$(OBJDIR)/Random.o:
	$(CPP) -g0 -O3 -Wall -Werror -fPIC -s -c ../../src/Random.cpp -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

fitness: $(OBJDIR)/Coordinates.o $(OBJDIR)/fitness_artdev3d.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/fitness_artdev3d.so $^

mutator: $(OBJDIR)/Gene.o $(OBJDIR)/Random.o $(OBJDIR)/mutator_artdev3d.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/mutator_artdev3d.so $^

all: $(EXEC) fitness mutator

clean:
	rm -f $(OBJ) $(OBJDIR)/fitness_artdev3d.o $(OBJDIR)/mutator_artdev3d.o
