CPPFLAGS = -Wall -Wextra -std=c++14
CXXFLAGS += -O3 -g -march=native -ftree-vectorize

BENCHMARKS = bench_revcomp bench_hash bench_gccontent bench_transversions
CHECKS = check_gccontent check_transversions check_hash check_revcomp
EXECUTABLES = $(BENCHMARKS)	$(CHECKS)

LOGFILE = log
RUNS ?= 3

.PHONY: all clean check format

all: $(EXECUTABLES) $(CHECKS)

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


hash.tex: bench_hash check_hash
	./driver.py -r $(RUNS) -c $(CXX) -m hash

gccontent.tex: bench_gccontent check_gccontent
	./driver.py -r $(RUNS) -c $(CXX) -m gccontent

transversions.tex: bench_transversions check_transversions
	./driver.py -r $(RUNS) -c $(CXX) -m transversions

revcomp.tex: bench_revcomp check_revcomp
	./driver.py -r $(RUNS) -c $(CXX) -m revcomp


format: .clang-format
	clang-format -i *.h *.cxx

clean:
	rm -f *.o $(EXECUTABLES) $(LOGFILE) *.tex perf.data*
