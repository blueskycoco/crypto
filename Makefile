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

enc: adapter.c adapter.h encrypt.c
ifeq ($(CRYPTO),USE_AES_CBC)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o encrypt encrypt.c adapter.c -L. aes.a
endif
ifeq ($(CRYPTO),USE_AES_ECB)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o encrypt encrypt.c adapter.c -L. aes.a
endif
ifeq ($(CRYPTO),USE_DES)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o encrypt encrypt.c adapter.c -L. des.a
endif
ifeq ($(CRYPTO),USE_3DES)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o encrypt encrypt.c adapter.c -L. des.a
endif
ifeq ($(CRYPTO),USE_RC4)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o encrypt encrypt.c adapter.c -L. rc4.a
endif
dec: adapter.c adapter.h decrypt.c
ifeq ($(CRYPTO),USE_AES_CBC)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o decrypt decrypt.c adapter.c -L. aes.a
endif
ifeq ($(CRYPTO),USE_AES_ECB)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o decrypt decrypt.c adapter.c -L. aes.a
endif
ifeq ($(CRYPTO),USE_DES)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o decrypt decrypt.c adapter.c -L. des.a
endif
ifeq ($(CRYPTO),USE_3DES)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o decrypt decrypt.c adapter.c -L. des.a
endif
ifeq ($(CRYPTO),USE_RC4)
	$(CC) $(CFLAGS) -D$(CRYPTO) -o decrypt decrypt.c adapter.c -L. rc4.a
endif

clean:
	$(RM) *.o crypto *~ *.a
