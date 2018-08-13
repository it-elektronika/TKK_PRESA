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
void initCommAKDPress();
void diagnostics();
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
  initCommAKDPress();
  initMain();
 
  while(program == 1)
  {
    receiveRequest();
    diagnostics();
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

void initCommAKDPress() 
{
  ip_adrs = "192.168.1.13";
  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  AKD_server.sin_family = AF_INET;
  AKD_server.sin_port = htons(502);
  AKD_server.sin_addr.s_addr = inet_addr(ip_adrs);
  printf("connecting to press drive\n");
  conn_AKD = connect(s, (struct sockaddr *)&AKD_server, sizeof(struct sockaddr_in));
  if (conn_AKD < 0) 
  {   
    error("ERROR connecting");
  }
  else
  {
    printf("AKD connected\n");
  }
}  


void initMain()
{
  program = 1;
  PiControlHandle_g = -1; 
}



void receiveRequest()
{
  //printf("RECEIVING REQUEST\n");
  FD_SET(newsockfd, &fdsTCP);
  n = select(32, &fdsTCP, NULL, NULL, &tv);
  n = recv(newsockfd, recvReadBuff, 29, 0);
  //printf("REQUEST RECEIVED\n");
  
  if(recvReadBuff[0] == 1)
  {
    sendResponse(1);
  } 
  else if(recvReadBuff[0] == 2)
  {
    /*
    for(i = 1; i < 29; ++i)
    {
      printf("recvReadBuff_%d:%d\n",i, recvReadBuff[i]); 
    }*/
    sprintf(outputWriteBuff, "O_%d",  recvReadBuff[1]);
    writeVariableValue(outputWriteBuff, recvReadBuff[2]);
    sendResponse(2);
  }
  else if(recvReadBuff[0] == 3)
  {
    step=1;
    sendResponse(3);
  }
  else if(recvReadBuff[0] == 4)
  {
    sendResponse(4);
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
    int * sendWrite28 = (int*)(&sendWriteBuff[27]);
    
    * sendWrite0 = 1;
    * sendWrite1 = readVariableValue("I_1");
    * sendWrite2 = readVariableValue("I_2");
    * sendWrite3 = readVariableValue("I_3");
    * sendWrite4 = readVariableValue("I_4");
    * sendWrite5 = readVariableValue("I_5");
    * sendWrite6 = readVariableValue("I_6");
    * sendWrite7 = readVariableValue("I_7");
    * sendWrite8 = readVariableValue("I_8");
    * sendWrite9 = readVariableValue("I_9");
    * sendWrite10 = readVariableValue("I_10");
    * sendWrite11 = readVariableValue("I_11");
    * sendWrite12 = readVariableValue("I_12");
    * sendWrite13 = readVariableValue("I_13");
    * sendWrite14 = readVariableValue("I_14");
    * sendWrite15 = readVariableValue("O_1");
    * sendWrite16 = readVariableValue("O_2");
    * sendWrite17 = readVariableValue("O_3");
    * sendWrite18 = readVariableValue("O_4");
    * sendWrite19 = readVariableValue("O_5");
    * sendWrite20 = readVariableValue("O_6");
    * sendWrite21 = readVariableValue("O_7");
    * sendWrite22 = readVariableValue("O_8");
    * sendWrite23 = readVariableValue("O_9");
    * sendWrite24 = readVariableValue("O_10");
    * sendWrite25 = readVariableValue("O_11");
    * sendWrite26 = readVariableValue("O_12");
    * sendWrite27 = readVariableValue("O_13");
    * sendWrite28 = readVariableValue("O_14");
    FD_ZERO(&fdsTCP);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  
    n = select(32, NULL, &fdsTCP, NULL, &tv); 
  
    n = send(newsockfd, sendWriteBuff, 29, 0);
    memset(sendWriteBuff, 0, 29);
    //printf("RESPONSE SENT reqId:%d\n", reqId);

  }
  else if(reqId == 2)
  {
    int * sendRead0 = (int*)(&sendReadBuff[0]);
    * sendRead0 = 2;
    
    FD_ZERO(&fdsTCP);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  
    n = select(32, NULL, &fdsTCP, NULL, &tv); 
   
    n = send(newsockfd, sendReadBuff, 29, 0);
    memset(sendReadBuff, 0, 29);
    //printf("RESPONSE SENT reqId:%d\n", reqId);
  }
  else if(reqId == 3)
  {
    int * sendWrite0 = (int*)(&sendWriteBuff[0]);
    * sendWrite0 = 3;
    
    FD_ZERO(&fdsTCP);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  
    n = select(32, NULL, &fdsTCP, NULL, &tv); 
    
    n = send(newsockfd, sendWriteBuff, 29, 0);
    memset(sendWriteBuff, 0, 29);
    //printf("RESPONSE SENT reqId:%d\n", reqId);
  }
  
  else if(reqId == 4)
  {
    int * sendWrite0 = (int*)(&sendWriteBuff[0]);
    int * sendWrite1 = (int*)(&sendWriteBuff[1]);
    * sendWrite0 = 4;
    * sendWrite1 = step;
    
    FD_ZERO(&fdsTCP);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  
    n = select(32, NULL, &fdsTCP, NULL, &tv); 
   
    n = send(newsockfd, sendWriteBuff, 29, 0);
    memset(sendWriteBuff, 0, 29);
    //printf("RESPONSE SENT reqId:%d\n", reqId);
  }
}


void diagnostics()
{
  switch(step)
  {
    case 0:
      break;

    case 11111111:
      writeVariableValue("O_10", 1);
      usleep(10000);
      step = 2;
      break;
 
    case 111111111:
      if(readVariableValue("I_9")==1)
      {
        step = 3;
      }
      break;

    case 1:
    {
      int i;
      int * read1 = (int*)(&readBuff[0]);
      int * read2 = (int*)(&readBuff[2]);
      int * read3 = (int*)(&readBuff[4]);
      int * read4 = (int*)(&readBuff[6]);
      int * read5 = (int*)(&readBuff[7]);
      int * read6 = (int*)(&readBuff[8]);
      int * read7 = (int*)(&readBuff[10]);


      memset(readBuff, 0, 12);
      * read1 = transId;   
      * read2 = htons(0);
      * read3 = htons(6);
      * read4 = 1;
      * read5 = 3;
      * read6 = htons(2072);
      * read7 = htons(2);
        
      FD_ZERO(&fdsAKD);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      conn_AKD = select(32, NULL, &fdsAKD, NULL, &tv);
      conn_AKD = send(s, readBuff, 12, 0);
      printf("Message Sent! - read feedback position\n");
      FD_SET(s, &fdsAKD);
      conn_AKD = select(32, &fdsAKD, NULL, NULL, &tv);
      conn_AKD = recv(s, readBuff_recv, 50 , 0);
      printf("Message Received! - read feedback position\n");
      for(i = 0; i < 50; i++)
      {
        printf("readBuff_recv[%d]:%s\n", i, readBuff_recv);
      }
      transId++;
      step = 0;
      break;
	   
    }
    case 111:
      writeVariableValue("O_1", 1);
      step = 2;
      break;

    case 222:
      writeVariableValue("O_10", 1);
      usleep(10000);
      step = 3;
      break;
    
    case 333:
      if(readVariableValue("I_7")==1)
      {
        step = 4;
      }
      break;
    case 444:
      writeVariableValue("O_10", 0);
      step = 5;
      break;

    case 555:
      writeVariableValue("O_9", 1);
      step = 6;
      break;

    case 666:
      if(readVariableValue("I_7")==1)
      {
        step = 7;
      }
      break;

    case 777:
      writeVariableValue("O_9", 0);
      step = 8;
      break;
   
    case 888:
      writeVariableValue("O_1", 0);
      step = 0;
      break;
   }
}

