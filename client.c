#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
     #include <sys/socket.h>
     #include<netinet/in.h>
		#include<errno.h> // for perror function
		#include <arpa/inet.h>
			#include<string.h>


#define ERROR -1
#define BUFFER 1024

int main()
{
	struct sockaddr_in remote_server;
	int sock;
	char input[BUFFER];
	char output[BUFFER];
	int len;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("socket");
		exit(-1);
	}

	remote_server.sin_family = AF_INET;
	remote_server.sin_port = htons(1000);
	remote_server.sin_addr.s_addr = INADDR_ANY;
	bzero(&remote_server.sin_zero,8);

	if((connect(sock, (struct sockaddr *)&remote_server, sizeof(struct sockaddr_in))) == ERROR)
	{
		perror("connect");
		exit(-1);

	}

	while(1)
	{
		fgets(input,BUFFER,stdin);
		send(sock,input,strlen(input),0);

		len = recv(sock,output,BUFFER,0);
		output[len] = '\0';
		printf("%s\n",output);

	}
	close(sock);

	return 0;
}