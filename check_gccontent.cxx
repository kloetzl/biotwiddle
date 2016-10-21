#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>

#include "common.h"
#include "gccontent.h"

static const size_t LENGTH = 100000;

int main()
{
	char *seq = static_cast<char *>(malloc(LENGTH + 1));
	gen(seq, LENGTH);
	double gc = 0;

	gc = gccontent_simple(seq, LENGTH);
	std::cout << "simple: " << gc << "\n";

	auto gc2 = gccontent_length(seq, LENGTH);
	std::cout << "length: " << gc2 << "\n";
	assert(abs(gc - gc2) < 1e-4);

	gc2 = gccontent_twiddle(seq, LENGTH);
	std::cout << "twiddle: " << gc2 << "\n";
	assert(abs(gc - gc2) < 1e-4);

	gc2 = gccontent_length_twiddle(seq, LENGTH);
	std::cout << "length_twiddle: " << gc2 << "\n";
	assert(abs(gc - gc2) < 1e-4);

	gc2 = gccontent_table(seq, LENGTH);
	std::cout << "table: " << gc2 << "\n";
	assert(abs(gc - gc2) < 1e-4);

	free(seq);
	return 0;
}