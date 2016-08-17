#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> // for perror function
#include <arpa/inet.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
//reference http://www.binarytides.com/multiple-socket-connections-fdset-select-linux/

//adress ==server


#define BUFFER 1024

int main()
{
	char aa[500];
	int opt=1;
	  char buffer[1025];
	int sock,cli;
	struct sockaddr_in server,client;
	int len;
	int sent;
	char mesg[10000];
	char input[BUFFER];
	char output[BUFFER];
	//printf("%s\n", mesg);
	int master_socket,client_socket[30] , max_clients = 30,sd,activity,max_sd,i,new_socket,valread,addrlen;
	 //set of socket descriptors
    fd_set readfds;

    //a message
    char *message = "ECHO Daemon v1.0 \r\n";

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < max_clients; i++) 
    {
        client_socket[i] = 0;
    }
      


	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

  if( setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
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
	addrlen=sizeof(server);

	while(1)
	{


		 //clear the socket set
        FD_ZERO(&readfds);
  
        //add master socket to set
        FD_SET(sock, &readfds);
        max_sd = sock;

         //add child sockets to set
        for ( i = 0 ; i < max_clients ; i++) 
        {
            //socket descriptor
            sd = client_socket[i];
             
            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);
             
            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

         activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);


          if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }


         if (FD_ISSET(sock, &readfds)) 
        {
            if ((new_socket = accept(sock, (struct sockaddr *)&server, (socklen_t*)&addrlen)) == -1)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }


          
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(server.sin_addr) , ntohs(server.sin_port));
        
            //send new connection greeting message
            if( send(new_socket, message, strlen(message), 0) != strlen(message) ) 
            {
                perror("send");
            }
              
            puts("Welcome message sent successfully");
              
            //add new socket to array of sockets
            for (i = 0; i < max_clients; i++) 
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);
                     
                    break;
                }
            }
        }
        
            printf("What you want to do\n");
            printf("1) Send message\n");
            printf("2) List Speakers\n");
            int in;
            scanf("%d",&in);
            if(in==1)
            {
//for (i = -1; i < max_clients; i++) 
//{
	printf("Enter Speaker no\n");
	int num;
	scanf("%d",&num);
             sd = client_socket[num];
             
             // fgets cause loop to skip input string on first iteration
                
              if(client_socket[num]>0){
              	printf("Selected client is %d\n",i);

					printf("enter string to send\n");
                   
                    fgets(input,BUFFER,stdin);
                   
                    send(sd , input , strlen(input) , 0 );
                }
              
     	 
 //}
 			}
 			else if(in==2)
 			{
 				for (i = 0; i < max_clients; i++) 
 				{
 					if(client_socket[i]>0)
 					{
 					getpeername(sd , (struct sockaddr*)&server , (socklen_t*)&addrlen);
                    printf("Speaket at , ip %s , port %d \n" , inet_ntoa(server.sin_addr) , ntohs(server.sin_port));
                      
              		}
 				}

 			}

		

	}


	

		

		close(cli);

	



	return 0;
}