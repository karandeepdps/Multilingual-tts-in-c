#inclua#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h> // for perror function
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


#define ERROR -1
int flag =0;

int playSound( char *filename ) 
{ char command[256]; int status; 
 /* create command to execute */ 
 sprintf( command, "afplay %s -r 10", filename );
   /* play sound */ status = system( command ); 
    return status; 
}

int playSound2( char *filename ) 
{ char command[256]; int status; 
 /* create command to execute */ 
 sprintf( command, "open 'http://translate.google.com/translate_tts?client=tw-ob&q=%s&tl=En' ", filename );
   /* play sound */ status = system( command ); 
    return status; 
}



int main()
{
	

	FILE *fp;
	char a[10],mesg[1000];
	
	struct sockaddr_in remote_server;
	int sock;
	
	int len;

	if((sock = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
	{
		perror("socket");
		exit(-1);
	}

	remote_server.sin_family = AF_INET;
	remote_server.sin_port = htons(110);
	remote_server.sin_addr.s_addr = INADDR_ANY;
	bzero(&remote_server.sin_zero,8);

	if((connect(sock, (struct sockaddr *)&remote_server, sizeof(struct sockaddr_in))) == ERROR)
	{
		perror("connect");
		exit(-1);

	}

	int data_len = 1;

		while(data_len)
		{
		data_len=recv(sock, mesg, 10000, 0);


		
		if(mesg[0]=='L' && mesg[1]=='E'&& mesg[2]=='N' && mesg[3]=='H')
			flag=0;
		if(mesg[0]=='L' && mesg[1]=='E'&& mesg[2]=='N' && mesg[3]=='E')
			flag=1;

		
		// flag=0 for hindi
		// flag=1 for english

		
		
		
		
		mesg[data_len-1]=' ';
		mesg[data_len]='\0';
		  
		printf("Sent Mesg: %s \n",mesg);

		
					
					//

						char word[256];
							memset(word,0,sizeof(word));
        				int i = 0, j = 0;

        				if (flag==1)
        				{
        					int kd=0,jj=0;
        					while (mesg[kd] != '\0')
        					{
        						word[jj]=mesg[kd];
        						if(mesg[kd]==' ')
        							word[jj]='+';
        						kd++;jj++;
        					}
        					printf("google string%s\n",word);
        					playSound2(word);
        					

        				}

					while (mesg[i] != '\0' && flag==0) {
						
					
                if (((mesg[i] == ' ') && (flag ==0))) {
                	printf("hahah\n");
                	word[j]='.';
                	word[j+1]='m';
                	word[j+2]='p';
                	word[j+3]='3';
                    word[j+4] = '\0';

                        printf("wordd=%s\n", word);
                        playSound(word);
                        j = 0;
                }
                
                else {
                        word[j++] = mesg[i];
                }
                i++;
        }
					//
		
		memset(mesg,0,sizeof(mesg));
		
		
		}


	
	close(sock);

	return 0;
}