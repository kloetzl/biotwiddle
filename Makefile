MODULES= hash gccontent revcomp transversions
TEX= hash.tex gccontent.tex revcomp.tex transversions.tex
BENCH_GCC = $(TEX:.tex=.g)
BENCH_CLANG = $(TEX:.tex=.clang)

CPPFLAGS = -Wall -Wextra -std=c++14
CXXFLAGS += -O3 -g -march=native -ftree-vectorize

BENCHMARKS = bench_revcomp bench_hash bench_gccontent bench_transversions
CHECKS = check_gccontent check_transversions check_hash check_revcomp
EXECUTABLES = $(BENCHMARKS)	$(CHECKS)

LOGFILE = log
RUNS ?= 3


.PHONY: all clean clean_binary check format bench_clang bench_gcc

all: twid.pdf

twid.pdf: twid.tex bench_gcc bench_clang $(TEX)
	pdflatex $<
	evince $@ &

bench_clang: CXX=clang++
bench_clang: clean_binary $(BENCH_CLANG)

bench_gcc: CXX=g++
bench_gcc: clean_binary $(BENCH_GCC)

%.tex: %.g %.clang
	cat $^ > $@

%.g: driver.py | check_% bench_%
	if [ $(CXX) != "g++" ]; then exit 1 ; fi
	./driver.py -r $(RUNS) -c "g++" -m $(*F)

%.clang: driver.py | check_% bench_%
	if [ $(CXX) != "clang++" ]; then exit 1 ; fi
	./driver.py -r $(RUNS) -c "clang++" -m $(*F)

%.o: %.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $^

bench_revcomp: bench_revcomp.o
bench_hash: bench_hash.o
bench_gccontent: bench_gccontent.o
bench_transversions: bench_transversions.o

$(BENCHMARKS):
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^ -lbenchmark -lpthread

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
