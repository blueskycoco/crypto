#ifndef _RC4_H_
#define _RC4_H_

#ifdef __cplusplus
extern "C" {
#endif

#define RC4_KEY JOHN_RC4_KEY
#define RC4_INT JOHN_RC4_INT
#define RC4_set_key JOHN_RC4_set_key
#define RC4 JOHN_RC4

#define JOHN_RC4_INT unsigned int

typedef struct rc4_key
{
	RC4_INT state[256];
	RC4_INT x;
	RC4_INT y;
} RC4_KEY;

extern void RC4(RC4_KEY *key, RC4_INT len, const unsigned char *indata, unsigned char *outdata);
extern void RC4_set_key(RC4_KEY *key, RC4_INT len, const unsigned char *data);
#ifdef __cplusplus
}
#endif

#endif //_RC4_H_
