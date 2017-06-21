#include <cassert>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "common.h"
#include "revcomp.h"

static const size_t LENGTH = 100000;

int main()
{
	char *seq = static_cast<char *>(malloc(LENGTH + 1));
	char *rev = static_cast<char *>(malloc(LENGTH + 1));
	char *rev2 = static_cast<char *>(malloc(LENGTH + 1));
	gen(seq, LENGTH);

	rev = revcomp_simple(seq, LENGTH, rev);

	rev2 = revcomp_table(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	rev2 = revcomp_reverse(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	rev2 = revcomp_twocase(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	rev2 = revcomp_twocase_switch(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	rev2 = revcomp_twiddle(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	rev2 = revcomp_subtraction(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	rev2 = revcomp_twostep(seq, LENGTH, rev2);
	assert(strcmp(rev, rev2) == 0);

	free(seq);
	free(rev);
	free(rev2);
	return 0;
}