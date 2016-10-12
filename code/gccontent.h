
static inline double gccontent_simple(const char *seq, size_t length)
{
	size_t gc = 0;

	const char *ptr = seq;
	for (; *ptr; ptr++) {
		if (*ptr == 'C' || *ptr == 'G') {
			gc++;
		}
	}

	return (double)gc / length;
}

static inline double gccontent_length(const char *seq, size_t length)
{
	size_t gc = 0;
	size_t i = 0;

	for (; i < length; i++) {
		if (seq[i] == 'C' || seq[i] == 'G') {
			gc++;
		}
	}

	return (double)gc / length;
}

static inline double gccontent_twiddle(const char *seq, size_t length)
{
	size_t gc = 0;

	for (; *seq; seq++) {
		char masked = *seq & 'G' & 'C';
		if (masked == ('G' & 'C')) {
			gc++;
		}
	}

	return (double)gc / length;
}

static inline double gccontent_length_twiddle(const char *seq, size_t length)
{
	size_t gc = 0;
	size_t i = 0;

	for (; i < length; i++) {
		char masked = seq[i] & 'G' & 'C';
		if (masked == ('G' & 'C')) {
			gc++;
		}
	}

	return (double)gc / length;
}
