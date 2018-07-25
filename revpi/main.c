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
void readOutVar();

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
    readOutVar();
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
  int * send3 = (int*)(&sendBuff[3]);
  int * send4 = (int*)(&sendBuff[4]);
  int * send5 = (int*)(&sendBuff[5]);
  int * send6 = (int*)(&sendBuff[6]);
  int * send7 = (int*)(&sendBuff[7]);
  int * send8 = (int*)(&sendBuff[8]);
  int * send9 = (int*)(&sendBuff[9]);
  int * send10 = (int*)(&sendBuff[10]);
  int * send11 = (int*)(&sendBuff[11]);
  int * send12 = (int*)(&sendBuff[12]);
  int * send13 = (int*)(&sendBuff[13]);
  int * send14 = (int*)(&sendBuff[14]);
  int * send15 = (int*)(&sendBuff[15]);
  int * send16 = (int*)(&sendBuff[16]);
  int * send17 = (int*)(&sendBuff[17]);
  int * send18 = (int*)(&sendBuff[18]);
  int * send19 = (int*)(&sendBuff[19]);
  int * send20 = (int*)(&sendBuff[20]);
  int * send21 = (int*)(&sendBuff[21]);
  int * send22 = (int*)(&sendBuff[22]);
  int * send23 = (int*)(&sendBuff[23]);
  int * send24 = (int*)(&sendBuff[24]);
  int * send25 = (int*)(&sendBuff[25]);
  int * send26 = (int*)(&sendBuff[26]);
  int * send27 = (int*)(&sendBuff[27]);

  * send0 = readVariableValue("I_1");
  * send1 = readVariableValue("I_2");
  * send2 = readVariableValue("I_3");
  * send3 = readVariableValue("I_4");
  * send4 = readVariableValue("I_5");
  * send5 = readVariableValue("I_6");
  * send6 = readVariableValue("I_7");
  * send7 = readVariableValue("I_8");
  * send8 = readVariableValue("I_9");
  * send9 = readVariableValue("I_10");
  * send10 = readVariableValue("I_11");
  * send11 = readVariableValue("I_12");
  * send12 = readVariableValue("I_13");
  * send13 = readVariableValue("I_14");
  * send14 = readVariableValue("I_15");
  * send15 = readVariableValue("I_16");
  * send16 = readVariableValue("I_17");
  * send17 = readVariableValue("I_18");
  * send18 = readVariableValue("I_19");
  * send19 = readVariableValue("I_20");
  * send20 = readVariableValue("I_21");
  * send21 = readVariableValue("I_22");
  * send22 = readVariableValue("I_23");
  * send23 = readVariableValue("I_24");
  * send24 = readVariableValue("I_25");
  * send25 = readVariableValue("I_26");
  * send26 = readVariableValue("I_27");
  * send27 = readVariableValue("I_28");


  n = recv(newsockfd, recvBuff, 255,0);     
  
  if(recvBuff[0] == 1)
  {
    if(n < 0) 
    {
      error("ERROR reading from socket");
    }
    n = send(newsockfd, sendBuff, 1, 0);
    if (n < 0) 
    { 
      error("ERROR writing to socket");
    }
  }
}


void readOutVar()
{
  if(recvBuff[0] == 2) 
  {
    sprintf(outputWriteBuff, "O_%d",  recvBuff[1]);
    writeVariableValue(outputWriteBuff, recvBuff[2]);
  }
  memset(sendBuff, 0, 256);
  int * send0 = (int*)(&sendBuff[0]);
  * send0 = 1;


  n = send(newsockfd, sendBuff, 1, 0);

}
