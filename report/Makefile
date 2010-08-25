# Makefile from textemplate

TARGET=mst

# Includes

include imagerules.mk


# Implicit rules

%.pdf: %.tex
	pdflatex -draftmode $<
	grep -q '^\\bibliography{.*}$$' $< && \
		bibtex $* && pdflatex -draftmode $< || true
	pdflatex $<
	pdflatex $<


# Variables

FIGS=fig/kruskal_01_quadrado2009_mst.pdf fig/QUADRADO2009_ini.pdf \
     fig/02_DONI22009_euclidean.pdf fig/02_DONI22009_delaunay.pdf \
     fig/kruskal_02_DONI22009_mst.pdf


# Making Rules

all: $(TARGET).pdf

$(TARGET).pdf: $(TARGET).tex bib.bib $(FIGS)

.PHONY: figs
figs: $(FIGS)


# Cleanup rules

.PHONY: clean cleanfigs
clean: cleanfigs
	rm -f *~ *.aux *.bbl *.blg *.log *.toc $(TARGET).pdf

cleanfigs:
	rm -f $(FIGS)


