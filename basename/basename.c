#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arg.h"

char		*fname(const char *, size_t);
void		 usage(char *);

int
main(int argc, char **argv)
{
	char *_ar_ = "", *bname = NULL;
	size_t n1 = 0, n2 = 0;

	ARG_START
		default:
			usage(*argv);
			break;
	ARG_END

	if (_n < 1 || _n > 2)
		usage(*argv);

	n1 = strlen(*_rest_args);
	bname = fname(*_rest_args, n1);
	if (_n > 1) {
		n2 = strlen(*(_rest_args + 1));
		n1 = strlen(bname);
		if (! strncmp((bname + n1 - n2), *(_rest_args + 1), n2))
			bname[n1 - n2] = 0x00;
	}

	printf("%s\n", bname);

 	ARG_REST_FREE
	return EXIT_SUCCESS;
}


char *
fname(const char *path, size_t n)
{
	if (n == 0) return NULL;
	for (; *(path + n) != '/'; n--);
	return (char *) (path + ++n);
}


void
usage(char *__progname)
{
	printf("usage: %s path [suffix]\n", __progname);
	exit(EXIT_FAILURE);
}
