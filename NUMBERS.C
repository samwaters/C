#include <stdio.h>
#include <math.h>
void magic();
void prime();
void factor();
int isfactor(long double factor, long double num);
int ismagic(long double number);
int isprime(long double number);

void main()
{
	int a;
	char tmp;
	strt:
	printf("1.Prime Numbers\n2.Magic numbers\n3.Factors\n4.Exit\nMake a selection:");
	scanf("%d",&a);
	switch(a)
	{
	case 1:
		prime();
		break;
	case 2:
		magic();
		break;
	case 3:
		factor();
		break;
	case 4:
		exit(0);
		break;
	default:
		printf("\nInvalid Selection\n");
		scanf("%c",&tmp);
	}
	printf("\n\n");
	goto strt;
}

void prime()
{
	long double sn, en, i;
	int x;
	printf("\nEnter start number:");
	scanf("%Le",&sn);
	printf("Enter end number:");
	scanf("%Le",&en);
	printf("\nPrime numbers between %.0Lf and %.0Lf:\n",sn,en);
	for(i=sn;i<=en;i++)
	{
		x = isprime(i);
		if(x == 1)
			printf("%.0Lf ",i);
	}
}

void magic()
{
	long double stnum, endnum, lvar;
	int mgic;
	printf("\nEnter start number:");
	scanf("%Le",&stnum);
	printf("Enter end number:");
	scanf("%Le",&endnum);
	printf("\nMagic numbers between %.0Lf and %.0Lf:\n",stnum,endnum);
	for(lvar=stnum;lvar<=endnum;lvar++)
	{
		mgic=ismagic(lvar);
		if(mgic==1)
			printf("%.0Lf ",lvar);
	}
}

void factor()
{
	long double sn, i;
	int x;
	printf("\nEnter number:");
	scanf("%Le",&sn);
	printf("\n%.0Lf has these factors:\n",sn);
	for(i=2;i<sn;i++)
	{
		x=isfactor(i,sn);
		if(x == 1)
			printf("%.0Lf ",i);
	}
}

int isfactor(long double factor, long double num)
{
	int fact;
	long double ans,ansc,ansf;
	ans=num / factor;
	ansc = ceil(ans);  /*Rounded UP*/
	ansf = floor(ans); /*Rounded DOWN*/
	if(ans==ansc)	   /*Does division = Rounded UP*/
	{
		if(ans==ansf) /*Does division = Rounded DOWN*/
		{
			return 1; /*This is a factor*/
		}
		else
		{
			return 0;
		}

	}
	else
	{
		return 0;
	}
}

int ismagic(long double number)
{
	int isfac;
	long double total,lvar;
	total=0;
	for(lvar=1;lvar<number;lvar++)
	{
		isfac=isfactor(lvar,number);
		if(isfac==1)
			total=total+lvar;
	}
	if(total==number)
		return 1;
	else
		return 0;
}

int isprime(long double number)
{
	long double x,y,z;
	long double ansc, ansf;
	int fc;
	fc = 0;
	x = sqrt(number);
	for(y=2;y<=x;y++)
	{
		z = number / y;
		ansc = ceil(z);
		ansf = floor(z);
		if(z == ansc)
		{
			if(z == ansf)
			{
				fc++;
			}
		}
	}
	if(fc == 0)
		return 1;
	else
		return 0;
}