TARGET = main
BIB = main.bbl
TEX = pdflatex
OPT = -file-line-error

default: $(TARGET)

$(TARGET): $(BIB)
	$(TEX) $(OPT) $(TARGET).tex

%.bbl: %.aux
	bibtex $<
	$(TEX) $(OPT) $(TARGET).tex

%.aux: %.tex
	$(TEX) $(OPT) $<

open: default
	@gnome-open main.pdf

clean:
	rm -f *.aux main.bbl main.blg main.log main.out main.toc
