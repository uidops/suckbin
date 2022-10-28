#include <err.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void		 usage(char *__progname);

int
main(int argc, char **argv)
{
	if (argc > 1)
		usage(*argv);

	uid_t uid = geteuid();
	struct passwd *pwd = getpwuid(uid);
	if (pwd == NULL) {
		if (!errno)
			errx(EXIT_FAILURE, "%d: no such user", uid);
		err(EXIT_FAILURE, "%d", uid);
	}

	puts(pwd->pw_name);

	return EXIT_SUCCESS;
}


void
usage(char *__progname)
{
	printf("usage: %s\n", __progname);
	exit(EXIT_FAILURE);
}
