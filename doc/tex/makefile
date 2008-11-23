TARGET = main
TEX = pdflatex
OPT = -file-line-error

default: $(TARGET)

$(TARGET): $(TARGET).bbl
	$(TEX) $(OPT) $(TARGET).tex

%.bbl: %.aux
	bibtex $<
	$(TEX) $(OPT) $(TARGET).tex

%.aux: %.tex
	$(TEX) $(OPT) $<

open: default
	@gnome-open $(TARGET).pdf

clean:
	rm -f *.aux $(TARGET).bbl $(TARGET).blg $(TARGET).log $(TARGET).out $(TARGET).toc
