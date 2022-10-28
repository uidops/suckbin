include ../config.mk

IDIR =../include
CFLAGS += -I$(IDIR)

whoami:
	$(CC) $(CFLAGS) $(LDFLAGS) -o whoami whoami.c

clean:
	$(RM) -f whoami
