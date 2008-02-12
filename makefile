# Makefile for Ngene

TARGET = ngene
BINDIR = bin
OBJDIR = obj
SRCDIR = src
EXEC = $(BINDIR)/$(TARGET)
OBJ = $(OBJDIR)/ConfigManager.o \
$(OBJDIR)/PluginManager.o \
$(OBJDIR)/Plotter_SVG.o \
$(OBJDIR)/PlotterFactory.o \
$(OBJDIR)/Logger.o \
$(OBJDIR)/Ngene.o

CPP = g++
CFLAGS = -g -Wall
LDFLAGS = -ldl -lboost_filesystem

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

cleanall: clean
	rm -f $(EXEC)
