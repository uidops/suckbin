#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arg.h"

void		 usage(void);

int
main(int argc, char **argv)
{
	unsigned char flag = 1;
	ARG_START
		case 'L':
			flag ^= 1;
			break;
		case 'P':
			break;
		default:
			usage();
			break;
	ARG_END

	char *cwd;
	if (flag) {
		cwd = calloc(PATH_MAX, sizeof(char));
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
usage(void)
{
	puts("PWD\n");
	puts(" -L: Logical");
	puts(" -P: Phisical");
	exit(EXIT_FAILURE);
}
