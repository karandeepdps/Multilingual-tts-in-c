#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> // for perror function
#include <arpa/inet.h>



int playSound( char *filename ) 
{ char command[256]; int status; 
 /* create command to execute */ 
 sprintf( command, "afplay %s -r 10", filename );
   /* play sound */ status = system( command ); 
    return status; 
}

int main()
{
	char aa[500];
	int sock,cli;
	struct sockaddr_in server,client;
	int len;
	int sent;
	char mesg[10000];
	//printf("%s\n", mesg);

	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port   = htons(14);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);

	len = sizeof(struct sockaddr_in);

	if((bind(sock, (struct sockaddr *)&server,len)) == -1)
	{
		perror("bind");
		exit(-1);
	}

	if((listen(sock, 5)) == -1)
	{

		perror("listen");
		exit(-1);
	}

	
		if((cli = accept(sock, (struct sockaddr *)&client, (socklen_t*)&len)) == -1)
		{
			perror("accept");
			exit(-1);
		}

int data_len = 1;

		while(data_len)
		{
		data_len=recv(cli, mesg, 10000, 0);
		
		send(cli,mesg,len,0);
		
		mesg[data_len]='\0';
		printf("Sent Mesg: %s \n",mesg);
		
					
					//

						char word[256];
        				int i = 0, j = 0;

					while (mesg[i] != '\0') {
                if (mesg[i] == ' ') {
                	word[j]='.';
                	word[j+1]='m';
                	word[j+2]='p';
                	word[j+3]='3';
                        word[j+4] = '\0';

                        printf("%s\n", word);
                        playSound(word);
                        j = 0;
                } else {
                        word[j++] = mesg[i];
                }
                i++;
        }
					//
		
		memset(mesg,0,sizeof(mesg));
		
		
		}

		

		close(cli);

	



	return 0;
}