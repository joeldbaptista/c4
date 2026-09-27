# c4 - C in four functions
# See LICENSE for copyright and license details.

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

BIN = c4
SRC = c4.c

# c4.c defines int as long long, so main() does not have the signature a
# hosted implementation requires; -ffreestanding stops clang rejecting it.
# -Wno-format: %d is passed long long arguments throughout.
# -Wno-parentheses: assignment inside a condition is deliberate.
CC = cc
CFLAGS = -O2 -ffreestanding -Wall -Wno-format -Wno-parentheses
LDFLAGS =

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC)

# compile hello.c, then compile c4 with c4 and compile hello.c with that
test: $(BIN)
	./$(BIN) examples/hello.c
	./$(BIN) $(SRC) examples/hello.c
	./$(BIN) $(SRC) $(SRC) examples/hello.c

# run every example; cat.c needs a file to print
examples: $(BIN)
	./$(BIN) examples/fizzbuzz.c
	./$(BIN) examples/fib.c
	./$(BIN) examples/control.c
	./$(BIN) examples/primes.c
	./$(BIN) examples/sort.c
	./$(BIN) examples/strings.c
	./$(BIN) examples/calc.c
	./$(BIN) examples/cat.c examples/hello.c

clean:
	rm -f $(BIN)

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp -f $(BIN) $(DESTDIR)$(BINDIR)
	chmod 755 $(DESTDIR)$(BINDIR)/$(BIN)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(BIN)

.PHONY: all test examples clean install uninstall
