Examples
========

Small programs that stay inside the subset of C that c4 understands. Run
them from the top of the repository, after `make`:

    ./c4 examples/fizzbuzz.c

`make examples` runs all of them in turn.

| File | What it shows |
| --- | --- |
| `fizzbuzz.c` | `for`, `if`/`else` chains, modulo |
| `fib.c` | recursion, and the same result computed iteratively |
| `control.c` | `for`, `while`, `break`, `continue`, `goto`, labels |
| `primes.c` | `malloc`, `free`, `memset`, a char buffer used as an array |
| `sort.c` | a global, subscripts into malloc'd memory, nested loops |
| `strings.c` | `slen`, `scopy`, `scmp` and `srev` written with char pointers |
| `calc.c` | a calculator built from one self-recursive function |
| `cat.c` | `argc` and `argv`, and the `open`, `read` and `close` opcodes |

Two of them take arguments:

    ./c4 examples/cat.c README.md
    ./c4 examples/calc.c "2 * (3 + 4)" "100 / 7"

Every example is also valid C for an ordinary compiler, so you can check
c4 against one:

    cc -w -o /tmp/sort examples/sort.c && /tmp/sort
    ./c4 examples/sort.c

The outputs agree, apart from the `exit(0) cycle = N` line that c4 prints
when a program finishes.

Two habits keep a program inside the subset. Declare every local at the
top of its function, because c4 accepts declarations nowhere else. Define
a function before it is called, because c4 has no forward declarations,
which also rules out mutual recursion; `calc.c` shows the way around
that.
