#include <stdio.h>
#include <stdlib.h>
#include "adapter.h"
void CharToHex(char *str,char *hex)
{
	int ix=0;
	int iy=0;
	while (str[ix] != '\0')
	{
		hex[iy]=(str[ix]&0xf0) >>4;
		if(hex[iy]>=10 && hex[iy]<=15)
			hex[iy]=hex[iy]+'a'-10;
		else
			hex[iy]=hex[iy]+'0';
		iy++;
		hex[iy]=str[ix]&0x0f;
		if(hex[iy]>=10 && hex[iy]<=15)
			hex[iy]=hex[iy]+'a'-10;
		else
			hex[iy]=hex[iy]+'0';
		iy++;
		ix++;
	}
	hex[iy]='\0';
	printf("Hex %s\n",hex);
	return ;
}
int main(int argc,char *argv[])
{
	int i = 0;
	byte *ppOutput = NULL;
	int pLength = 0;
	printf("argv[1] %s\n",argv[1]);
	printf("argv[2] %s\n",argv[2]);
	char *hex_key=(char *)malloc(2*strlen(argv[1])+1);
	memset(hex_key,'\0',strlen(argv[1])+1);
	CharToHex(argv[1],hex_key);
	char *hex_enc=(char *)malloc(2*strlen(argv[2])+1);
	memset(hex_enc,'\0',strlen(argv[2])+1);
	CharToHex(argv[2],hex_enc);
	if(0 == encrypt_mg(hex_key, hex_enc, &ppOutput, &pLength))
	{
		printf("encrypt_mg ok\n");
		printf("encrypt len %d:\n",pLength);
		for(i=0;i<pLength;i++)
			printf("%02x",ppOutput[i]);
		free(ppOutput);
		ppOutput = NULL;
	}
	else
		printf("encrypt_mg failed\n");
	free(hex_key);
	free(hex_enc);
	hex_key = NULL;
	hex_enc = NULL;
	return 0;
}

