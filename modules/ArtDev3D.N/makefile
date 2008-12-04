TARGET = gene_artdev3d.so
BINDIR = ../../bin/modules
OBJDIR = build/unix
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/ArtDev3D.o \
	$(OBJDIR)/Algorithm.o \
	$(OBJDIR)/ConfigManager.o \
	$(OBJDIR)/Gene.o \
	$(OBJDIR)/gene_artdevn.o \
	$(OBJDIR)/Random.o

CPP = g++
CFLAGS = -g -O2 -Wall -Werror -pipe -I ../../include -ftree-vectorize -fPIC
LDFLAGS = -shared

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) -c $< $(CFLAGS) -o $@

$(OBJDIR)/%.o: ../../src/%.cpp
	$(CPP) -c $< $(CFLAGS) -o $@

fitness: $(OBJDIR)/fitness_artdevn.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/fitness_artdev3d.so $^

mutator: $(OBJDIR)/Gene.o $(OBJDIR)/Random.o $(OBJDIR)/mutator_artdevn.o
	$(CPP) $(LDFLAGS) -o $(BINDIR)/mutator_artdev3d.so $^

all: $(EXEC) fitness mutator

clean:
	rm -f $(OBJ) $(OBJDIR)/fitness_artdevn.o $(OBJDIR)/mutator_artdevn.o
