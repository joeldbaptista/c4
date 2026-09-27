c4 - C in four functions
========================

An exercise in minimalism.

c4 is a compiler and virtual machine for a small subset of C, written by
Robert Swierczek. It is small enough to compile itself: the compiler reads
`c4.c`, emits bytecode for its own virtual machine, and then runs that
bytecode. The whole thing is one file and four functions.

Original code [here](https://github.com/rswier/c4).

Build
-----

    make

This produces the `c4` binary. Other targets are `test`, `clean`, `install`
and `uninstall`; that list is complete.

    make test

`make test` compiles `hello.c`, then compiles c4 with c4 and uses the result
to compile `hello.c` again, then repeats that one level deeper.

The build uses `-ffreestanding`. This is not an optimisation choice. `c4.c`
contains `#define int long long`, so `main` does not have the signature a
hosted C implementation requires, and clang rejects the file without that
flag.


Usage
-----

    c4 [-s] [-d] file ...

c4 compiles `file` and runs it immediately. There is no object file and no
linker. Arguments after `file` are passed to the compiled program, so `file`
itself becomes `argv[0]` of that program.

    ./c4 hello.c              compile and run hello.c
    ./c4 c4.c hello.c         run c4 under c4, compiling hello.c
    ./c4 c4.c c4.c hello.c    one level deeper again

`-s` prints each source line followed by the instructions emitted for it,
then exits without running the program.

`-d` prints every instruction as the virtual machine executes it. Output is
large, so redirect it.

When a program finishes, c4 prints a line of the form `exit(0) cycle = N`,
where `N` is the number of instructions the virtual machine executed.


The four functions
------------------

`next` is the lexer. It reads one token, and it also prints the source and
the disassembly when `-s` is set.

`expr` parses expressions by precedence climbing and emits code as it goes.
There is no syntax tree.

`stmt` parses statements. It recurses into `expr`.

`main` parses declarations, drives the other three, and then interprets the
bytecode it produced.


The language
------------

The supported subset is small. The following list of features is complete:

- Types `char`, `int`, `void`, and pointers to them.
- `enum`, with optional explicit values.
- `if`, `else`, `while`, `return`, blocks, expression statements, and the
  empty statement.
- The usual operators, including `? :`, `++`, `--`, `sizeof`, casts, and
  array subscripting.
- Function definitions, including recursion.

Everything else in C is absent. In particular this list of omissions covers
the ones you are most likely to reach for first, although it is not
exhaustive: `for`, `do`, `switch`, `break`, `continue`, `goto`, `struct`,
`union`, `typedef`, floating point, unsigned types, `static`, `const`,
function prototypes, global initialisers, and local declarations anywhere
but the top of a function body.

Three further restrictions are worth stating, because they are easy to trip
over:

- There is no preprocessor. A `#` and the rest of its line are skipped, so
  `#include` and `#define` have no effect on the compiled program.
- Only `//` comments are recognised. `/* */` is a syntax error.
- In string and character literals, only `\n` is translated. Any other
  escape yields the character after the backslash, so `\t` is `t`.

Nine library functions are available, and they are reached as opcodes rather
than through a header: `open`, `read`, `close`, `printf`, `malloc`, `free`,
`memset`, `memcmp` and `exit`. `printf` takes at most six arguments in
total, that is a format string and five values; a sixth value prints
rubbish rather than raising an error.


The virtual machine
-------------------

The machine has four registers: a program counter, a stack pointer, a base
pointer, and a general register `a` that holds the result of every
expression. It has 39 opcodes, in three groups:

- 14 for memory access and control flow, `LEA` through `PSH`.
- 16 arithmetic and logical operations, `OR` through `MOD`.
- 9 that call into the host C library, `OPEN` through `EXIT`.

Because there is one result register, an expression compiles to code that
pushes its left operand and leaves its right operand in `a`. Every binary
operator then pops one value and combines it with `a`.

The compiler allocates four fixed pools of 256 KB each, for the symbol
table, the emitted code, the data segment, and the stack. It never frees
them, and it never grows them.


Conventions
-----------

`STYLE.md` describes the C style this repository follows, which is the
suckless style. `PRINCIPLES.md` records the programming principles the code
is meant to reflect.


Licence
-------

GPL version 2. See `LICENSE`.
