#include <stdio.h>
#include <stdlib.h>
#include "adapter.h"
#include <mcheck.h>
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
	setenv("MALLOC_TRACE", "output", 1);
	mtrace();
	printf("argv[1] %s\n",argv[1]);
	printf("argv[2] %s\n",argv[2]);
	char *hex_key=(char *)malloc(2*strlen(argv[1])+1);
	memset(hex_key,'\0',strlen(argv[1])+1);
	CharToHex(argv[1],hex_key);
	if(0 == decrypt_mg(hex_key, argv[2], &ppOutput, &pLength))
	{
		printf("decrypt_mg ok\n");
		printf("decrypt len %d:\n",pLength);
		for(i=0;i<pLength;i++)
			printf("%c",ppOutput[i]);
		printf("\n");
		free(ppOutput);
		ppOutput = NULL;
	}
	else
		printf("decrypt_mg failed\n");
	free(hex_key);
	hex_key = NULL;
	return 0;
}

