TARGET = gene_cartesian.so
BINDIR = ../../bin/modules
OBJDIR = build/unix
SRCDIR = src
EXEC   = $(BINDIR)/$(TARGET)
OBJ    = $(OBJDIR)/Cartesian.o \
	$(OBJDIR)/Algorithm.o \
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

all: $(EXEC) fitness mutator

clean:
	rm -f $(OBJ)
