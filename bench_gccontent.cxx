#include <benchmark/benchmark.h>
#include <cstdlib>

#include "common.h"
#include "gccontent.h"

static const size_t LENGTH = 100000;

static void gccontent_simple(benchmark::State &state)
{
	char *sequence = (char *)malloc(LENGTH + 1);
	gen(sequence, LENGTH);

	while (state.KeepRunning()) {
		double gc = gccontent_simple(sequence, LENGTH);
		escape(&gc);
	}

	free(sequence);
}
BENCHMARK(gccontent_simple);

static void gccontent_length(benchmark::State &state)
{
	char *sequence = (char *)malloc(LENGTH + 1);
	gen(sequence, LENGTH);

	while (state.KeepRunning()) {
		double gc = gccontent_length(sequence, LENGTH);
		escape(&gc);
	}

	free(sequence);
}
BENCHMARK(gccontent_length);

static void gccontent_twiddle(benchmark::State &state)
{
	char *sequence = (char *)malloc(LENGTH + 1);
	gen(sequence, LENGTH);

	while (state.KeepRunning()) {
		double gc = gccontent_twiddle(sequence, LENGTH);
		escape(&gc);
	}

	free(sequence);
}
BENCHMARK(gccontent_twiddle);

static void gccontent_length_twiddle(benchmark::State &state)
{
	char *sequence = (char *)malloc(LENGTH + 1);
	gen(sequence, LENGTH);

	while (state.KeepRunning()) {
		double gc = gccontent_length_twiddle(sequence, LENGTH);
		escape(&gc);
	}

	free(sequence);
}
BENCHMARK(gccontent_length_twiddle);

BENCHMARK_MAIN();
