#include <benchmark/benchmark.h>
#include <cstdlib>
#include <random>

#include "common.h"
#include "transversions.h"

static const size_t LENGTH = 100000;

void gen(char *str, size_t length, size_t seed)
{
	static const char *ACGT = "ACGT";

	auto base_rand = std::default_random_engine{seed};
	auto base_dist = std::uniform_int_distribution<int>{0, 3};
	auto base_acgt = [&] { return ACGT[base_dist(base_rand)]; };

	while (length--) {
		*str++ = base_acgt();
	}

	*str = '\0';
}

void mutate(char *str, size_t length, const char *base, double substitutions)
{
	static const char *NOT_A = "CGT";
	static const char *NOT_C = "AGT";
	static const char *NOT_G = "ACT";
	static const char *NOT_T = "ACG";

	auto rand = std::default_random_engine{seed};
	auto snp = std::uniform_real_distribution<double>{0., 1.};
	auto dist = std::uniform_int_distribution<int>{0, 2};
	auto mutate = [&](char c) {
		auto r = dist(rand);
		switch (c) {
			case 'A': return NOT_A[r];
			case 'C': return NOT_C[r];
			case 'G': return NOT_G[r];
			case 'T': return NOT_T[r];
		}

		return 'X';
	};
	auto total_subst = length * substitutions;

	while (length--) {
		char c = *base++;
		if (snp(rand) < substitutions) {
			*str++ = mutate(c);
		} else {
			*str++ = c;
		}
	}

	*str = '\0';
}

static void transversion_mutations(benchmark::State &state)
{
	char *subject = static_cast<char *>(malloc(LENGTH + 1));
	char *query = static_cast<char *>(malloc(LENGTH + 1));
	gen(subject, LENGTH, 1729);
	gen(query, LENGTH, 8003);

	while (state.KeepRunning()) {
		auto mutations = transversion_mutations(subject, LENGTH, query);
		escape(&mutations);
	}

	free(subject);
	free(query);
}
BENCHMARK(transversion_mutations);

static void transversion_mutations_length(benchmark::State &state)
{
	char *subject = static_cast<char *>(malloc(LENGTH + 1));
	char *query = static_cast<char *>(malloc(LENGTH + 1));
	gen(subject, LENGTH, 1729);
	gen(query, LENGTH, 8003);

	while (state.KeepRunning()) {
		auto mutations = transversion_mutations_length(subject, LENGTH, query);
		escape(&mutations);
	}

	free(subject);
	free(query);
}
BENCHMARK(transversion_mutations_length);

static void transversion_transversions(benchmark::State &state)
{
	char *subject = static_cast<char *>(malloc(LENGTH + 1));
	char *query = static_cast<char *>(malloc(LENGTH + 1));
	gen(subject, LENGTH, 1729);
	gen(query, LENGTH, 8003);

	while (state.KeepRunning()) {
		size_t transversions =
			transversion_transversions(subject, LENGTH, query);
		escape(&transversions);
	}

	free(subject);
	free(query);
}
BENCHMARK(transversion_transversions);

static void transversion_twiddle(benchmark::State &state)
{
	char *subject = static_cast<char *>(malloc(LENGTH + 1));
	char *query = static_cast<char *>(malloc(LENGTH + 1));
	gen(subject, LENGTH, 1729);
	gen(query, LENGTH, 8003);

	while (state.KeepRunning()) {
		size_t transversions =
			transversion_twiddle_length(subject, LENGTH, query);
		escape(&transversions);
	}

	free(subject);
	free(query);
}
BENCHMARK(transversion_twiddle);

static void transversion_builtin(benchmark::State &state)
{
	char *subject = static_cast<char *>(malloc(LENGTH + 1));
	char *query = static_cast<char *>(malloc(LENGTH + 1));
	gen(subject, LENGTH, 1729);
	gen(query, LENGTH, 8003);

	while (state.KeepRunning()) {
		size_t transversions = transversion_builtin(subject, LENGTH, query);
		escape(&transversions);
	}

	free(subject);
	free(query);
}
BENCHMARK(transversion_builtin);

BENCHMARK_MAIN();
