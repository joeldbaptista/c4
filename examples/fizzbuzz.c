// fizzbuzz - the classic exercise
//
// Shows: for, if/else chains, and the modulo operator.
//
//     ./c4 examples/fizzbuzz.c

#include <stdio.h>

int
main()
{
	int i;

	for (i = 1; i <= 30; ++i) {
		if (i % 15 == 0)
			printf("FizzBuzz\n");
		else if (i % 3 == 0)
			printf("Fizz\n");
		else if (i % 5 == 0)
			printf("Buzz\n");
		else
			printf("%d\n", i);
	}
	return 0;
}
