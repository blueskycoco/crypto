
#ifndef _AES_H_
#define _AES_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>


// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES128 encryption in CBC-mode of operation and handles 0-padding.
// ECB enables the basic ECB 16-byte block algorithm. Both can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
  #define CBC 1
#endif

#ifndef ECB
  #define ECB 1
#endif



#if defined(ECB) && ECB

void AES128_ECB_encrypt(unsigned char* input, const unsigned char* key, unsigned char *output);
void AES128_ECB_decrypt(unsigned char* input, const unsigned char* key, unsigned char *output);

#endif // #if defined(ECB) && ECB


#if defined(CBC) && CBC

void AES128_CBC_encrypt_buffer(unsigned char* output, unsigned char* input, unsigned long length, const unsigned char* key, const unsigned char* iv);
void AES128_CBC_decrypt_buffer(unsigned char* output, unsigned char* input, unsigned long length, const unsigned char* key, const unsigned char* iv);

#endif // #if defined(CBC) && CBC

#ifdef __cplusplus
}
#endif

#endif //_AES_H_
