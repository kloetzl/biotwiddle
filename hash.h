
static size_t hash_simple(const char *kmer, size_t k)
{
	size_t return_value = 0;

	while (k--) {
		char c = *kmer++;
		size_t val = 0;
		switch (c) {
			case 'A': val = 0; break;
			case 'C': val = 1; break;
			case 'G': val = 2; break;
			case 'T': val = 3; break;
		}

		return_value <<= 2;
		return_value |= val;
	}

	return return_value;
}

static size_t hash_twiddle(const char *kmer, size_t k)
{
	size_t return_value = 0;

	while (k--) {
		char c = *kmer++;
		c &= 6;
		c ^= c >> 1;

		return_value <<= 2;
		return_value |= c >> 1;
	}

	return return_value;
}

static size_t hash_twiddle_length(const char *kmer, size_t K)
{
	size_t return_value = 0;
	size_t k = 0;

	while (k < K) {
		char c = kmer[k++];
		c &= 6;
		c ^= c >> 1;

		return_value <<= 2;
		return_value |= c >> 1;
	}

	return return_value;
}

static size_t hash_table(const char *kmer, size_t K)
{
	static char table[127];
	table['A'] = 0;
	table['C'] = 1;
	table['G'] = 2;
	table['T'] = 3;

	size_t return_value = 0;
	size_t k = 0;

	while (k < K) {
		return_value <<= 2;
		return_value |= table[kmer[k++]];
	}

	return return_value;
}
