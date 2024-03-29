#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arg.h"

void		 usage(char *__progname);

int
main(int argc, char **argv)
{
	unsigned char flag = 1;

	char *_ar_ = "";
	ARG_START
		case 'L':
			flag ^= 1;
			break;
		case 'P':
			break;
		default:
			usage(*argv);
			break;
	ARG_END
	ARG_REST_FREE

	char *cwd;
	if (flag) {
		cwd = calloc(PATH_MAX, sizeof(char));
		if (cwd == NULL)
			err(EXIT_FAILURE, "calloc");

		cwd = getcwd(cwd, PATH_MAX);
	} else {
		cwd = getenv("PWD");
	}

	if (cwd == NULL)
		errx(EXIT_FAILURE, "can't determine cwd");

	puts(cwd);
	if (flag)
		free(cwd);

	return EXIT_SUCCESS;
}


void
usage(char *__progname)
{
	printf("usage: %s [-LP]\n", __progname);
	exit(EXIT_FAILURE);
}
