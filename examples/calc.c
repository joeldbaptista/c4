// calc - a four-function calculator
//
// c4 has no forward declarations, so a parser cannot be split into
// mutually recursive functions. This uses the same trick c4 itself
// uses: one function that calls itself with a precedence level.
//
// Shows: a global parse position, self-recursion, and character
// handling with a char pointer.
//
//     ./c4 examples/calc.c
//     ./c4 examples/calc.c "2 * (3 + 4)" "100 / 7"

#include <stdio.h>
#include <stdlib.h>

char *pos;      // the character the parser is looking at

void
skip()
{
	while (*pos == ' ')
		++pos;
}

// lev is the lowest precedence this call will consume: 1 accepts + and
// -, 2 accepts * and /, and 3 accepts neither, so it reads one operand
int
eval(int lev)
{
	int v, c;

	skip();
	if (*pos == '(') {
		++pos;
		v = eval(1);
		skip();
		if (*pos == ')') {
			++pos;
		} else {
			printf("missing )\n");
			exit(1);
		}
	} else if (*pos == '-') {
		++pos;
		v = -eval(3);
	} else if (*pos >= '0' && *pos <= '9') {
		v = 0;
		while (*pos >= '0' && *pos <= '9') {
			v = v * 10 + *pos - '0';
			++pos;
		}
	} else {
		printf("bad character\n");
		exit(1);
	}

	skip();
	while (1) {
		c = *pos;
		if (lev <= 2 && (c == '*' || c == '/')) {
			++pos;
			if (c == '*')
				v = v * eval(3);
			else
				v = v / eval(3);
		} else if (lev <= 1 && (c == '+' || c == '-')) {
			++pos;
			if (c == '+')
				v = v + eval(2);
			else
				v = v - eval(2);
		} else {
			return v;
		}
		skip();
	}
	return v;
}

int
main(int argc, char **argv)
{
	char *s;
	int i;

	if (argc > 1) {
		for (i = 1; i < argc; ++i) {
			pos = argv[i];
			printf("%s = %d\n", argv[i], eval(1));
		}
		return 0;
	}

	s = "1 + 2 * 3";
	pos = s;
	printf("%s = %d\n", s, eval(1));

	s = "2 * (3 + 4) - 5";
	pos = s;
	printf("%s = %d\n", s, eval(1));

	s = "100 / 7 / 2";
	pos = s;
	printf("%s = %d\n", s, eval(1));

	s = "-3 * -4 + 10 / 4";
	pos = s;
	printf("%s = %d\n", s, eval(1));
	return 0;
}
