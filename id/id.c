#include <sys/types.h>
#include <err.h>
#include <errno.h>
#include <grp.h>
#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arg.h"

void		 usage(char *__progname);

int
main(int argc, char **argv)
{
	unsigned char flag = 0;
	struct passwd *pwu = NULL;
	struct group *pwg = NULL;

	char *_ar_ = "";
	ARG_START
		case 'g':
			flag |= 0x01;
			break;
		case 'u':
			flag |= 0x02;
			break;
		case 'G':
			flag |= 0x04;
			break;
		case 'n':
			flag |= 0x08;
			break;
		default:
			usage(*argv);
			break;
	ARG_END

 	if ((flag & 0x07) & ((flag & 0x07) - 1))
		usage(*argv);

	if (*_rest_args == NULL) {
		errno = 0;
		pwu = getpwuid(getuid());
		if (pwu == NULL) {
			if (errno)
				err(EXIT_FAILURE, "%u", getuid());
			else
				errx(EXIT_FAILURE, "%u: no such user", getuid());

		}

	} else if ((unsigned)**_rest_args-'0' < 10) {
		errno = 0;
		pwu = getpwuid(strtol(*_rest_args, NULL, 10));
		if (pwu == NULL) {
			if (errno)
				err(EXIT_FAILURE, "%u", strtol(*_rest_args, NULL, 10));
			else
				errx(EXIT_FAILURE, "%u: no such user", strtol(*_rest_args, NULL, 10));

		}

	} else {
		errno = 0;
		pwu = getpwnam(*_rest_args);
		if (pwu == NULL) {
			if (errno)
				err(EXIT_FAILURE, "%s", *_rest_args);
			else
				errx(EXIT_FAILURE, "%s: no such user", *_rest_args);

		}

	}

	errno = 0;
	if ((pwg = getgrgid(pwu->pw_gid)) == NULL) {
		if (errno)
			err(EXIT_FAILURE, "%u", pwu->pw_gid);
		else
			errx(EXIT_FAILURE, "%u: no such gruop", pwu->pw_gid);
	}

	if (flag & 0x01) {
		errno = 0;
		if (flag & 0x08)
			printf("%s", pwg->gr_name);
		else
			printf("%u", pwu->pw_gid);

	} else if (flag & 0x02) {
		if (flag & 0x08)
			printf("%s", pwu->pw_name);
		else
			printf("%u", pwu->pw_uid);

	} else if (flag & 0x04) {
		gid_t *groups = calloc(NGROUPS_MAX, sizeof(gid_t));
		int ngroups = NGROUPS_MAX;
		getgrouplist(pwu->pw_name, pwu->pw_gid, groups, &ngroups);
		for (int i = 0; i < ngroups; i++) {
			if (flag & 0x08) {
				errno = 0;
				if ((pwg = getgrgid(groups[i])) == NULL) {
					if (errno)
						err(EXIT_FAILURE, "%u", pwu->pw_gid);
					else
						errx(EXIT_FAILURE, "%u: no such group", pwu->pw_gid);
				}

				printf((i < ngroups - 1) ? "%s " : "%s", pwg->gr_name);

			} else
				printf((i < ngroups - 1) ? "%u " : "%u", groups[i]);

		}

		free(groups);

	} else {
		gid_t *groups = calloc(NGROUPS_MAX, sizeof(gid_t));
		int ngroups = NGROUPS_MAX;

		printf("uid=%u(%s) gid=%u(%s) groups=", pwu->pw_uid, pwu->pw_name, pwg->gr_gid, pwg->gr_name);
		getgrouplist(pwu->pw_name, pwu->pw_gid, groups, &ngroups);
		for (int i = 0; i < ngroups; i++) {
			errno = 0;
			if ((pwg = getgrgid(groups[i])) == NULL) {
				if (errno)
					err(EXIT_FAILURE, "%u", pwu->pw_gid);
				else
					errx(EXIT_FAILURE, "%u: no such group", pwu->pw_gid);
			}

			printf((i < ngroups - 1) ? "%u(%s)," : "%u(%s)", groups[i], pwg->gr_name);

		}

		free(groups);

	}

	ARG_REST_FREE

	putchar('\n');
	return EXIT_SUCCESS;
}


void
usage(char *__progname)
{
	printf("usage: %s [-n] [-g | -u | -G] [user | uid]\n", __progname);
	exit(EXIT_FAILURE);
}
