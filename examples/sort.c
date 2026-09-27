// sort - insertion sort over an array held in malloc'd memory
//
// Shows: a global, pointer arithmetic through subscripts, nested loops,
// and a check that the result is really sorted.
//
//     ./c4 examples/sort.c

#include <stdio.h>
#include <stdlib.h>

int seed;

// a small linear congruential generator, so every run prints the same
// numbers; the constants stay small enough not to overflow a 32-bit int
int
rnd()
{
	seed = (seed * 75 + 74) % 65537;
	return seed % 1000;
}

int
main()
{
	int *v, n, i, j, t;

	n = 20;
	if (!(v = (int *)malloc(n * sizeof(int)))) {
		printf("out of memory\n");
		return 1;
	}
	seed = 1;
	for (i = 0; i < n; ++i)
		v[i] = rnd();

	printf("before:");
	for (i = 0; i < n; ++i)
		printf(" %d", v[i]);
	printf("\n");

	for (i = 1; i < n; ++i) {
		t = v[i];
		j = i - 1;
		while (j >= 0 && v[j] > t) {
			v[j + 1] = v[j];
			--j;
		}
		v[j + 1] = t;
	}

	printf("after: ");
	for (i = 0; i < n; ++i)
		printf(" %d", v[i]);
	printf("\n");

	for (i = 1; i < n; ++i) {
		if (v[i - 1] > v[i]) {
			printf("NOT SORTED\n");
			return 1;
		}
	}
	printf("sorted\n");
	free(v);
	return 0;
}
