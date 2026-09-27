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

	k = 0;
	while (k < 1000) {
		foo(k);
		++k;
	}
	return 0;
}
