static char *revcomp_simple(const char *forward, size_t len, char *reverse)
{
	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		unsigned char d;

		switch (forward[k]) {
			case 'A': d = 'T'; break;
			case 'C': d = 'G'; break;
			case 'G': d = 'C'; break;
			case 'T': d = 'A'; break;
		}

		reverse[len - k - 1] = d;
	}

	return reverse;
}

static char *revcomp_table(const char *forward, size_t len, char *reverse)
{
	static /*constexpr*/ char table[127];
	table['A'] = 'T';
	table['T'] = 'A';
	table['G'] = 'C';
	table['C'] = 'G';

	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		reverse[len - k - 1] = table[forward[k]];
	}

	return reverse;
}

static char *revcomp_reverse(const char *forward, size_t len, char *reverse)
{
	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		unsigned char d;

		switch (forward[len - k - 1]) {
			case 'A': d = 'T'; break;
			case 'C': d = 'G'; break;
			case 'G': d = 'C'; break;
			case 'T': d = 'A'; break;
		}

		reverse[k] = d;
	}

	return reverse;
}

static char *revcomp_twocase(const char *forward, size_t len, char *reverse)
{
	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		unsigned char c = forward[len - k - 1], d;

		if (c == 'G' || c == 'C') {
			d = 'C' + 'G' - c;
		} else {
			d = 'A' + 'T' - c;
		}

		//// the following switch statement is sematically identical, but much
		//// slower than the if above
		// switch (c) {
		// 	default:
		// 	case 'A':
		// 	case 'T':
		// 		d = 'A' + 'T' - c;
		// 		break;
		// 	case 'C':
		// 	case 'G':
		// 		d = 'C' + 'G' - c;
		// 		break;
		// }

		reverse[k] = d;
	}

	return reverse;
}

static char *revcomp_twiddle(const char *forward, size_t len, char *reverse)
{
	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		char c = forward[len - k - 1];

		reverse[k] = c ^= c & 2 ? 4 : 21;
	}

	return reverse;
}

static char *revcomp_subtraction(const char *forward, size_t len, char *reverse)
{
	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		char c = forward[len - k - 1];

		reverse[k] = (c & 2 ? 'G' + 'C' : 'A' + 'T') - c;
	}

	return reverse;
}

static char *revcomp_twostep(const char *forward, size_t len, char *reverse)
{
	reverse[len] = '\0';

	for (size_t k = 0; k < len; k++) {
		char c = forward[k];

		reverse[k] = c ^= c & 2 ? 4 : 21;
	}

	for (size_t k = 0; k < len / 2; k++) {
		std::swap(reverse[k], reverse[len - k - 1]);
	}

	return reverse;
}
