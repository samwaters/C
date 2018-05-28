#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
int Encode();
char output[5000];
void SaveEnc();
void main()
{
	int a;
	printf("\nSam's Encoder / Decoder\n");
	printf("1. Encode Text\n");
	printf("2. Load Encoded Text\n");
	printf("3. Save Encoded Text\n");
	printf("4. Decode Text\n");
	printf("5. Load Decoded Text\n");
	printf("6. Save Decoded Text\n");
	printf("7. Exit\n");
	printf("Make Selection:");
	scanf("%d",&a);
	switch(a)
	{
	case 1:
		Encode();
		break;
	case 2:
		break;
	case 3:
		SaveEnc();
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		exit(0);
	default:
		printf("\nInvalid Selection\n");
		exit(0);
		break;
	}
	main();
}

int Encode()
{
	int seed, pia, a, nums[1000],out1;
	char input;
	pia=0;
	printf("Enter Seed:");
	scanf("%d",&seed);
	srand(seed);
	printf("\nPlease wait...\nInitialising...\n");
	for(a=0;a<1001;a++)
	{
		nums[a] = rand();
	}
	printf("Enter message to see encoded version\nPress Esc when done\n");
	reenter:
	while(!kbhit)
	{
	}
	input = getch();
	if(input == 27)
		return 0;
	out1 = toascii(input + 1 + nums[pia]);
	output[pia] = out1;
	pia++;
	printf("%c",out1);
	goto reenter;
}

void SaveEnc()
{
	FILE * fhandle;
	int i;
	fhandle = fopen("c:/encode1.txt","a+");
	for(i=0;i<5001;i++)
	{
		fprintf(fhandle,"%c",output[i]);
	}
	printf("Saved File Successfully\n");
	main();
}