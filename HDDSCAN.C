#include <stdio.h>
#include <dos.h>

void readfromdisk(int drive, int head, int sect, int cyl, int count);
int isdriveready(int drive);
void resetdrive(int drive);
void checkdrive(int drive);

char fdata[512];
int DRIVE = 0;

void main()
{
	int i,dr;
	printf("Enter Drive:");
	scanf("%d",&dr);
	DRIVE = dr;
	clrscr();
	checkdrive(DRIVE);
	readfromdisk(DRIVE,0,0,1,512);
	for(i=0;i<512;i++)
	{
		printf("%c",fdata[i]);
	}
}

void readfromdisk(int drive, int head, int sect, int cyl, int count)
{
	union REGS regs;
	struct SREGS sregs;
	int x,y,rcount=0;
	char p[512];
	tryagain:
	regs.h.ah=0x02;
	regs.h.dl=drive;
	regs.h.dh=head;
	regs.h.cl=sect;
	regs.h.ch=cyl;
	regs.h.al=count;
	checkdrive(drive);
	int86x(0x13,&regs,&regs,&sregs);
	sregs.es=FP_SEG(p);
	regs.x.bx=FP_OFF(p);
	x=regs.h.ah;
	if(x==0)
	{
		for(y=0;y<512;y++)
		{
			fdata[y] = p[y];
		}
	}
	else
	{
		if(rcount < 9)
		{
			printf("Read Error: %d\nAttempting Reset\n",x);
			resetdrive(drive);
			rcount++;
			goto tryagain;
		}
		else
		{
			printf("Read Error: %d\nAll Attempted Resets Failed\n",x);
			exit(-1);
		}
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