# Makefile from textemplate

TARGET=prova

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

FIGS= fig/5diamonds_grf_dcmst_kruskal_2.pdf fig/5diamonds_grf_dcmst_prim_2.pdf \
fig/Euclid301_GRF_dcmst_kruskal_2.pdf fig/Euclid301_GRF_dcmst_prim_2.pdf \
fig/Euclid303_txt_dcmst_kruskal_2.pdf fig/Euclid303_txt_dcmst_prim_2.pdf \
fig/Euclid306_txt_dcmst_kruskal_2.pdf fig/Euclid306_txt_dcmst_prim_2.pdf \
fig/P20_GRF_dcmst_kruskal_2.pdf fig/P20_GRF_dcmst_prim_2.pdf fig/P22_GRF_dcmst_kruskal_2.pdf \
fig/P22_GRF_dcmst_prim_2.pdf fig/PEARN01_grf_dcmst_kruskal_2.pdf \
fig/PEARN01_grf_dcmst_prim_2.pdf fig/Euclid301_GRF_dcmst_kruskal_3.pdf \
fig/Euclid301_GRF_dcmst_kruskal_4.pdf fig/Euclid301_GRF_dcmst_prim_3.pdf \
fig/Euclid301_GRF_dcmst_prim_4.pdf fig/Euclid303_txt_dcmst_kruskal_3.pdf \
fig/Euclid303_txt_dcmst_kruskal_4.pdf fig/Euclid303_txt_dcmst_prim_3.pdf \
fig/Euclid303_txt_dcmst_prim_4.pdf fig/Euclid306_txt_dcmst_kruskal_3.pdf \
fig/Euclid306_txt_dcmst_kruskal_4.pdf fig/Euclid306_txt_dcmst_prim_3.pdf \
fig/Euclid306_txt_dcmst_prim_4.pdf

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


