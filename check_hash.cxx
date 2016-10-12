#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "common.h"
#include "hash.h"

static const size_t LENGTH = 16;

int main()
{
	char *seq = static_cast<char *>(malloc(LENGTH + 1));
	gen(seq, LENGTH);

	auto hash = hash_simple(seq, LENGTH);
	std::cout << "simple: " << hash << "\n";

	auto hash2 = hash_twiddle(seq, LENGTH);
	std::cout << "twiddle: " << hash2 << "\n";
	assert(hash == hash2);

	hash2 = hash_twiddle_length(seq, LENGTH);
	std::cout << "twiddle length: " << hash2 << "\n";
	assert(hash == hash2);

	free(seq);
	return 0;
}