#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

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

int main()
{
	char *subject = static_cast<char *>(malloc(LENGTH + 1));
	char *query = static_cast<char *>(malloc(LENGTH + 1));
	gen(subject, LENGTH, 1729);
	gen(query, LENGTH, 8003);
	double mut = 0, trans = 0;

	mut = transversions_mutations(subject, LENGTH, query);
	std::cout << "mutations: " << mut << "\n";

	auto mut2 = transversions_mutations_length(subject, LENGTH, query);
	std::cout << "mutations2: " << mut2 << "\n";
	assert(abs(mut - mut2) < 10.0 / LENGTH);

	trans = transversions_transversions(subject, LENGTH, query);
	std::cout << "transversions: " << trans << "\n";
	assert(trans < mut);

	auto trans2 = transversions_twiddle_length(subject, LENGTH, query);
	std::cout << "twiddle: " << trans2 << "\n";
	assert(abs(trans - trans2) < 10.0 / LENGTH);

	auto trans3 = transversions_builtin(subject, LENGTH, query);
	std::cout << "builtin: " << trans3 << "\n";
	assert(abs(trans - trans2) < 10.0 / LENGTH);

	free(subject);
	free(query);
	return 0;
}
