#include <stdio.h>
#include <string.h>

void addfile(char *filename);
void newarchive(char *filename);
void closearchive();

FILE *archive;
char fname[11];

void main()
{
	clrscr();
	newarchive("c:/archive.dat");
	addfile("c:/c/eep.bmp");
	addfile("c:/c/eep2.bmp");
	addfile("c:/c/eep3.bmp");
	closearchive();
}

void newarchive(char *filename)
{
	archive = fopen(filename,"wb");
	fwrite("SAM\0",3,1,archive);
}

void addfile(char *filename)
{
	FILE *fh;
	char buf[1];
	char fc1[1], fc2[1];
	int EF=0,y;
	fc1[0] = 0x250;
	fc2[0] = 0x251;
	fh=fopen(filename,"rb");
	if(fh == NULL)
	{
		printf("File does not exist\n");
		exit(1);
	}
	fwrite(fc1,1,1,archive);
	while(EF == 0)
	{
		EF = feof(fh);
		if(EF != 0)
			goto EF1;
		fread(buf,1,1,fh);
		fwrite(buf,1,1,archive);
	}
	EF1:
	fwrite(fc2,1,1,archive);
}

void closearchive()
{
	char fc[1];
	fc[0] = 0x252;
	fwrite(fc,1,1,archive);
	fcloseall();
}