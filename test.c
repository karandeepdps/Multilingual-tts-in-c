#include<stdio.h>
#include <string.h>
int main()
{

	int choice;

	printf("Enter 1 for hindi 2 for English\n");
	scanf("%d",&choice);

	if(choice==1)
{
char trainno[10];

  printf("Enter 5 digit Train No\n");

scanf("%s",trainno);



	
	

char mesgtosend[300];

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
	mesgtosend[j+i+17]=cityto[j];
	//printf("hi\n");
}

mesgtosend[j+i+17]=' ';
mesgtosend[j+i+18]='p';
mesgtosend[j+i+19]='n';
mesgtosend[j+i+20]=' ';

printf("Enter platform no\n");

char platform[30];
scanf("%s",platform);

mesgtosend[j+i+21]=platform[0];
mesgtosend[j+i+22]=' ';
mesgtosend[j+i+23]='p';
mesgtosend[j+i+24]='a';
mesgtosend[j+i+25]='\n';



printf("%s\n",mesgtosend);
}
else
{


char mesgtosend[300]="please pay attention that train no ";

char trainno[10];

  printf("Enter 5 digit Train No\n");

scanf("%s",trainno);

mesgtosend[35]=trainno[0];mesgtosend[36]=' ';
mesgtosend[37]=trainno[1];mesgtosend[38]=' ';
mesgtosend[39]=trainno[2];mesgtosend[40]=' ';
mesgtosend[41]=trainno[3];mesgtosend[42]=' ';
mesgtosend[43]=trainno[4];mesgtosend[44]=' ';


strcat(mesgtosend," coming from ");



printf("Enter from city\n");

char city[30];
scanf("%s",city);

int count=0;
while(city[count]!='\0')
	count++;




int i;
for(i = 0;i<count;i++)
{
	mesgtosend[i+58]=city[i];
	//printf("hi\n");
}

strcat(mesgtosend," going to city ");


printf("Enter to city\n");

char cityto[30];
scanf("%s",cityto);

count=0;
while(cityto[count]!='\0')
	count++;

int j;
for(j = 0;j<count;j++)
{
	mesgtosend[j+i+73]=cityto[j];
	//printf("hi\n");
}



char src[50], dest[50];

   strcpy(src,  " is arriving on platform no");
  

   strcat(mesgtosend, src);

   printf("Enter platform no\n");

char platform[30];
scanf("%s",platform);

strcat(mesgtosend, platform);


printf("%s\n",mesgtosend);




}

	return 0;
}


//1a=yatrigan kirpaya dyan de gadi number [1 2 3] [city] se [city] platform no [1] pe arri hae; 