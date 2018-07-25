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
#include "main.h"

#define PORTNO 1500

void initServer();
void initMain();
void sendReadVar();

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main()
{
  initServer();
  initMain();
  memset(regs, 0, 10);
 
  while(program == 1)
  {
    printf("I_2:%d\n", readVariableValue("I_2"));
    sendReadVar();
  }    
  close(newsockfd);
  close(sockfd);
  return 0; 
}

void initServer()
{
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
}

void initMain()
{
  program = 1;
  PiControlHandle_g = -1; 
}


void sendReadVar()
{
  int * send0 = (int*)(&sendBuff[0]);
  int * send1 = (int*)(&sendBuff[1]);
  int * send2 = (int*)(&sendBuff[2]);

  * send0 = readVariableValue("I_1");
  * send1 = readVariableValue("I_2");
  * send2 = readVariableValue("I_3");

  n = recv(newsockfd, recvBuff, 255,0);     
  
  if(recvBuff[0] == 1)
  {
    if(n < 0) 
    {
      error("ERROR reading from socket");
    }
    n = send(newsockfd, regs, 3, 0);
    if (n < 0) 
    { 
      error("ERROR writing to socket");
    }
  }
  
}
