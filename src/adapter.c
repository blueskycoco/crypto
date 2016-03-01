#include "adapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAILED	1
#define SUCCESS	0
#define AES_BLOCK_LEN 16
#ifdef LOG_OUT
#ifdef ANDROID
#include <android/log.h>
#define LOG_TAG NULL
#define LOG_INFO 3	//ANDROID_LOG_DEBUG
#define DEBUG(...) __android_log_print(LOG_INFO, LOG_TAG, __VA_ARGS__) 
#else
#define DEBUG printf
#endif
#else
#define DEBUG 
#endif
#ifdef LOG_OUT
#define _xc_preserve_interface
#endif
char hex_to_char(char hex)
{
	char tmp = 0;
	if(hex >= '0' && hex <= '9')
		tmp = hex-'0';
	else if(hex >= 'a' && hex <= 'f')
		tmp = hex-'a' +10;
	else if(hex >= 'A' && hex <= 'F')
		tmp = hex-'A'+10;
	return tmp;
}
void HexToChar(const char *hex,char **out)
{
	int i = 0;
	//DEBUG("HexToChar len %d\n",strlen(hex));
	*out = (char *)malloc(strlen(hex)/2 + 1);
	memset(*out,'\0',strlen(hex)/2 + 1);
	for(i = 0;i < strlen(hex);i=i+2)
	{
		(*out)[i/2] = (hex_to_char(hex[i]) * 16 ) + hex_to_char(hex[i+1]);
	}
	//DEBUG("orignal hex %s\n",hex);
	//DEBUG("after to char %s\n",*out);
}
_xc_preserve_interface
int encrypt_mg(const char* hexKey, const char* hexContent, byte** ppOutput, int* pLength)
{
	if(hexKey == NULL || hexContent == NULL || pLength == NULL || strlen(hexKey) != 64)
	{
		if(hexKey == NULL)
			DEBUG("hexKey is NULL\n");

		if(hexContent == NULL)
			DEBUG("hexContent is NULL\n");

		if(pLength == NULL)
			DEBUG("pLength is NULL\n");

		if(strlen(hexKey) != 64)
			DEBUG("hexKey len is not 64 , %d\n",(int)strlen(hexKey));
		
		return FAILED;
	}
	char *key = NULL;
	char *encrypt = NULL;
	HexToChar(hexKey, &key);
	HexToChar(hexContent, &encrypt);
	if(key == NULL || encrypt == NULL)
	{
		if(key)
		{
			free(key);
			key = NULL;
		}
		else
			DEBUG("HexToChar key failed\n");

		if(encrypt)
		{
			free(encrypt);
			encrypt = NULL;
		}
		else
			DEBUG("HexToChar encrypt failed\n");
		return FAILED;
	}
#if defined(USE_AES_CBC) || defined(USE_AES_ECB)
	unsigned long length = strlen(hexContent) / 2;
	unsigned long nlen = ((length % AES_BLOCK_LEN) == 0) ? length : (length + AES_BLOCK_LEN - length % AES_BLOCK_LEN);
#ifdef USE_AES_CBC
	byte *encrypt1=NULL;
	if(nlen!=length)
	{
		encrypt1 = (byte *)malloc(nlen+1);
		memset(encrypt1,'\0',nlen+1);
		memcpy(encrypt1,encrypt,length);
		memset(encrypt1+length,'\0',nlen-length);
	}
	else
	{
		encrypt1 = (byte *)malloc(nlen+1);
		memset(encrypt1,'\0',nlen+1);
		memcpy(encrypt1,encrypt,nlen);
	}
#endif
	*ppOutput = (byte *)malloc(nlen+1);
	memset(*ppOutput,'\0',nlen+1);
	*pLength = nlen;
#ifdef USE_AES_CBC
	AES128_CBC_encrypt_buffer(*ppOutput, (unsigned char*)encrypt1, nlen, (const unsigned char *)key, (const unsigned char *)(key + AES_BLOCK_LEN));
	free(encrypt1);
	encrypt1=NULL;
#else
	AES128_ECB_encrypt((unsigned char*)encrypt, (const unsigned char *)key, *ppOutput);
#endif
#endif

#if defined(USE_DES) || defined(USE_3DES)
	unsigned long nlen = strlen(hexContent)/2;
	
#ifdef USE_DES
	if(nlen<8)
	{	
		*ppOutput = (byte *)malloc(8+1);
		memset(*ppOutput,'\0',8+1);
		*pLength = 8;
	}
	else
	{
		*ppOutput = (byte *)malloc((nlen/8+1)*8);
		memset(*ppOutput,'\0',(nlen/8+1)*8);
		*pLength = (nlen/8+1)*8;
	}
	int i=0;
	byte *p=*ppOutput;
	for(i=0;i<nlen/8;i++)
	{
	DesEncrypt((byte *)encrypt+8*i, (byte *)key, p);
	p=p+8;
	}
	if(nlen%8!=0)
		DesEncrypt((byte *)encrypt+i*8, (byte *)key, p);
#else
	char *encrypt1=NULL;
	if(nlen%8!=0)
	{
		*ppOutput=(byte *)malloc(nlen+8-nlen%8+1);
		memset(*ppOutput,'\0',nlen+8-nlen%8+1);
		encrypt1=(char *)malloc(nlen+8-nlen%8+1);
		memset(encrypt1,'\0',nlen+8-nlen%8+1);
		memcpy(encrypt1,encrypt,nlen);
		memset(encrypt1+nlen,'\0',8-nlen%8);
		nlen=nlen+8-nlen%8;
	}
	else
	{
		*ppOutput=(byte *)malloc(nlen+1);
		memset(*ppOutput,'\0',nlen+1);
		encrypt1=(char *)malloc(nlen+1);
		memset(encrypt1,'\0',nlen+1);
		memcpy(encrypt1,encrypt,nlen);
	}
	TripleDesEncryptCBC((byte *)encrypt1, nlen, (byte *)key, *ppOutput);
	free(encrypt1);
	encrypt1=NULL;
#endif
#endif

#ifdef USE_RC4
	RC4_KEY rc4_key;
	*ppOutput = (byte *)malloc(strlen(hexContent)/2+1);
	memset(*ppOutput,'\0',strlen(hexContent)/2+1);
	*pLength=strlen(hexContent)/2;
	RC4_set_key(&rc4_key,32,(const unsigned char *)key);
	RC4(&rc4_key,strlen(hexContent)/2,(const unsigned char *)encrypt,*ppOutput);
#endif
	if(key)
	{
		free(key);
		key = NULL;
	}
	if(encrypt)
	{
		free(encrypt);
		encrypt = NULL;
	}

	if(strlen((char *)*ppOutput) != 0)
	{
		*pLength = strlen((char *)*ppOutput);
		return SUCCESS;
	}
	DEBUG("*pLength %d <> %d\n",(int)*pLength,(int)strlen((char *)*ppOutput));
	return FAILED;
}
_xc_preserve_interface
int decrypt_mg(const char* hexKey, const char* hexContent, byte** ppOutput, int* pLength)
{
	if(hexKey == NULL || hexContent == NULL || pLength == NULL || strlen(hexKey) != 64)
	{
		if(hexKey == NULL)
			DEBUG("hexKey is NULL\n");

		if(hexContent == NULL)
			DEBUG("hexContent is NULL\n");

		if(pLength == NULL)
			DEBUG("pLength is NULL\n");

		if(strlen(hexKey) != 64)
			DEBUG("hexKey len is not 64 , %d\n",(int)strlen(hexKey));
		
		return FAILED;
	}
	char *key = NULL;
	char *encrypt = NULL;
	HexToChar(hexKey, &key);
	HexToChar(hexContent, &encrypt);
	if(key == NULL || encrypt == NULL)
	{
		if(key)
		{
			free(key);
			key = NULL;
		}
		else
			DEBUG("HexToChar key failed\n");

		if(encrypt)
		{
			free(encrypt);
			encrypt = NULL;
		}
		else
			DEBUG("HexToChar encrypt failed\n");
		return FAILED;
	}
#if defined(USE_AES_CBC) || defined(USE_AES_ECB)
	unsigned long length = strlen(hexContent) / 2;
	unsigned long nlen = ((length % AES_BLOCK_LEN) == 0) ? length : (length + AES_BLOCK_LEN - length % AES_BLOCK_LEN);
	*ppOutput = (byte *)malloc(nlen+1);
	memset(*ppOutput,'\0',nlen+1);
#ifdef USE_AES_CBC
		byte *encrypt1=NULL;
		if(nlen!=length)
		{
			encrypt1 = (byte *)malloc(nlen+1);
			memset(encrypt1,'\0',nlen+1);
			memcpy(encrypt1,encrypt,length);
			memset(encrypt1+length,'\0',nlen-length);
		}
		else
		{
			encrypt1 = (byte *)malloc(nlen+1);
			memset(encrypt1,'\0',nlen+1);
			memcpy(encrypt1,encrypt,nlen);
		}
#endif
#ifdef USE_AES_CBC
	AES128_CBC_decrypt_buffer(*ppOutput, (unsigned char*)encrypt, nlen, (const unsigned char *)key, (const unsigned char *)(key + AES_BLOCK_LEN));
	free(encrypt1);
	encrypt1=NULL;
#else
	AES128_ECB_decrypt((unsigned char *)encrypt, (const unsigned char *)key, *ppOutput);
#endif
#endif

#if defined(USE_DES) || defined(USE_3DES)
	unsigned long nlen = strlen(hexContent)/2;
	
#ifdef USE_DES
	if(nlen<8)
	{
		*ppOutput = (byte *)malloc(8+1);
		memset(*ppOutput,'\0',8+1);
		*pLength = 8;
	}
	else
	{
		*ppOutput = (byte *)malloc((nlen/8+1)*8);
		memset(*ppOutput,'\0',(nlen/8+1)*8);
		*pLength = (nlen/8+1)*8;
	}
	int i=0;
	byte *p=*ppOutput;
	for(i=0;i<nlen/8;i++)
	{
		DesDecrypt((byte *)encrypt+8*i, (byte *)key, p);
		p=p+8;
	}
	if(nlen%8!=0)
		DesEncrypt((byte *)encrypt+8*i, (byte *)key, p);	
#else
	char *encrypt1=NULL;
	if(nlen%8!=0)
	{
		*ppOutput=(byte *)malloc(nlen+8-nlen%8+1);
		memset(*ppOutput,'\0',nlen+8-nlen%8+1);
		encrypt1=(char *)malloc(nlen+8-nlen%8+1);
		memset(encrypt1,'\0',nlen+8-nlen%8+1);
		memcpy(encrypt1,encrypt,nlen);
		memset(encrypt1+nlen,'\0',8-nlen%8);
		nlen=nlen+8-nlen%8;
	}
	else
	{
		*ppOutput=(byte *)malloc(nlen+1);
		memset(*ppOutput,'\0',nlen+1);
		encrypt1=(char *)malloc(nlen+1);
		memset(encrypt1,'\0',nlen+1);
		memcpy(encrypt1,encrypt,nlen);
	}

	TripleDesDecryptCBC((byte *)encrypt1, nlen, (byte *)key, *ppOutput);
	free(encrypt1);
	encrypt1=NULL;
#endif
#endif

#ifdef USE_RC4
	RC4_KEY rc4_key;
	*ppOutput = (byte *)malloc(strlen(hexContent)/2+1);
	memset(*ppOutput,'\0',strlen(hexContent)/2+1);
	*pLength=strlen(hexContent)/2;
	RC4_set_key(&rc4_key,32,(const unsigned char *)key);
	RC4(&rc4_key,strlen(hexContent)/2,(const unsigned char *)encrypt,*ppOutput);
#endif

	if(key)
	{
		free(key);
		key = NULL;
	}
	if(encrypt)
	{
		free(encrypt);
		encrypt = NULL;
	}

	if(strlen((char *)*ppOutput) != 0)
	{
		*pLength = strlen((char *)*ppOutput);
		return SUCCESS;
	}
	DEBUG("*pLength %d <> %d\n",(int)*pLength,(int)strlen((char *)*ppOutput));
	return FAILED;
	return 0;
}
