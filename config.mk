CC ?= cc
LD ?= ld
RM ?= rm

CFLAGS ?= -O3 -pipe -march=native -fPIC
LDFLAGS ?= -Wl,-O3,--hash-style=sysv,--as-needed,-z,relo,-z,now,-z,noexecstack,--gc-sections,--sort-common -pie -s
