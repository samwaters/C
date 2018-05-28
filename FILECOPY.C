#include <stdio.h>

void main()
{
	FILE *fh, *fh2;
	char fname[30], fname2[30];
	char buf[1];
	int a;
	printf("File 1:");
	scanf("%s",fname);
	printf("File 2:");
	scanf("%s",fname2);
	fh=fopen(fname,"rb");
	fh2=fopen(fname2,"wb");
	a=0;
	while(a == 0)
	{
		a=feof(fh);
		fread(buf,1,1,fh);
		fwrite(buf,1,1,fh2);
	}
	printf("\n\aDone!\n");
	fcloseall();
}