# General rules for making images

%.pdf: %.eps
	epstopdf $< > $@

%.pdf: %.dot
	fdp -Tpdf < $< > $@

%.pdf: %.svg
	inkscape -A $@ $<

%.eps: %.plt
	gnuplot $< > $@

%.eps: %.dia
	dia -e $@ -t eps $<

