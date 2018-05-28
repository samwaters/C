#include <stdio.h>
#include <time.h>

struct mytime
{
	int hour;
	int minute;
	int second;
};

struct td
{
	struct mytime *time1;
	struct mytime *time2;
};

struct mytime *gt();
struct mytime *gettd(struct td *t);
int isalarm(struct mytime *thetime);
void alarm();

void main()
{
	struct mytime *a, *b, *c, *d;
	struct td *td1;
	int h,m,s;
	int ah, am, as;
	printf("--Alarm Clock--\n");
	a=gt();
	printf("Time Now: %.2d:%.2d:%.2d\n",a->hour,a->minute,a->second);
	printf("Enter Hour:");
	scanf("%d",&ah);
	printf("Enter Minute:");
	scanf("%d",&am);
	printf("Enter Second:");
	scanf("%d",&as);
	b->hour = ah;
	b->minute = am;
	b->second = as;
	rc:
	a=gt();
	h = a->hour;
	m = a->minute;
	s = a->second;
	d->hour = h;
	d->minute = m;
	d->second = s;
	td1->time1 = d;
	td1->time2 = b;
	c = gettd(td1);
	if(isalarm(c) == 1)
	{
		alarm();
	}
	else
	{
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b%.2d:%.2d:%.2d remaining",c->hour,c->minute,c->second);
		goto rc;
	}
}

struct mytime *gt()
{
	time_t t1;
	struct tm *t2;
	struct mytime *thetime;
	t1=time(NULL);
	t2 = localtime(&t1);
	thetime->hour = t2->tm_hour;
	thetime->minute = t2->tm_min;
	thetime->second = t2->tm_sec;
	return thetime;
}

struct mytime *gettd(struct td *t)
{
	int hd, md, sd;
	struct mytime *d1;
	struct mytime *d2;
	struct mytime *td;
	d1 = t->time1;
	d2 = t->time2;
	sd = d2->second - d1->second;
	md = d2->minute - d1->minute;
	hd = d2->hour - d1->hour;
	if(sd < 0)
	{
		sd = 60 + sd;
		md--;
	}
	if(md < 0)
	{
		md = 60 + md;
		hd--;
	}
	td->hour = hd;
	td->minute = md;
	td->second = sd;
	return td;
}

void alarm()
{
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b00:00:00 remaining");
	printf("\nALARM");
	while(inportb(0x60) != 1)
	{
		printf("\a");
	}
}

int isalarm(struct mytime *thetime)
{
	if((thetime->hour == 0) && (thetime->minute == 0) && (thetime->second == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}