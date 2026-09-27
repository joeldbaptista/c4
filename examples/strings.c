// strings - string routines written out by hand
//
// c4 has no string library, so these are the usual four written with
// plain char pointers.
//
// Shows: char pointers, pointer comparison, and functions returning
// values used inside expressions.
//
//     ./c4 examples/strings.c

#include <stdio.h>
#include <stdlib.h>

int
slen(char *s)
{
	int n;

	n = 0;
	while (*s) {
		++n;
		++s;
	}
	return n;
}

void
scopy(char *d, char *s)
{
	while (*s) {
		*d = *s;
		++d;
		++s;
	}
	*d = 0;
}

int
scmp(char *a, char *b)
{
	while (*a && *a == *b) {
		++a;
		++b;
	}
	return *a - *b;
}

void
srev(char *s)
{
	char *f;
	int t;

	f = s + slen(s) - 1;
	while (s < f) {
		t = *s;
		*s = *f;
		*f = t;
		++s;
		--f;
	}
}

int
main()
{
	char *a, *b;

	if (!(a = malloc(64)) || !(b = malloc(64))) {
		printf("out of memory\n");
		return 1;
	}
	scopy(a, "c in four functions");
	printf("a        = %s\n", a);
	printf("slen(a)  = %d\n", slen(a));

	scopy(b, a);
	printf("scmp     = %d %d\n", scmp(a, b), scmp(a, "zzz"));

	srev(b);
	printf("reversed = %s\n", b);
	srev(b);
	printf("back     = %s (scmp %d)\n", b, scmp(a, b));

	free(a);
	free(b);
	return 0;
}
