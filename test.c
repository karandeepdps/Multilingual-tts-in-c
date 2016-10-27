#include<stdio.h>
int main()
{

char trainno[10];

  printf("Enter 5 digit Train No\n");

scanf("%s",trainno);



	
	

char mesgtosend[100];

mesgtosend[0]='1';
mesgtosend[1]='a';
mesgtosend[2]=' ';
mesgtosend[3]=trainno[0];
mesgtosend[4]=' ';
mesgtosend[5]=trainno[1];
mesgtosend[6]=' ';
mesgtosend[7]=trainno[2];
mesgtosend[8]=' ';
mesgtosend[9]=trainno[3];
mesgtosend[10]=' ';
mesgtosend[11]=trainno[4];
mesgtosend[12]=' ';


printf("%s\n",mesgtosend);

printf("Enter from city\n");

char city[30];
scanf("%s",city);

int count=0;
while(city[count]!='\0')
	count++;




int i;
for(i = 0;i<count;i++)
{
	mesgtosend[i+13]=city[i];
	//printf("hi\n");
}


mesgtosend[i+13]=' ';
mesgtosend[i+14]='s';
mesgtosend[i+15]='e';
mesgtosend[i+16]=' ';

printf("Enter to city\n");

char cityto[30];
scanf("%s",cityto);

count=0;
while(cityto[count]!='\0')
	count++;

int j;
for(j = 0;j<count;j++)
{
	mesgtosend[j+i]=city[j];
	//printf("hi\n");
}

mesgtosend[j+i]=' ';
mesgtosend[j+i]='p';
mesgtosend[j+i]='n';
mesgtosend[j+i]=' ';

printf("Enter platform no\n");

char platform[30];
scanf("%s",cityto);


printf("%s\n",mesgtosend);

	return 0;
}


//1a=yatrigan kirpaya dyan de gadi number [1 2 3] [city] se [city] platform no [1] pe arri hae; 