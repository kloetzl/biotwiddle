#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdlib>

#include "common.h"
#include "revcomp.h"

static const size_t LENGTH = 1000000;

static void revcomp_simple(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	char *reverse = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		revcomp_simple(forward, LENGTH, reverse);
		escape(reverse);
	}

	free(forward);
	free(reverse);
}
BENCHMARK(revcomp_simple);

static void revcomp_reverse(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	char *reverse = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		revcomp_reverse(forward, LENGTH, reverse);
		escape(reverse);
	}

	free(forward);
	free(reverse);
}
BENCHMARK(revcomp_reverse);

static void revcomp_twocase(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	char *reverse = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		revcomp_twocase(forward, LENGTH, reverse);
		escape(reverse);
	}

	free(forward);
	free(reverse);
}
BENCHMARK(revcomp_twocase);

static void revcomp_twiddle(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	char *reverse = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		revcomp_twiddle(forward, LENGTH, reverse);
		escape(reverse);
	}

	free(forward);
	free(reverse);
}
BENCHMARK(revcomp_twiddle);

static void revcomp_subtraction(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	char *reverse = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		revcomp_subtraction(forward, LENGTH, reverse);
		escape(reverse);
	}

	free(forward);
	free(reverse);
}
BENCHMARK(revcomp_subtraction);

static void revcomp_twostep(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	char *reverse = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		revcomp_twostep(forward, LENGTH, reverse);
		escape(reverse);
	}

	free(forward);
	free(reverse);
}
BENCHMARK(revcomp_twostep);

BENCHMARK_MAIN();
