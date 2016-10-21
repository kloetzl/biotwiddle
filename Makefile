MODULES= hash gccontent revcomp transversions
TEX= hash.tex gccontent.tex revcomp.tex transversions.tex
BENCH_GCC = $(TEX:.tex=.g)
BENCH_CLANG = $(TEX:.tex=.clang)

CPPFLAGS = -Wall -Wextra -std=gnu++14
CXXFLAGS += -O3 -g -march=native -ftree-vectorize

BENCHMARKS = bench_revcomp bench_hash bench_gccontent bench_transversions
CHECKS = check_gccontent check_transversions check_hash check_revcomp
EXECUTABLES = $(BENCHMARKS)	$(CHECKS)

LOGFILE = log
RUNS ?= 3


.PHONY: all clean clean_binary check format

all: twid.pdf

twid.pdf: $(BENCH_CLANG) $(BENCH_GCC) $(TEX) twid.tex twid.bbl
	pdflatex twid.tex
	evince $@ &

twid.aux: twid.tex
	pdflatex $<

twid.bbl: twid.aux
	bibtex twid


%.tex: %.g %.clang
	cat $^ > $@

%.g: driver.py bench_%.g check_%
	./driver.py -r $(RUNS) -c "g++" -m $(*F)

%.clang: driver.py bench_%.clang check_%
	./driver.py -r $(RUNS) -c "clang++" -m $(*F)


%.clang.o: %.cxx
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

%.g.o: %.cxx
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

%.o: %.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

bench_revcomp.clang: bench_revcomp.clang.o
bench_hash.clang: bench_hash.clang.o
bench_gccontent.clang: bench_gccontent.clang.o
bench_transversions.clang: bench_transversions.clang.o

bench_revcomp.g: bench_revcomp.g.o
bench_hash.g: bench_hash.g.o
bench_gccontent.g: bench_gccontent.g.o
bench_transversions.g: bench_transversions.g.o


bench_revcomp.clang bench_hash.clang bench_gccontent.clang bench_transversions.clang:
	clang++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ -lbenchmark -lpthread

bench_revcomp.g bench_hash.g bench_gccontent.g bench_transversions.g:
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ -lbenchmark -lpthread


check_gccontent: check_gccontent.o
check_transversions: check_transversions.o
check_hash: check_hash.o
check_revcomp: check_revcomp.o

$(CHECKS):
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^


check: $(CHECKS)
	@ for file in $^; do \
		echo -n "testing $${file} … "; \
		./$${file} &> $(LOGFILE) || \
		(echo " Unexpected error: $@\n See $(LOGFILE) for details." && exit 1); \
		echo "pass."; \
	done
	rm -f $(LOGFILE)

format: .clang-format
	clang-format -i *.h *.cxx

clean_binary:
	rm -f *.o $(EXECUTABLES) $(CHECKS)

clean: clean_binary
	rm -f $(LOGFILE) $(TEX) perf.data* *.out *.min *.aux twid.log twid.pdf *.g *.clang
