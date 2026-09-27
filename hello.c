#include <stdio.h>

void
foo(int k)
{
	if (k & 1)
		printf("Hello there %d! You're odd!\n", k);
}

int main()
{
	int k;

	for (k = 0; k < 1000; ++k)
		foo(k);
	return 0;
}
