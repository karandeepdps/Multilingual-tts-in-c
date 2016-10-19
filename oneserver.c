//
//                          MACBOOK AIR OSX 10.10.5
//                          KARANDEEPDPS  Target: x86_64-apple-darwin14.5.0 Thread model: posix
//                          RAS Apple LLVM version 6.1.0 (clang-602.0.53) (based on LLVM 3.6.0svn)
//                          Made Under Guideance of Mr.Vishvas Rathi Sir(Upes)



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
//https://www.gnu.org/software/libc/manual/html_node/Waiting-for-I_002fO.html


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
	int client_socket ,i,valread,addrlen;
	 //set of socket descriptors
    fd_set readfds;

    //a message
    char *message = "Karandeepdps@gmail.com \r\n";

  
      


	if( (sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}



/*
Sometimes, you might notice, you try to rerun a server and bind() fails, claiming 
“Address already in use.” What does that mean? Well, a little bit of a socket that 
was connected is still hanging around in the kernel, and it's hogging the port. You 
can either wait for it to clear (a minute or so), or add code to your program allowing
 it to reuse the port, like this:
*/

 
int yes=1;
  if( setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof yes) == -1)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }


        //AF_INET (IPv4) or AF_INET6 (IPv6)
      //struct sockaddr {
     // unsigned short    sa_family;    // address family, AF_xxx
     //  char              sa_data[14];  // 14 bytes of protocol address
    //};

/*
sa_family can be a variety of things, but it'll be AF_INET (IPv4) or AF_INET6 (IPv6) for everything we do in this document.
 sa_data contains a destination address and port number for the socket. This is rather unwieldy since you don't want to 
 tediously pack the address in the sa_data by hand.
To deal with struct sockaddr, programmers created a parallel structure: 
struct sockaddr_in (“in” for “Internet”) to be used with IPv4.
And this is the important bit: a pointer to a struct sockaddr_in can be cast to a pointer to a struct sockaddr and vice-versa. 
So even though connect() wants a struct sockaddr*, you can still use a struct sockaddr_in and cast it at the last minute!
struct sockaddr_in {
    short int          sin_family;  // Address family, AF_INET
    unsigned short int sin_port;    // Port number
    struct in_addr     sin_addr;    // Internet address
    unsigned char      sin_zero[8]; // Same size as struct sockaddr
};
*/

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

  if (( client_socket = accept(sock, (struct sockaddr *)&server, (socklen_t*)&addrlen)) == -1)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }


	while(1)
	{

        
            printf("What you want to do\n");
            printf("1) Send Message\n");
        
            printf("2) Change Language\n");
            int in;
            scanf("%d",&in);
            if(in==1)
            {

	printf("Message\n");


					printf("enter string to send\n");
                   
                    fgets(input,BUFFER,stdin);
                 
                   
                    send( client_socket , input , strlen(input) , 0 );
                
              system("clear");
     	 
 
 			}
 			


 			else if(in==2)
 			{
 			//	printf("Enter Speaker no\n");
			//	int num;
				//scanf("%d",&num);
           //  sd = client_socket;

             printf("Enter 0 for hindi 1 for english\n");
 				int in;
 				scanf("%d",&in);
 				memset(input,0,BUFFER);
 				if(in==0){
 					input[0]='L';input[1]='E';input[2]='N';input[3]='H';
 				}

 					else{
 						input[0]='L';input[1]='E';input[2]='N';input[3]='E';
 					}
             
                
            
              //	printf("Changing language of client no %d\n",num);
                send( client_socket , input , strlen(input) , 0 );
                
 				
                 system("clear");

 			}

		

	}


	

		

		close(cli);

	



	return 0;
}