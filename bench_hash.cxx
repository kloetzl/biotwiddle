#include <benchmark/benchmark.h>
#include <cstdlib>

#include "common.h"
#include "hash.h"

static const size_t LENGTH = 100000;
static const size_t K = 16;

static void hash_simple(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		for (char *kmer = forward; kmer < forward + LENGTH - K; kmer++) {
			size_t hash = hash_simple(kmer, K);
			escape(&hash);
		}
	}

	free(forward);
}
BENCHMARK(hash_simple);

static void hash_twiddle(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		for (char *kmer = forward; kmer < forward + LENGTH - K; kmer++) {
			size_t hash = hash_twiddle(kmer, K);
			escape(&hash);
		}
	}

	free(forward);
}
BENCHMARK(hash_twiddle);

static void hash_twiddle_length(benchmark::State &state)
{
	char *forward = (char *)malloc(LENGTH + 1);
	gen(forward, LENGTH);

	while (state.KeepRunning()) {
		for (char *kmer = forward; kmer < forward + LENGTH - K; kmer++) {
			size_t hash = hash_twiddle_length(kmer, K);
			escape(&hash);
		}
	}

	free(forward);
}
BENCHMARK(hash_twiddle_length);

BENCHMARK_MAIN();
