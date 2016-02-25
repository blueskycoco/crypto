#include "adapter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FAILED	1
#define SUCCESS	0
#define AES_BLOCK_LEN 16
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
	//printf("HexToChar len %d\n",strlen(hex));
	*out = (char *)malloc(strlen(hex)/2 + 1);
	memset(*out,'\0',strlen(hex)/2 + 1);
	for(i = 0;i < strlen(hex);i=i+2)
	{
		(*out)[i/2] = (hex_to_char(hex[i]) * 16 ) + hex_to_char(hex[i+1]);
	}
	//printf("orignal hex %s\n",hex);
	//printf("after to char %s\n",*out);
}
int encrypt_mg(const char* hexKey, const char* hexContent, byte** ppOutput, int* pLength)
{
	if(hexKey == NULL || hexContent == NULL || pLength == NULL || strlen(hexKey) != 64)
	{
		if(hexKey == NULL)
			printf("hexKey is NULL\n");

		if(hexContent == NULL)
			printf("hexContent is NULL\n");

		if(pLength == NULL)
			printf("pLength is NULL\n");

		if(strlen(hexKey) != 64)
			printf("hexKey len is not 64 , %d\n",strlen(hexKey));
		
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
			printf("HexToChar key failed\n");

		if(encrypt)
		{
			free(encrypt);
			encrypt = NULL;
		}
		else
			printf("HexToChar encrypt failed\n");
		return FAILED;
	}
#if defined(USE_AES_CBC) || defined(USE_AES_ECB)
	unsigned long length = strlen(hexContent) / 2;
	unsigned long nlen = ((length % AES_BLOCK_LEN) == 0) ? length : (length + AES_BLOCK_LEN - length % AES_BLOCK_LEN);
	*ppOutput = (byte *)malloc(nlen+1);
	memset(*ppOutput,'\0',nlen+1);
	*pLength = nlen;
#ifdef USE_AES_CBC
	AES128_CBC_encrypt_buffer(*ppOutput, (unsigned char*)encrypt, nlen, (const unsigned char *)key, (const unsigned char *)(key + AES_BLOCK_LEN));
#else
	AES128_ECB_encrypt((unsigned char*)encrypt, (const unsigned char *)key, *ppOutput);
#endif
#endif

#if defined(USE_DES) || defined(USE_3DES)
	unsigned long nlen = strlen(hexContent)/2;
	byte *to_enc = (byte *)malloc(nlen+nlen%8);:w

	if(nlen<8)
		*ppOutput = (byte *)malloc(8+1);
	else
		*ppOutput = (byte *)malloc(nlen+1);
	memset(*ppOutput,'\0',nlen+1);
	*pLength = nlen;
#ifdef USE_DES
	DesEncrypt((byte *)encrypt, (byte *)key, *ppOutput);
#else
	TripleDesEncryptCBC((byte *)encrypt, nlen, (byte *)key, *ppOutput);
#endif
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
	printf("*pLength %d <> %d\n",*pLength,strlen((char *)*ppOutput));
	return FAILED;
}

int decrypt_mg(const char* hexKey, const char* hexContent, byte** ppOutput, int* pLength)
{
	if(hexKey == NULL || hexContent == NULL || pLength == NULL || strlen(hexKey) != 64)
	{
		if(hexKey == NULL)
			printf("hexKey is NULL\n");

		if(hexContent == NULL)
			printf("hexContent is NULL\n");

		if(pLength == NULL)
			printf("pLength is NULL\n");

		if(strlen(hexKey) != 64)
			printf("hexKey len is not 64 , %d\n",strlen(hexKey));
		
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
			printf("HexToChar key failed\n");

		if(encrypt)
		{
			free(encrypt);
			encrypt = NULL;
		}
		else
			printf("HexToChar encrypt failed\n");
		return FAILED;
	}
#if defined(USE_AES_CBC) || defined(USE_AES_ECB)
	unsigned long length = strlen(hexContent) / 2;
	unsigned long nlen = ((length % AES_BLOCK_LEN) == 0) ? length : (length + AES_BLOCK_LEN - length % AES_BLOCK_LEN);
	*ppOutput = (byte *)malloc(nlen+1);
	memset(*ppOutput,'\0',nlen+1);
#ifdef USE_AES_CBC
	AES128_CBC_decrypt_buffer(*ppOutput, (unsigned char*)encrypt, nlen, (const unsigned char *)key, (const unsigned char *)(key + AES_BLOCK_LEN));
#else
	AES128_ECB_decrypt((unsigned char *)encrypt, (const unsigned char *)key, *ppOutput);
#endif
#endif

#if defined(USE_DES) || defined(USE_3DES)
	unsigned long nlen = strlen(hexContent)/2;
	*ppOutput = (byte *)malloc(nlen+1);
	memset(*ppOutput,'\0',nlen+1);
	*pLength = nlen;
#ifdef USE_DES
	DesDecrypt((byte *)encrypt, (byte *)key, *ppOutput);
#else
	TripleDesDecryptCBC((byte *)encrypt, nlen, (byte *)key, *ppOutput);
#endif
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
	printf("*pLength %d <> %d\n",*pLength,strlen((char *)*ppOutput));
	return FAILED;
	return 0;
}
