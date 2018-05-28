#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <mem.h>
#include <alloc.h>

#define SCREENWIDTH 320

typedef unsigned char byte;
typedef unsigned short word;

typedef struct tagBITMAP
{
	word width;
	word height;
	byte palette[256*3];
	byte *data;
} BITMAP;

void setgmode();
void bskip(FILE *fp, int nobytes);
void loadbitmap(char *fname, BITMAP *bmp);
void drawbitmap(BITMAP *bmp, int x, int y);
void setuppalette(byte *palette);
byte *VGAMEM=(byte *)0xA0000000L;

void main()
{
	char fname[30];
	BITMAP bmp;
	int x,y;
	printf("Enter bitmap to load:");
	scanf("%s",fname);
	printf("Enter X coordinate:");
	scanf("%d",&x);
	printf("Enter Y coordinate:");
	scanf("%d",&y);
	loadbitmap(fname,&bmp);
	setgmode(0x13);
	setuppalette(bmp.palette);
	drawbitmap(&bmp,x,y);
	while(inportb(0x60) != 1)
	{
		/*Wait for ESC*/
	}
	setgmode(0x03);
}

void bskip(FILE *fp, int nobytes)
{
	/*Skip bytes in a file*/
	int i;
	for(i=0;i<nobytes;i++)
	{
		fgetc(fp);
	}
}

void loadbitmap(char *file, BITMAP *bmp)
{
	FILE *fh;
	long index;
	word nocolors;
	int x;
	fh = fopen(file,"rb");
	if(fh==NULL)
	{
		printf("Error opening file\n");
		exit(0);
	}
	/*Check to see if it's a bitmap*/
	/*If it is, the first two bytes will be B and M*/
	if(fgetc(fh) != 'B' || fgetc(fh) != 'M')
	{
		printf("Not a valid bitmap file\n");
		exit(0);
	}
	bskip(fh,16); /*Ignore next 16 bytes*/
	/*Now read the WIDTH, HEIGHT and COLOR COUNT*/
	fread(&bmp->width, sizeof(word),1,fh); /*Width*/
	bskip(fh,2);
	fread(&bmp->height, sizeof(word),1,fh); /*Height*/
	bskip(fh,22);
	fread(&nocolors,sizeof(word),1,fh); /*No. of Colors*/
	bskip(fh,6);
	if(nocolors==0)
	{
		/*If undefined, assume 256 colors*/
		nocolors=256;
	}
	/*Allocate memory for the bitmap*/
	/*We need enough for every pixel = height * width*/
	bmp->data = (byte *) malloc((word)(bmp->width*bmp->height));
	if(bmp->data == NULL)
	{
		fclose(fh);
		printf("Insufficient memory for bitmap\nRequired: %d x %d\n",bmp->width, bmp->height);
		exit(0);
	}
	/*Now read palette information*/
	for(index=0;index<nocolors;index++)
	{
		/*>> is a RIGHT SHIFT OPERATOR*/
		/*In this case we are right shifting by two*/
		/*Because the palette requires us to*/
		bmp->palette[(int)(index*3+2)] = fgetc(fh) >> 2;
		bmp->palette[(int)(index*3+1)] = fgetc(fh) >> 2;
		bmp->palette[(int)(index*3+0)] = fgetc(fh) >> 2;
		x = fgetc(fh);
	}
	/*Finally, read the bitmap data*/
	/*Data starts in the bottom left corner*/
	/*Therefore we have to read 'backwards'*/
	for(index=((bmp->height-1)*bmp->width);index>=0;index-=bmp->width)
	{
		for(x=0;x<bmp->width;x++)
		{
			bmp->data[(word)(index+x)] = (byte)fgetc(fh);
		}
	}
	fclose(fh);
	/*And the concludes the bitmap loading routine!*/
}

void drawbitmap(BITMAP *bmp, int x, int y)
{
	/*This is really simple as all the complicated stuff*/
	/*Was done in the loadbitmap function*/
	/*All we have to do is copy the bitmap data*/
	/*To VGA memory and it appears like magic!*/
	/*<< is a LEFT SHIFT operator*/
	int i;
	word soffset = (y<<8)+(y<<6)+x; /*Screen offset*/
	word boffset = 0; /*Bitmap offset*/
	for(i=0;i<bmp->height;i++)
	{
		memcpy(&VGAMEM[soffset],&bmp->data[boffset],bmp->width);
		boffset+=bmp->width;
		soffset+=SCREENWIDTH;
	}
}

void setuppalette(byte *palette)
{
	/*As the bitmap can define its own palette*/
	/*It is stored in the bitmap file itself*/
	/*Therefore we must read it and tell the VGA system*/
	/*Which color is which*/
	int i;
	/*Output 0 to this port to inform VGA that we are defining*/
	/*a new palette*/
	outportb(0x03c8,0);
	for(i=0;i<256*3;i++)
	{
		/*Set each color to the one the bitmap specified*/
		outportb(0x03c9,palette[i]);
	}
}

void setgmode(byte mode)
{
	union REGS regs;
	regs.h.ah = 0x00;
	regs.h.al = mode;
	int86(0x10,&regs,&regs);
	/*initgraph can't work here*/
	/*DOS only supports the graphics modes*/
	/*320x200x256colors OR 640x480x16colors*/
	/*We need 256colors so interrupts it is*/
}