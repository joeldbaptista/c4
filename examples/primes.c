// primes - the sieve of Eratosthenes
//
// Shows: malloc and free, memset, a char buffer used as an array, and
// continue.
//
//     ./c4 examples/primes.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	char *sieve;
	int n, i, j, num;

	n = 200;
	if (!(sieve = malloc(n))) {
		printf("out of memory\n");
		return 1;
	}
	memset(sieve, 0, n);

	// sieve[i] becomes 1 once i is known to be composite
	for (i = 2; i * i < n; ++i) {
		if (sieve[i])
			continue;
		for (j = i * i; j < n; j = j + i)
			sieve[j] = 1;
	}

	num = 0;
	for (i = 2; i < n; ++i) {
		if (sieve[i])
			continue;
		printf("%d ", i);
		++num;
	}
	printf("\n%d primes below %d\n", num, n);
	free(sieve);
	return 0;
}
