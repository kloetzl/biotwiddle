#include <random>

static const size_t seed = 1729;

void gen(char *str, size_t length)
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

/** Fake the compiler into thinking *p is being read. Thus it cannot remove *p
 * as unused. */
void escape(void *p)
{
	asm volatile("" : : "g"(p) : "memory");
}
