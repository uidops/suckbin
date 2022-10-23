#ifndef ARG_H
#define ARG_H

#define ARG_START for (int i = 1; i < argc; i++) { \
	if (argv[i][0] == '-') { \
		char _arg = argv[i][1]; \
		switch (argv[i][1]) {

#define ARG_END } \
	} \
}

#endif
