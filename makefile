# Makefile for Ngene

TARGET = Ngene
BINDIR = bin
OBJDIR = platform/unix
SRCDIR = src
EXEC = $(BINDIR)/$(TARGET)
OBJ = $(OBJDIR)/$(TARGET).o \
$(OBJDIR)/ConfigManager.o \
$(OBJDIR)/Plotter_SVG.o \
$(OBJDIR)/PlotterFactory.o \
$(OBJDIR)/PluginManager.o \
$(OBJDIR)/Logger.o

CPP = g++
FLAGS = -O2 -Wall
INCLUDES = -iquoteInterfaces -ldl -lboost_filesystem

default: $(EXEC)

$(EXEC): $(OBJ)
	$(CPP) $(FLAGS) $(INCLUDES) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CPP) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

cleanall: clean
	rm -f $(EXEC)

