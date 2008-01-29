TARGET = gene_nbryo.so
BINDIR = bin
OBJDIR = obj
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/Cell.o \
		 $(OBJDIR)/CellFactory.o \
		 $(OBJDIR)/ConfigManager.o \
		 $(OBJDIR)/Gene.o \
		 $(OBJDIR)/Hormones.o \
		 $(OBJDIR)/Nbryo.o \
		 $(OBJDIR)/NUtility.o \
		 $(OBJDIR)/Organism.o \
		 $(OBJDIR)/Protein.o \
		 $(OBJDIR)/Ribosome.o \
		 $(OBJDIR)/gene_nbryo.o

CPP = g++
CFLAGS = -O2 -Wall
LDFLAGS =

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) -shared $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) -fPIC $(CFLAGS) -c $< -o $@

clean:
	rm -r $(OBJ)

cleanall: clean
	rm -f $(EXEC)
