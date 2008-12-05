# Makefile for Ngene

TARGET = ngene
BINDIR = bin
OBJDIR = build/unix
SRCDIR = src
EXEC = $(BINDIR)/$(TARGET)
OBJ = $(OBJDIR)/Algorithm.o \
	$(OBJDIR)/ConfigManager.o \
	$(OBJDIR)/InterruptHandler.o \
	$(OBJDIR)/Logger.o \
	$(OBJDIR)/PlotterFactory.o \
	$(OBJDIR)/Plotter_SVG.o \
	$(OBJDIR)/PluginManager.o \
	$(OBJDIR)/Ngene.o

CPP = g++
CFLAGS = -g -O2 -Wall -pipe -I include -ftree-vectorize #-fopenmp
LDFLAGS = -ldl #-lgomp

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(OBJ)

cleanall: clean
	rm -f $(EXEC)
