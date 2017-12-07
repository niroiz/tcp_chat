
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIM_LENGTH 10 
#define IP_ADDRESS "127.0.0.1" 
#define PORT 1339 

int main(void)
{ 
  int sock;  
  struct sockaddr_in cli_name; 
  size_t len;
  int count;
  int value; 
  int num;
  int bye;
  bye = 1;
char Csay[180];
   char Ssay[180];
	
  printf("Client is alive and establishing socket connection.\n");

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    { perror ("Error opening channel");
      close(sock);
      exit(1);
    }
      

  bzero(&cli_name, sizeof(cli_name)); 
  cli_name.sin_family = AF_INET; 
  cli_name.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
  cli_name.sin_port = htons(PORT); 


  if (connect(sock, (struct sockaddr *)&cli_name, sizeof(cli_name)) < 0)
    { perror ("Error establishing communications");
      close(sock);
      exit(1);
    }



  while (bye == 1)
    {   printf("write: ");
	gets(Ssay);
	write(sock, Ssay, 180);
	if ((Ssay[0] == 'b') && (Ssay[1] == 'y') && (Ssay[2] == 'e')){
	break;}
        //printf("Client has written [%s] to socket.\n", Ssay);
	read(sock, Csay, 180);
	printf("Server has written [%s] to socket.\n", Csay);
	if((Csay[0] == 'b') && (Csay[1] == 'y') && (Csay[2] == 'e')){
	break;}
    }

  printf("Exiting now.\n");

  close(sock); 
  exit(0); 

} 
