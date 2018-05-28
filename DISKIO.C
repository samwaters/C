#include <stdio.h>
#include <dos.h>

int writetodisk(int drive, int head, int sect, int cyl, int count, char data[512]);
void readfromdisk(int drive, int head, int sect, int cyl, int count);
void rfile();
void readline();
void wte();
void rd();
int isdriveready(int drive);
void resetdrive(int drive);
void checkdrive(int drive);

char fdata[512];

FILE *fh;

void main()
{
	int mde;
	clrscr();
	checkdrive(0);
	fcloseall();
	resetdrive(0);
	printf("--Menu--\n");
	printf("1. Write to Disk\n2. Read from Disk\n3. Exit\nMake a selection:");
	scanf("%d",&mde);
	switch(mde)
	{
	case 1:
		checkdrive(0);
		wte();
		break;
	case 2:
		checkdrive(0);
		rd();
		break;
	case 3:
		exit(0);
		break;
	default:
		printf("\nInvalid Selection\n\n\n\a");
		main();
	}
}

void wte()
{
	char fname[30];
	printf("File Name and Path (use / slash):");
	scanf("%s",fname);
	fh = fopen(fname,"r+");
	if(fh == NULL)
	{
		printf("Cannot open file\n\n\n");
		main();
	}
	rfile();
}

void rd()
{
	int s=1;
	int cyl=1;
	char fname[30];
	printf("File Name and Path [to Save]:");
	scanf("%s",fname);
	fh=fopen(fname,"a+");
	if(fh==NULL)
	{
		printf("Cannot open file\n\n\a");
		exit(-1);
	}
	for(cyl=0;cyl<80;cyl++)
	{
		for(s=1;s<37;s++)
		{
			readfromdisk(0,0,s,cyl,1);
		}
	}
}

void rfile()
{
	int s=1;
	int cyl=0;
	int x=0;
	while(feof(fh) == 0)
	{
		readline();
		printf("%s\n\a",fdata);
		x=writetodisk(0,0,s,cyl,1,fdata);
		if(x != 0)
		{
			printf("\nWrite Error: %d\n\n",x);
			exit(-1);
		}
		s++;
		if(s > 36)
		{
			s=1;
			cyl++;
		}
	}
	writetodisk(0,0,s,cyl,1,"\0");
	printf("\n\n");
	main();
}

int writetodisk(int drive, int head, int sect, int cyl, int count, char data[512])
{
	union REGS regs;
	struct SREGS sregs;
	regs.h.ah=0x03;
	regs.h.dl=drive;
	regs.h.dh=head;
	regs.h.cl=sect;
	regs.h.ch=cyl;
	regs.h.al=count;
	sregs.es = FP_SEG(data);
	regs.x.bx = FP_OFF(data);
	int86x(0x13,&regs,&regs,&sregs);
	return regs.h.ah;
}

void readfromdisk(int drive, int head, int sect, int cyl, int count)
{
	union REGS regs;
	struct SREGS sregs;
	int x,y;
	char p[512];
	char e1=0x7F;
	char e2=0xFF;
	regs.h.ah=0x02;
	regs.h.dl=drive;
	regs.h.dh=head;
	regs.h.cl=sect;
	regs.h.ch=cyl;
	regs.h.al=count;
	checkdrive(0);
	int86x(0x13,&regs,&regs,&sregs);
	sregs.es=FP_SEG(p);
	regs.x.bx=FP_OFF(p);
	x=regs.h.ah;
	if(x==0)
	{
		for(y=0;y<512;y++)
		{
			if( (p[y] != '\0') && (p[y] != e1) && (p[y] != e2) )
			{
				printf("%c",p[y]);
				fprintf(fh,"%c",p[y]);
			}
			if( p[y] == '\0' )
			{
				printf("\n\n");
				fcloseall();
				main();
			}
		}
	}
	else
	{
		printf("Read Error: %d\n\n",x);
		exit(-1);
	}

}

void readline()
{
	int x;
	char a;
	for(x=0;x<512;x++)
	{
		if(feof(fh) == 0)
		{
			a=fgetc(fh);
			fdata[x] = a;
		}
		else
			fdata[x]='\0';
	}
}

int isdriveready(int drive)
{
	union REGS regs;
	regs.h.ah=0x01;
	regs.h.dl=drive;
	int86(0x13,&regs,&regs);
	return regs.h.ah;
}

void resetdrive(int drive)
{
	union REGS regs;
	int i;
	for(i=0;i<3;i++)
	{
		regs.h.ah=0x00;
		regs.h.dl=drive;
		int86(0x13,&regs,&regs);
	}
}

void checkdrive(int drive)
{
	int res;
	int count=0;
	dr:
	res=isdriveready(drive);
	if(res != 0)
	{
		count++;
		if(count > 100)
		{
			count=0;
			resetdrive(drive);
		}
		goto dr;
	}
}
