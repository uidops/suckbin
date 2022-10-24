#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		 usage(char *__progname);

int
main(int argc, char **argv)
{
	if (argc > 1)
		usage(*argv);

	fputs("\x1b[2J\x1b[H", stdout);
	return EXIT_SUCCESS;
}


void
usage(char *__progname)
{
	printf("usage: %s\n", __progname);
	exit(EXIT_FAILURE);
}
