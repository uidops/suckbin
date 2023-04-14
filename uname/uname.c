#include <sys/utsname.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "arg.h"

void		 put_(const char *, FILE *);
void		 usage(const char *__progname);

int
main(int argc, char **argv)
{
	unsigned char mflag = 0, nflag = 0, rflag = 0, sflag = 0, vflag=0;
	struct utsname uts;

	char *_ar_ = "";
	ARG_START
		case 'a':
			mflag = nflag = rflag = sflag = vflag = 1;
			break;
		case 'm':
			mflag = 1;
			break;
		case 'n':
			nflag = 1;
			break;
		case 'r':
			rflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'v':
			vflag = 1;
			break;
		default:
			usage(*argv);
			break;
	ARG_END
	if (*_rest_args != NULL)
		usage(*argv);

	ARG_REST_FREE
	if (uname(&uts) == -1)
		err(EXIT_FAILURE, "uname");

	if (sflag || !(nflag || rflag || vflag || mflag))
		put_(uts.sysname, stdout);

	if (nflag)
		put_(uts.nodename, stdout);

	if (rflag)
		put_(uts.release, stdout);

	if (vflag)
		put_(uts.version, stdout);

	if (mflag)
		put_(uts.machine, stdout);

	putchar('\n');
	return EXIT_SUCCESS;
}

void
put_(const char *s, FILE *fstream)
{
	static unsigned char _space = 0;
	if (_space)
		fputc(' ', fstream);

	fputs(s, fstream);
	_space = 1;
}

void
usage(const char *__progname)
{
	printf("usage: %s [-amnrsv]\n", __progname);
	exit(EXIT_FAILURE);
}
