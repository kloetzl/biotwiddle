export RUNS=2
MODULES= hash gccontent revcomp transversions
TEX= hash.tex gccontent.tex revcomp.tex transversions.tex

.PHONY: all clean

all: twid.pdf

twid.pdf: twid.tex $(TEX)
	pdflatex $<
	evince $@ &

hash.tex: code/hash.tex
gccontent.tex: code/gccontent.tex
revcomp.tex: code/revcomp.tex
transversions.tex: code/transversions.tex

$(TEX):
	cp $^ $@

$(patsubst %,code/%,$(TEX)):
	$(MAKE) -C code clean
	$(MAKE) -C code "CXX=g++" $(@F)
	mv $@ $@.bkp
	$(MAKE) -C code clean
	$(MAKE) -C code "CXX=clang++" $(@F)
	cat $@.bkp >> $@

clean:
	rm -f $(TEX) *.out *.min *.aux twid.log twid.pdf
