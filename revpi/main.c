/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include "kunbus.h"

#define PORTNO 1500

char regs[10];
int PiControlHandle_g = -1;



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
     int sockfd, newsockfd;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     
     int * regpos0 = (int*)(&regs[0]);
     int * regpos1 = (int*)(&regs[1]);
     int * regpos2 = (int*)(&regs[2]);
     memset(regs, 0, 10);
    
     * regpos0 = readVariableValue("I_1");
     * regpos1 = readVariableValue("I_2");
     * regpos2 = readVariableValue("I_3");

     PiControlHandle_g = -1; 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if(sockfd < 0) 
     {   
       error("ERROR opening socket");
     }
     
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORTNO);
     
     if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
     { 
       error("ERROR on binding");
     }
  
     listen(sockfd,5);
     puts("Waiting for incoming connection\n");
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
     {
       error("ERROR on accept");
     }
     bzero(buffer,256);
     while(1)
     {
       n = read(newsockfd,buffer,255);
	 
       if(n < 0) 
       {
	 error("ERROR reading from socket");
	 printf("Here is the message: %s\n",buffer);
       }
       

       n = send(newsockfd, regs, 3, 0);
       
       if (n < 0) 
       { 
	 error("ERROR writing to socket");
       }
     }    
     sleep(5);
     close(newsockfd);
     close(sockfd);
     return 0; 
}
