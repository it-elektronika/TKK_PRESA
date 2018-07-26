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
void readLine(int fd, char data[], size_t maxlen);
void receiveRequest();
void sendResponse(int reqId);
void error(const char *msg)
{
  perror(msg);
  exit(1);
}

int main()
{
  initServer();
  initMain();
 
  while(program == 1)
  {
    receiveRequest();
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
  printf("Connection Accepted\n");

}

void initMain()
{
  program = 1;
  PiControlHandle_g = -1; 
}

void readLine(int fd, char data[], size_t maxlen)
{
   size_t len = 0;
   while (len < maxlen)
   {
      char c;
      int ret = recv(fd, &c, 1, 0);
      if (ret < 0)
      {
          data[len] = 0;
          //return len; // EOF reached
      }
      if (c == '\n')
      {
          data[len] = 0;
          //return len; // EOF reached
      }
      data[len++] = c;
   }
}

void receiveRequest()
{
  readLine(newsockfd, recvReadBuff, 3);
  printf("REQUEST RECEIVED\n");
  if(recvReadBuff[0] == 1)
  {
    sendResponse(1);
  } 
  else
  {
    sendResponse(2);
  }
}


void sendResponse(int reqId)
{
  if(reqId == 1)
  {
    int * sendWrite0 = (int*)(&sendWriteBuff[0]);
    int * sendWrite1 = (int*)(&sendWriteBuff[1]);
    int * sendWrite2 = (int*)(&sendWriteBuff[2]);
    int * sendWrite3 = (int*)(&sendWriteBuff[3]);
    int * sendWrite4 = (int*)(&sendWriteBuff[4]);
    int * sendWrite5 = (int*)(&sendWriteBuff[5]);
    int * sendWrite6 = (int*)(&sendWriteBuff[6]);
    int * sendWrite7 = (int*)(&sendWriteBuff[7]);
    int * sendWrite8 = (int*)(&sendWriteBuff[8]);
    int * sendWrite9 = (int*)(&sendWriteBuff[9]);
    int * sendWrite10 = (int*)(&sendWriteBuff[10]);
    int * sendWrite11 = (int*)(&sendWriteBuff[11]);
    int * sendWrite12 = (int*)(&sendWriteBuff[12]);
    int * sendWrite13 = (int*)(&sendWriteBuff[13]);
    int * sendWrite14 = (int*)(&sendWriteBuff[14]);
    int * sendWrite15 = (int*)(&sendWriteBuff[15]);
    int * sendWrite16 = (int*)(&sendWriteBuff[16]);
    int * sendWrite17 = (int*)(&sendWriteBuff[17]);
    int * sendWrite18 = (int*)(&sendWriteBuff[18]);
    int * sendWrite19 = (int*)(&sendWriteBuff[19]);
    int * sendWrite20 = (int*)(&sendWriteBuff[20]);
    int * sendWrite21 = (int*)(&sendWriteBuff[21]);
    int * sendWrite22 = (int*)(&sendWriteBuff[22]);
    int * sendWrite23 = (int*)(&sendWriteBuff[23]);
    int * sendWrite24 = (int*)(&sendWriteBuff[24]);
    int * sendWrite25 = (int*)(&sendWriteBuff[25]);
    int * sendWrite26 = (int*)(&sendWriteBuff[26]);
    int * sendWrite27 = (int*)(&sendWriteBuff[27]);
    
    * sendWrite0 = readVariableValue("I_1");
    * sendWrite1 = readVariableValue("I_2");
    * sendWrite2 = readVariableValue("I_3");
    * sendWrite3 = readVariableValue("I_4");
    * sendWrite4 = readVariableValue("I_5");
    * sendWrite5 = readVariableValue("I_6");
    * sendWrite6 = readVariableValue("I_7");
    * sendWrite7 = readVariableValue("I_8");
    * sendWrite8 = readVariableValue("I_9");
    * sendWrite9 = readVariableValue("I_10");
    * sendWrite10 = readVariableValue("I_11");
    * sendWrite11 = readVariableValue("I_12");
    * sendWrite12 = readVariableValue("I_13");
    * sendWrite13 = readVariableValue("I_14");
    * sendWrite14 = readVariableValue("O_1");
    * sendWrite15 = readVariableValue("O_2");
    * sendWrite16 = readVariableValue("O_3");
    * sendWrite17 = readVariableValue("O_4");
    * sendWrite18 = readVariableValue("O_5");
    * sendWrite19 = readVariableValue("O_6");
    * sendWrite20 = readVariableValue("O_7");
    * sendWrite21 = readVariableValue("O_8");
    * sendWrite22 = readVariableValue("O_9");
    * sendWrite23 = readVariableValue("O_10");
    * sendWrite24 = readVariableValue("O_11");
    * sendWrite25 = readVariableValue("O_12");
    * sendWrite26 = readVariableValue("O_13");
    * sendWrite27 = readVariableValue("O_14");
    
    n = send(newsockfd, sendWriteBuff, 28, 0);
    memset(sendWriteBuff, 0, 28);
    printf("RESPONSE SENT reqId:%d\n", reqId);

  }
  else
  {
    int * sendRead0 = (int*)(&sendReadBuff[0]);
    * sendRead0 = 2;
   
    n = send(newsockfd, sendReadBuff, 1, 0);
    memset(sendReadBuff, 0, 256);
    printf("RESPONSE SENT reqId:%d\n", reqId);

    /*
    sprintf(outputWriteBuff, "O_%d",  recvReadBuff[1]);
    printf("recvbuff1:%d\n", recvReadBuff[1]); 
    printf("recvbuff2:%d\n", recvReadBuff[2]); 
    
    writeVariableValue(outputWriteBuff, recvReadBuff[2]);
    */
  }
  printf("O_1:%d\n",readVariableValue("O_1"));
  printf("O_2:%d\n",readVariableValue("O_2"));
  printf("O_3:%d\n",readVariableValue("O_3"));
  printf("O_4:%d\n",readVariableValue("O_4"));
  printf("O_5:%d\n",readVariableValue("O_5"));
  printf("O_6:%d\n",readVariableValue("O_6"));
  printf("O_7:%d\n",readVariableValue("O_7"));
  printf("O_8:%d\n",readVariableValue("O_8"));
  printf("O_9:%d\n",readVariableValue("O_9"));
  printf("O_10:%d\n",readVariableValue("O_10"));
  printf("O_11:%d\n",readVariableValue("O_11"));
  printf("O_12:%d\n",readVariableValue("O_12"));
  printf("O_13:%d\n",readVariableValue("O_13"));
}


