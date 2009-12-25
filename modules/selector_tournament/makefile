TARGET = selector_tournament
BINDIR = ../../bin/modules
OBJDIR = ../../build/unix

CPP = g++
CFLAGS = -g0 -O2 -Wall -Werror -pipe -I ../../include -ftree-vectorize -fPIC

default: $(TARGET).so

$(OBJDIR)/%.o: %.cpp
	$(CPP) -c $< $(CFLAGS) -o $@

$(TARGET).so: $(OBJDIR)/$(TARGET).o
	$(CPP) -shared -o $(BINDIR)/$@ $^

clean:
	rm -f $(OBJDIR)/$(TARGET).o
