#include <sys/types.h>
#include <unistd.h>          
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>     
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>

#define SIM_LENGTH 10 
#define PORT 1339

void clean_up(int cond, int *sock)
{ printf("Exiting now.\n");
  close(*sock); 
  exit(cond);
} 

int main(void)
{ 
  int sock; 
  int connect_sock; 
  struct sockaddr_in serv_name; 
  size_t len; 
  int count;
  int num;
  int bye;
  bye = 1;
  char Csay[180];
   char Ssay[180];
  sock = socket(AF_INET, SOCK_STREAM, 0);  
  if (sock < 0)
    { perror ("Error opening channel");
      clean_up(1, &sock);
    }
  
  bzero(&serv_name, sizeof(serv_name)); 
  serv_name.sin_family = AF_INET;                                   
  serv_name.sin_port = htons(PORT); 
  serv_name.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(sock, (struct sockaddr *)&serv_name, sizeof(serv_name)) < 0)
    { perror ("Error naming channel");
      clean_up(1, &sock);
    }
      
  printf("Server is alive and waiting for socket connection from client.\n");
  listen(sock, 1); 

  len = sizeof(serv_name);
  connect_sock = accept(sock, (struct sockaddr *)&serv_name, &len);



  while (bye == 1)	
    { 
      read(connect_sock, Csay, 180);
	printf("Client has written [%s] to socket.\n", Csay);
	if((Csay[0] == 'b') && (Csay[1] == 'y') && (Csay[2] == 'e')){
	break;}
	printf("write: ");
       gets(Ssay);
	write(connect_sock, Ssay, 180);
	if ((Ssay[0] == 'b') && (Ssay[1] == 'y') && (Ssay[2] == 'e')){
	break;}
      //printf("Server has written [%s] to socket.\n", Ssay);	
    }

  close(connect_sock); 
  clean_up(0, &sock); 

}
