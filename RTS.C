#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
void cka(int ya,int ca,int ro);
void fq(int num);
void pran();
int num=0;
int q=0;
struct
{
	int rootof;
	int rig;
}rw[20];
int rts[20];
void main()
{
	int a;
	time_t t;
	rts[0]=4;
	rts[1]=9;
	rts[2]=16;
	rts[3]=25;
	rts[4]=36;
	rts[5]=49;
	rts[6]=64;
	rts[7]=81;
	rts[8]=100;
	rts[9]=121;
	rts[10]=144;
	rts[11]=169;
	rts[12]=196;
	rts[13]=225;
	rts[14]=256;
	rts[15]=289;
	rts[16]=324;
	rts[17]=361;
	rts[18]=400;
	time(&t);
	srand(t);
    gen:a=rand();
    if(a>18)
	goto gen;
    else
	fq(rts[a]);
}

void fq(int num)
{
	int b,c;
	printf("\nQuestion %d: What is the square root of %d?",q + 1,num);
	scanf("%d",&b);
	c=sqrt(num);
	cka(b,c,num);
}

void cka(int ya,int ca,int ro)
{
	if(ya==ca)
	{
		rw[q].rootof=ro;
		rw[q].rig=1;
	}
	else
	{
		rw[q].rootof=ro;
		rw[q].rig=0;
	}
	q++;
	if(q<20)
		main();
	else
		pran();

}

void pran()
{
	char z;
	int a,y=0;
	int g;
	printf("\n**********************A*N*S*W*E*R*S**********************\n");
	for(a=0;a<20;a++)
	{
		g=rw[a].rig;
		if(g==1)
			printf("Question %d (Root %d): Correct\n",a+1,rw[a].rootof);
		else
			printf("Question %d (Root %d): Incorrect\n",a+1,rw[a].rootof);
		y=y+rw[a].rig;
	}
	if(y < 5)
		printf("\nSCORE: %d / 20\nWhat kind of score do you call that?\n",y);
	if(y >= 5 && y < 10)
		printf("\nSCORE: %d / 20\nYou'd better do some SERIOUS revision!\n",y);
	if(y >= 10 && y < 15)
		printf("\nSCORE: %d / 20\nAn OK score I suppose, but there's still some SERIOUS improvements to be made!\n",y);
	if(y >=15 && y < 20)
		printf("\nSCORE: %d / 20\nGood attempt! Just a little more work!\n",y);
	if(y == 20)
		printf("\nSCORE: %d / 20\nPERFECT! Told you that work was worth it!\n",y);
	printf("Enter to end...");
	scanf("%c",&z);
	scanf("%c",&z);
}