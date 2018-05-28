#include <stdio.h>

int isvalidarchive(char *fname);
void extractfile(char *outfile);

FILE *filename;

void main()
{
	int x;
	x = isvalidarchive("c:/archive.dat");
	if(x == 0)
	{
		printf("Not a valid archive!\n");
		exit(1);
	}
	extractfile("c:/c/eep4.bmp");
}

int isvalidarchive(char *fname)
{
	char x,y,z;
	filename = fopen(fname,"rb");
	if(filename == NULL)
	{
		printf("File Access Error\n");
		exit(1);
	}
	x = fgetc(filename);
	y = fgetc(filename);
	z = fgetc(filename);
	if((x == 'S') && (y == 'A') && (z == 'M'))
		return 1;
	else
		return 0;
}

void extractfile(char *outpath)
{
	char x=0,buf[1];
	char fc1=0x250,fc2=0x251,fc3=0x252;
	FILE *fh;
	fh = fopen(outpath,"wb");
	buf[0] = 'A';
	/*Find the start of the next file denoted by 0x250*/
	while(x != fc1)
	{
		x = fgetc(filename);
		if(x == fc3)
		{
			printf("No more files in archive!\n");
			exit(0);
		}
	}
	while(buf[0] != fc2)
	{
		fread(buf,1,1,filename);
		fwrite(buf,1,1,fh);
	}
	fclose(fh);
}
