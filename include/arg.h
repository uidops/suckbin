#ifndef ARG_H
#define ARG_H

#define ARG_START size_t _n = 0; \
	char **_rest_args = calloc(argc, sizeof(char *)); \
	for (int i = 1; i < argc; i++) { \
		if (argv[i][0] != '-' && argv[i-1][0] != '-') { \
			_rest_args[_n++] = argv[i]; \
			continue; \
		} else if (argv[i][0] == '-') { \
			char *_arg = argv[i+1]; \
			switch (argv[i][1]) {

#define ARG_END } \
	} \
}

#define ARG_REST_FREE free(_rest_args);

#endif
