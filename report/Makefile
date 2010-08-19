# Makefile from textemplate


# Includes

include imagerules.mk


# Implicit rules

%.pdf: %.tex
	pdflatex -draftmode $<
	grep -q '^\\bibliography{.*}$$' $< && \
		bibtex $* && pdflatex -draftmode $< || true
	pdflatex $<


# Variables

FIGS=fig/graph.pdf fig/watermark.pdf fig/diagram.pdf fig/euler.pdf


# Making Rules

all: textemplate.pdf prestemplate.pdf

textemplate.pdf: textemplate.tex bib.bib $(FIGS)

pretexmplate.pdf: prestemplate.tex $(FIGS)

.PHONY: figs
figs: $(FIGS)


# Cleanup rules

.PHONY: clean cleanfigs
clean: cleanfigs
	rm -f *~ *.aux *.bbl *.blg *.log *.toc textemplate.pdf

cleanfigs:
	rm -f $(FIGS)


