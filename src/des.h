#ifndef _DES_H
#define _DES_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
typedef unsigned char byte;
void DesEncrypt(byte *m, byte *k, byte*out);
void DesDecrypt(byte *m, byte *k, byte*out);
void TripleDesEncryptCBC(byte *m, int msg_len, byte *k, byte *out);
void TripleDesDecryptCBC(byte *m, int msg_len, byte *k, byte *out);
#ifdef __cplusplus
}
#endif
#endif
