#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arg.h"

void		 usage(char *__progname);

int
main(int argc, char **argv)
{
	if (argc < 2)
		usage(*argv);

	ARG_START
		default:
			usage(*argv);
			break;
	ARG_END

	for (char **args = _rest_args; *args != NULL; args++) {
		unsigned int num = atoi(*(argv+1));
		while ((num = sleep(num)));
	}

	ARG_REST_FREE

	return EXIT_SUCCESS;
}


void
usage(char *__progname)
{
	printf("usage: %s [num ...]\n", __progname);
	exit(EXIT_FAILURE);
}
