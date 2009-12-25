TARGET = main
TEX = @pdflatex
BIB = @bibtex
DRAFT = -draftmode
OPT = -file-line-error -halt-on-error

default: $(TARGET)

$(TARGET): $(TARGET).bbl
	$(TEX) $(OPT) $(TARGET).tex > /dev/null
	@grep written $(TARGET).log

%.bbl: %.aux
	$(BIB) $< > /dev/null
	$(TEX) $(DRAFT) $(OPT) $(TARGET).tex > /dev/null

%.aux: %.tex
	$(TEX) $(DRAFT) $(OPT) $< > /dev/null

open: default
	@gnome-open $(TARGET).pdf

clean:
	rm -f *.aux $(TARGET).bbl $(TARGET).blg $(TARGET).lof $(TARGET).log $(TARGET).out $(TARGET).toc
