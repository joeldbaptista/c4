// fib - Fibonacci numbers, twice over
//
// Shows: recursion, and the same result computed iteratively.
//
//     ./c4 examples/fib.c

#include <stdio.h>

int
fib(int n)
{
	if (n < 2)
		return n;
	return fib(n - 1) + fib(n - 2);
}

int
main()
{
	int i, a, b, t;

	printf("recursive:");
	for (i = 0; i < 15; ++i)
		printf(" %d", fib(i));
	printf("\n");

	printf("iterative:");
	a = 0;
	b = 1;
	for (i = 0; i < 15; ++i) {
		printf(" %d", a);
		t = a + b;
		a = b;
		b = t;
	}
	printf("\n");
	return 0;
}
