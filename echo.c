#include<stdio.h>
#include<stdlib.h>
   #include <sys/types.h>
     #include <sys/socket.h>
     #include<netinet/in.h>
		#include<errno.h> // for perror function
		#include <arpa/inet.h>
			#include<string.h>
#include<unistd.h>

#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024





int main()
{
	int sock,cli;
	struct sockaddr_in server,client;
	int len;
	int sent,new;
	char mesg[] = "Hello socket baby \n";
	char data[10000];
	//printf("%s\n", mesg);

	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port   = htons(1000);
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

	while(1)
	{
		if((new = accept(sock, (struct sockaddr *)&client, (socklen_t*)&len)) == -1)
		{
			perror("accept");
			exit(-1);
		}

		printf("New client connected from port no %d and ip %s\n",
			ntohs(client.sin_port),inet_ntoa(client.sin_addr));

		int data_len = 1;

		while(data_len)
		{
			 data_len = recv(new, data, MAX_DATA, 0);

			 if(data_len)
			 {
			 	sent = send(new,data,data_len,0);
			 	data[data_len] = '\0';  
			 	printf("Sent Mesg: %s\n",data);
			 }
			

		printf("Send %d bytes to client : %s\n",sent,inet_ntoa(client.sin_addr));

		
		}
		printf("Client Disconnected\n");

		close(new);

	}



	return 0;
}