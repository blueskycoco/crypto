#include <stdio.h>
#include <stdlib.h>
#include "adapter.h"
int main(int argc,char *argv[])
{
	int i = 0;
	byte *ppOutput = NULL;
	int pLength = 0;
	printf("argv[1] %s\n",argv[1]);
	printf("argv[2] %s\n",argv[2]);
	if(0 == encrypt_mg(argv[1], argv[2], &ppOutput, &pLength))
	{
		printf("encrypt_mg ok\n");
		printf("encrypt len %d:\n",pLength);
		for(i=0;i<pLength;i++)
			printf("%02x",ppOutput[i]);
		//free(ppOutput);
		//ppOutput = NULL;
	}
	else
		printf("encrypt_mg failed\n");
	return 0;
}

