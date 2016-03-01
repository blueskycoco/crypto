#ifndef _ADPATER_H
#define _ADAPTER_H
#ifdef __cplusplus
extern "C" {
#endif
#if defined(USE_AES_CBC) || defined(USE_AES_ECB)
#include "aes.h"
#include <stdio.h>
#include <string.h>
typedef unsigned char byte;
#endif
#if defined(USE_DES) || defined(USE_3DES)
#include "des.h"
#endif
#if defined(USE_RC4)
#include "rc4.h"
#include <stdio.h>
#include <string.h>
typedef unsigned char byte;
#endif
int encrypt_mg(const char* hexKey, const char* hexContent, byte** ppOutput, int* pLength);
int decrypt_mg(const char* hexKey, const char* hexContent, byte** ppOutput, int* pLength);
#ifdef __cplusplus
}
#endif
#endif
