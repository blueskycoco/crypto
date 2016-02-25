CC = gcc
CFLAGS = -g -Wall
AFLAGS = rcs
AR = ar

default: des.a aes.a rc4.a
des.a: des.o
	$(AR) $(AFLAGS) des.a des.o
aes.a: aes.o
	$(AR) $(AFLAGS) aes.a aes.o
rc4.a: rc4.o
	$(AR) $(AFLAGS) rc4.a rc4.o

des.o: des.c des.h
	$(CC) $(CFLAGS) -c des.c
aes.o: aes.c aes.h
	$(CC) $(CFLAGS) -c aes.c
rc4.o: rc4.c rc4.h
	$(CC) $(CFLAGS) -c rc4.c

use_aes_cbc_enc: adapter.c adapter.h encrypt.c
	$(CC) $(CFLAGS) -DUSE_AES_CBC -o encrypt encrypt.c adapter.c -L. aes.a
use_aes_cbc_dec: adapter.c adapter.h decrypt.c
	$(CC) $(CFLAGS) -DUSE_AES_CBC -o decrypt decrypt.c adapter.c -L. aes.a

clean:
	$(RM) *.o crypto *~ *.a
