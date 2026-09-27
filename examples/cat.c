// cat - print a file, the way c4 reads its own source
//
// Shows: argc and argv, and the open, read and close opcodes.
//
//     ./c4 examples/cat.c README.md
//     ./c4 examples/cat.c examples/cat.c

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	char *buf;
	int fd, n, sz;

	// argv[0] is this source file, so the file to print is argv[1]
	if (argc < 2) {
		printf("usage: cat file\n");
		return 1;
	}
	if ((fd = open(argv[1], 0)) < 0) {
		printf("cannot open %s\n", argv[1]);
		return 1;
	}
	sz = 64 * 1024;
	if (!(buf = malloc(sz))) {
		printf("out of memory\n");
		return 1;
	}
	while ((n = read(fd, buf, sz - 1)) > 0) {
		buf[n] = 0;
		printf("%s", buf);
	}
	close(fd);
	free(buf);
	return 0;
}
