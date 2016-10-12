double transversions_mutations(const char *subject, size_t length,
							  const char *query)
{
	size_t mutations = 0;
	const char *sbj = subject, *qry = query;

	for (; *sbj; sbj++, qry++) {
		if (*sbj != *qry) {
			mutations++;
		}
	}

	return static_cast<double>(mutations) / length;
}

double transversions_mutations_length(const char *subject, size_t length,
									 const char *query)
{
	size_t mutations = 0;

	for (size_t k = 0; k < length; k++) {
		if (subject[k] != query[k]) {
			mutations++;
		}
	}

	return static_cast<double>(mutations) / length;
}

double transversions_transversions(const char *subject, size_t length,
								  const char *query)
{
	static const auto is_purine = [](char c) { return c == 'A' || c == 'G'; };

	size_t transversions = 0;
	const char *sbj = subject, *qry = query;

	for (; *sbj; sbj++, qry++) {
		if ((is_purine(*sbj) && !is_purine(*qry)) ||
			(!is_purine(*sbj) && is_purine(*qry))) {
			transversions++;
		}
	}

	return static_cast<double>(transversions) / length;
}

double transversions_twiddle_length(const char *subject, size_t length,
								   const char *query)
{
	size_t transversions = 0;

	for (size_t k = 0; k < length; k++) {
		if (((subject[k] + 1) ^ (query[k] + 1)) & 4) {
			transversions++;
		}
	}

	return static_cast<double>(transversions) / length;
}

double transversions_builtin(const char *subject, size_t length,
							const char *query)
{
	size_t transversions = 0;

	for (size_t k = 0; k < length; k++) {
		auto c1 = __builtin_popcount(subject[k]);
		auto c2 = __builtin_popcount(query[k]);
		// if ((c1 == 3 && c2 != 3) || (c1 != 3 && c2 == 3)) {
		if ((c1 == 3) ^ (c2 == 3)) {
			transversions++;
		}
	}

	return static_cast<double>(transversions) / length;
}
