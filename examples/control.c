// control - every loop and jump c4 understands
//
// Shows: for, while, break, continue, goto, and a label.
//
//     ./c4 examples/control.c

#include <stdio.h>

int
main()
{
	int i, j;

	// break leaves the innermost loop only
	printf("break:    ");
	for (i = 0; i < 10; ++i) {
		if (i == 5)
			break;
		printf("%d ", i);
	}
	printf("\n");

	// continue skips the rest of one pass, but the increment still runs
	printf("continue: ");
	for (i = 0; i < 10; ++i) {
		if (i % 2)
			continue;
		printf("%d ", i);
	}
	printf("\n");

	// while does the same work, with the step written out
	printf("while:    ");
	i = 0;
	while (i < 10) {
		printf("%d ", i);
		i = i + 2;
	}
	printf("\n");

	// goto leaves two loops at once, which break cannot do
	for (i = 1; i < 10; ++i) {
		for (j = 1; j < 10; ++j) {
			if (i * j == 42)
				goto found;
		}
	}
	printf("goto:     no pair found\n");
	return 0;
found:
	printf("goto:     %d * %d = 42\n", i, j);

	// a loop built from a label and a goto, which is what the
	// compiler emits for the loops above
	i = 0;
again:
	if (i < 3) {
		printf("manual:   %d\n", i);
		++i;
		goto again;
	}
	return 0;
}
