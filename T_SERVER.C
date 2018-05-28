#include <stdio.h>

#define PORT 0x3F8
int ID;

void main()
{
	FILE *fhandle;
	int tmp;
	char fname[30];
	outportb(PORT,252);
	printf("Enter file to open:");
	scanf("%s",fname);
	fhandle = fopen(fname,"a+");
	while(tmp > 5)
	{
		tmp = fgetc(fhandle);
		printf("%c",tmp);
		outportb(PORT,tmp);
		outportb(PORT,252);
	}
	outportb(PORT,27);
}