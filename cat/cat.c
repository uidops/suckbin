#include <sys/stat.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arg.h"

void		 usage(char *__progname);

int
main(int argc, char **argv)
{
	int fd = STDIN_FILENO;
	size_t nb = 0;
	ssize_t nr = 0;
	char *buff = NULL;
	struct stat statbuf;

	ARG_START
		default:
			usage(*argv);
			break;
	ARG_END

	char **args = _rest_args;
	if (*args == NULL)
		*args = "-";

	for (; *args != NULL; args++) {
		if (!strcmp(*args, "-")) {
			fd = STDIN_FILENO;
			*args = "<stdin>";
		} else {
			fd = open(*args, O_RDONLY);
			if (fd == -1) {
				warn("%s", *args);
				continue;
			}
		}

		memset(&statbuf, 0x00, sizeof(struct stat));
		fstat(fd, &statbuf);
		nb = statbuf.st_blksize > BUFSIZ ? statbuf.st_blksize : BUFSIZ;

		buff = malloc((nb + 1)*sizeof(char));
		if (buff == NULL) {
			warn("malloc");
			continue;
		}

		while ((nr = read(fd, buff, nb)) > 0) {
			buff[nr] = 0x00;
			if (write(STDOUT_FILENO, buff, nr) != nr) {
				warn("%s", *args);
				break;
			}
		}

		free(buff);
	}

	ARG_REST_FREE
	return EXIT_SUCCESS;
}


void
usage(char *__progname)
{
	printf("usage: %s [file ...]\n", __progname);
	exit(EXIT_FAILURE);
}
