#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> // for perror function
#include <arpa/inet.h>




#define BUFFER 1024

int main()
{
	char aa[500];
	int sock,cli;
	struct sockaddr_in server,client;
	int len;
	int sent;
	char mesg[10000];
	char input[BUFFER];
	char output[BUFFER];
	//printf("%s\n", mesg);

	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port   = htons(110);
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


		while(1)
	{
		fgets(input,BUFFER,stdin);
		send(cli,input,strlen(input),0);

		len = recv(sock,output,BUFFER,0);
		input[len] = '\0';
		printf("%s\n",input);

	}


		

		close(cli);

	



	return 0;
}