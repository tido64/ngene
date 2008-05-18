# Makefile for Ngene

TARGET = ngene
BINDIR = bin
OBJDIR = obj
SRCDIR = src
EXEC = $(BINDIR)/$(TARGET)
OBJ = $(OBJDIR)/ConfigManager.o \
$(OBJDIR)/Logger.o \
$(OBJDIR)/PlotterFactory.o \
$(OBJDIR)/Plotter_SVG.o \
$(OBJDIR)/PluginManager.o \
$(OBJDIR)/Random.o \
$(OBJDIR)/Ngene.o

CPP = g++
CFLAGS = -g -O3 -Wall -fopenmp
LDFLAGS = -ldl -lgomp

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

$(OBJDIR)/Ngene.o: $(SRCDIR)/Ngene.cpp
	$(CPP) -DSIMPLE $(CFLAGS) -c $< -o $@

$(OBJDIR)/Random.o: $(SRCDIR)/Random.cpp
	$(CPP) -g0 -O3 -Wall -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

cleanall: clean
	rm -f $(EXEC)
