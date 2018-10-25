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
    printf("Step:%d\n", step);
    printf("Program:%d\n", program);
    printf("PageNum:%d\n", pageNum);
    
    if(readVariableValue("I_1_i03") && step == 0)
    {
      step = 1;
    }
    else if(readVariableValue("I_2_i03"))
    {
      step = -1;
    }

    if(step != 0)
    {
      inCycle = 1;
    }
    else
    { 
      inCycle = 0;
    }

    //if(!inCycle)
    //{
    receiveMessage();
    sendMessage();
    //  counter = 0;
    //}
    //else
    //{
    //  while(counter < 4)
    //  {
    //    receiveMessage();
    //    sendMessage();
    //    counter++;
    // }
    //}
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
  int * clear1 =  (int*)(&obufCl[0]);
  int * clear2 =  (int*)(&obufCl[2]);
  int * clear3 =  (int*)(&obufCl[4]);
  int * clear4 =  (int*)(&obufCl[6]);
  int * clear5 =  (int*)(&obufCl[7]);
  int * clear6 =  (int*)(&obufCl[8]);
  int * clear7 =  (int*)(&obufCl[10]);
  int * clear8 =  (int*)(&obufCl[12]);
  int * clear9 =  (int*)(&obufCl[16]);
 
  int * writePosTen1 = (int*)(&writePosTenBuff[0]);
  int * writePosTen2 = (int*)(&writePosTenBuff[2]);
  int * writePosTen3 = (int*)(&writePosTenBuff[4]);
  int * writePosTen4 = (int*)(&writePosTenBuff[6]);
  int * writePosTen5 = (int*)(&writePosTenBuff[7]);
  int * writePosTen6 = (int*)(&writePosTenBuff[8]);
  int * writePosTen7 = (int*)(&writePosTenBuff[10]);
  int * writePosTen8 = (int*)(&writePosTenBuff[12]);
  int * writePosTen11 = (int*)(&writePosTenBuff[21]);
  int * writePosTen12 = (int*)(&writePosTenBuff[28]);
  int * writePosTen13 = (int*)(&writePosTenBuff[29]);
  int * writePosTen14 = (int*)(&writePosTenBuff[33]);
  int * writePosTen15 = (int*)(&writePosTenBuff[40]);
  int * writePosTen16 = (int*)(&writePosTenBuff[44]);
  int * writePosTen17 = (int*)(&writePosTenBuff[48]);
  int * writePosTen18 = (int*)(&writePosTenBuff[52]);
  
  int * writePosUp1 = (int*)(&writePosUpBuff[0]);
  int * writePosUp2 = (int*)(&writePosUpBuff[2]);
  int * writePosUp3 = (int*)(&writePosUpBuff[4]);
  int * writePosUp4 = (int*)(&writePosUpBuff[6]);
  int * writePosUp5 = (int*)(&writePosUpBuff[7]);
  int * writePosUp6 = (int*)(&writePosUpBuff[8]);
  int * writePosUp7 = (int*)(&writePosUpBuff[10]);
  int * writePosUp8 = (int*)(&writePosUpBuff[12]);
  int * writePosUp11 = (int*)(&writePosUpBuff[21]);
  int * writePosUp12 = (int*)(&writePosUpBuff[28]);
  int * writePosUp13 = (int*)(&writePosUpBuff[29]);
  int * writePosUp14 = (int*)(&writePosUpBuff[33]);
  int * writePosUp15 = (int*)(&writePosUpBuff[40]);
  int * writePosUp16 = (int*)(&writePosUpBuff[44]);
  int * writePosUp17 = (int*)(&writePosUpBuff[48]);
  int * writePosUp18 = (int*)(&writePosUpBuff[52]);
 
  int * writePosDown1 = (int*)(&writePosDownBuff[0]);
  int * writePosDown2 = (int*)(&writePosDownBuff[2]);
  int * writePosDown3 = (int*)(&writePosDownBuff[4]);
  int * writePosDown4 = (int*)(&writePosDownBuff[6]);
  int * writePosDown5 = (int*)(&writePosDownBuff[7]);
  int * writePosDown6 = (int*)(&writePosDownBuff[8]);
  int * writePosDown7 = (int*)(&writePosDownBuff[10]);
  int * writePosDown8 = (int*)(&writePosDownBuff[12]);
  int * writePosDown11 = (int*)(&writePosDownBuff[21]);
  int * writePosDown12 = (int*)(&writePosDownBuff[28]);
  int * writePosDown13 = (int*)(&writePosDownBuff[29]);
  int * writePosDown14 = (int*)(&writePosDownBuff[33]);
  int * writePosDown15 = (int*)(&writePosDownBuff[40]);
  int * writePosDown16 = (int*)(&writePosDownBuff[44]);
  int * writePosDown17 = (int*)(&writePosDownBuff[48]);
  int * writePosDown18 = (int*)(&writePosDownBuff[52]);
 

  int * moveTask1 =  (int*)(&obufMT[0]);
  int * moveTask2 =  (int*)(&obufMT[2]);
  int * moveTask3 =  (int*)(&obufMT[4]);
  int * moveTask4 =  (int*)(&obufMT[6]);
  int * moveTask5 =  (int*)(&obufMT[7]);
  int * moveTask6 =  (int*)(&obufMT[8]);
  int * moveTask7 =  (int*)(&obufMT[10]);
  int * moveTask8 =  (int*)(&obufMT[12]);
  int * moveTask9 =  (int*)(&obufMT[13]);
  
  int * moveTask1Next =  (int*)(&obufMTN[0]);
  int * moveTask2Next =  (int*)(&obufMTN[2]);
  int * moveTask3Next =  (int*)(&obufMTN[4]);
  int * moveTask4Next =  (int*)(&obufMTN[6]);
  int * moveTask5Next =  (int*)(&obufMTN[7]);
  int * moveTask6Next =  (int*)(&obufMTN[8]);
  int * moveTask7Next =  (int*)(&obufMTN[10]);
  int * moveTask8Next =  (int*)(&obufMTN[12]);
  int * moveTask9Next =  (int*)(&obufMTN[13]);
 

  int * dinModeChange1 =  (int*)(&obufDMC[0]);
  int * dinModeChange2 =  (int*)(&obufDMC[2]);
  int * dinModeChange3 =  (int*)(&obufDMC[4]);
  int * dinModeChange4 =  (int*)(&obufDMC[6]);
  int * dinModeChange5 =  (int*)(&obufDMC[7]);
  int * dinModeChange6 =  (int*)(&obufDMC[8]);
  int * dinModeChange7 =  (int*)(&obufDMC[10]);
  int * dinModeChange8 =  (int*)(&obufDMC[12]);
  int * dinModeChange9 =  (int*)(&obufDMC[13]);
  
  int * drvSave1 =  (int*)(&obufDS[0]);
  int * drvSave2 =  (int*)(&obufDS[2]);
  int * drvSave3 =  (int*)(&obufDS[4]);
  int * drvSave4 =  (int*)(&obufDS[6]);
  int * drvSave5 =  (int*)(&obufDS[7]);
  int * drvSave6 =  (int*)(&obufDS[8]);
  int * drvSave7 =  (int*)(&obufDS[10]);
  int * drvSave8 =  (int*)(&obufDS[12]);
  int * drvSave9 =  (int*)(&obufDS[13]);

  memset(obufCl, 0, 17);
  * clear1 = transId;   
  * clear2 = htons(0);
  * clear3 = htons(11);
  * clear4 = 1;
  * clear5 = 16;
  * clear6 = htons(530);
  * clear7 = htons(2);
  * clear8 = 4;
  * clear9 = 2; 
    
  memset(writePosTenBuff, 0, 58);
  * writePosTen1 = transId;   
  * writePosTen2 = htons(0);
  * writePosTen3 = htons(47);
  * writePosTen4 = 1;
  * writePosTen5 = 16;
  * writePosTen6 = htons(8192);
  * writePosTen7 = htons(20);
  * writePosTen8 = 40;
  * writePosTen11 = htonl(2000000);   
  * writePosTen12 = 16;           
  * writePosTen13 = htonl(5000000);  
  * writePosTen14 = htonl(5000000);  
  * writePosTen15 = 100;            
  * writePosTen16 = 0;            
  * writePosTen17 = 1;            
  * writePosTen18 = 1;  
 
  memset(writePosUpBuff, 0, 58);
  * writePosUp1 = transId;   
  * writePosUp2 = htons(0);
  * writePosUp3 = htons(47);
  * writePosUp4 = 1;
  * writePosUp5 = 16;
  * writePosUp6 = htons(8192);
  * writePosUp7 = htons(20);
  * writePosUp8 = 40;
  * writePosUp11 = htonl(2000000);   
  * writePosUp12 = 16;           
  * writePosUp13 = htonl(5000000);  
  * writePosUp14 = htonl(5000000);  
  * writePosUp15 = 100;            
  * writePosUp16 = 0;            
  * writePosUp17 = 1;            
  * writePosUp18 = 1;  
 
  memset(writePosDownBuff, 0, 58);
  * writePosDown1 = transId;   
  * writePosDown2 = htons(0);
  * writePosDown3 = htons(47);
  * writePosDown4 = 1;
  * writePosDown5 = 16;
  * writePosDown6 = htons(8192);
  * writePosDown7 = htons(20);
  * writePosDown8 = 40;
  * writePosDown11 = htonl(2000000);   
  * writePosDown12 = 16;           
  * writePosDown13 = htonl(5000000);  
  * writePosDown14 = htonl(5000000);  
  * writePosDown15 = 100;            
  * writePosDown16 = 0;            
  * writePosDown17 = 1;            
  * writePosDown18 = 1;  
 
  memset(obufMT, 0, 17);
  * moveTask1 = transId;   
  * moveTask2 = htons(0);
  * moveTask3 = htons(11);
  * moveTask4 = 1;
  * moveTask5 = 16;
  * moveTask6 = htons(2014);
  * moveTask7 = htons(2);
  * moveTask8 = 4;
  * moveTask9 = 2;
  
  memset(obufMTN, 0, 17);
  * moveTask1Next = transId;   
  * moveTask2Next = htons(0);
  * moveTask3Next = htons(11);
  * moveTask4Next = 1;
  * moveTask5Next = 16;
  * moveTask6Next = htons(2016);
  * moveTask7Next = htons(2);
  * moveTask8Next = 4;
  * moveTask9Next = 2;


  memset(obufDMC, 0, 17);
  * dinModeChange1 = transId;   
  * dinModeChange2 = htons(0);
  * dinModeChange3 = htons(11);
  * dinModeChange4 = 1;
  * dinModeChange5 = 16;
  * dinModeChange6 = htons(152);
  * dinModeChange7 = htons(2);
  * dinModeChange8 = 4;
  * dinModeChange9 = htons(1);
 

   memset(obufDS, 0, 17);
  * drvSave1 = transId;   
  * drvSave2 = htons(0);
  * drvSave3 = htons(11);
  * drvSave4 = 1;
  * drvSave5 = 16;
  * drvSave6 = htons(8210);
  * drvSave7 = htons(2);
  * drvSave8 = 4;
  * drvSave9 = htonl(1);
 

  pageNum = 2;
  program = 1;
  PiControlHandle_g = -1; 
  step = -1;
}



void sendMessage()
{
  int * sendMessagePtr0 = (int*)(&sendMessageBuff[0]);
  int * sendMessagePtr1 = (int*)(&sendMessageBuff[1]);
  int * sendMessagePtr2 = (int*)(&sendMessageBuff[2]);
  int * sendMessagePtr3 = (int*)(&sendMessageBuff[3]);
  int * sendMessagePtr4 = (int*)(&sendMessageBuff[4]);
  int * sendMessagePtr5 = (int*)(&sendMessageBuff[5]);
  int * sendMessagePtr6 = (int*)(&sendMessageBuff[6]);
  int * sendMessagePtr7 = (int*)(&sendMessageBuff[7]);
  int * sendMessagePtr8 = (int*)(&sendMessageBuff[8]);
  int * sendMessagePtr9 = (int*)(&sendMessageBuff[9]);
  int * sendMessagePtr10 = (int*)(&sendMessageBuff[10]);
  int * sendMessagePtr11 = (int*)(&sendMessageBuff[11]);
  int * sendMessagePtr12 = (int*)(&sendMessageBuff[12]);
  int * sendMessagePtr13 = (int*)(&sendMessageBuff[13]);
  int * sendMessagePtr14 = (int*)(&sendMessageBuff[14]);
  int * sendMessagePtr15 = (int*)(&sendMessageBuff[15]);
  int * sendMessagePtr16 = (int*)(&sendMessageBuff[16]);
  int * sendMessagePtr17 = (int*)(&sendMessageBuff[17]);
  int * sendMessagePtr18 = (int*)(&sendMessageBuff[18]);
  int * sendMessagePtr19 = (int*)(&sendMessageBuff[19]);
  int * sendMessagePtr20 = (int*)(&sendMessageBuff[20]);
  int * sendMessagePtr21 = (int*)(&sendMessageBuff[21]);
  int * sendMessagePtr22 = (int*)(&sendMessageBuff[22]);
  int * sendMessagePtr23 = (int*)(&sendMessageBuff[23]);
  int * sendMessagePtr24 = (int*)(&sendMessageBuff[24]);
  int * sendMessagePtr25 = (int*)(&sendMessageBuff[25]);
  int * sendMessagePtr26 = (int*)(&sendMessageBuff[26]);
  int * sendMessagePtr27 = (int*)(&sendMessageBuff[27]);
  int * sendMessagePtr28 = (int*)(&sendMessageBuff[28]);
  int * sendMessagePtr29 = (int*)(&sendMessageBuff[29]);
  int * sendMessagePtr30 = (int*)(&sendMessageBuff[30]);
  int * sendMessagePtr31 = (int*)(&sendMessageBuff[31]);
  int * sendMessagePtr32 = (int*)(&sendMessageBuff[32]);
  int * sendMessagePtr33 = (int*)(&sendMessageBuff[33]);
  int * sendMessagePtr34 = (int*)(&sendMessageBuff[34]);
  int * sendMessagePtr35 = (int*)(&sendMessageBuff[35]);
  int * sendMessagePtr36 = (int*)(&sendMessageBuff[36]);
  int * sendMessagePtr37 = (int*)(&sendMessageBuff[37]);
  int * sendMessagePtr38 = (int*)(&sendMessageBuff[38]);
  int * sendMessagePtr39 = (int*)(&sendMessageBuff[39]);
  int * sendMessagePtr40 = (int*)(&sendMessageBuff[40]);
  int * sendMessagePtr41 = (int*)(&sendMessageBuff[41]);
  int * sendMessagePtr42 = (int*)(&sendMessageBuff[42]);
  int * sendMessagePtr43 = (int*)(&sendMessageBuff[43]);
  int * sendMessagePtr44 = (int*)(&sendMessageBuff[44]);
  int * sendMessagePtr45 = (int*)(&sendMessageBuff[45]);
  int * sendMessagePtr46 = (int*)(&sendMessageBuff[46]);
  int * sendMessagePtr47 = (int*)(&sendMessageBuff[47]);
  int * sendMessagePtr48 = (int*)(&sendMessageBuff[48]);
  int * sendMessagePtr49 = (int*)(&sendMessageBuff[49]);
  int * sendMessagePtr50 = (int*)(&sendMessageBuff[50]);
  int * sendMessagePtr51 = (int*)(&sendMessageBuff[51]);
  int * sendMessagePtr52 = (int*)(&sendMessageBuff[52]);  
  int * sendMessagePtr53 = (int*)(&sendMessageBuff[53]);
  int * sendMessagePtr54 = (int*)(&sendMessageBuff[54]);
  int * sendMessagePtr55 = (int*)(&sendMessageBuff[55]);
  int * sendMessagePtr56 = (int*)(&sendMessageBuff[56]);
  int * sendMessagePtr57 = (int*)(&sendMessageBuff[57]);
  int * sendMessagePtr58 = (int*)(&sendMessageBuff[58]);
  int * sendMessagePtr59 = (int*)(&sendMessageBuff[59]);
  int * sendMessagePtr60 = (int*)(&sendMessageBuff[60]);
  int * sendMessagePtr61 = (int*)(&sendMessageBuff[61]);
  int * sendMessagePtr62 = (int*)(&sendMessageBuff[62]);
  int * sendMessagePtr63 = (int*)(&sendMessageBuff[63]);
  int * sendMessagePtr64 = (int*)(&sendMessageBuff[64]);
  int * sendMessagePtr65 = (int*)(&sendMessageBuff[65]);
  int * sendMessagePtr66 = (int*)(&sendMessageBuff[66]);
  int * sendMessagePtr67 = (int*)(&sendMessageBuff[67]);
  int * sendMessagePtr68 = (int*)(&sendMessageBuff[68]);
  int * sendMessagePtr69 = (int*)(&sendMessageBuff[69]);
  int * sendMessagePtr70 = (int*)(&sendMessageBuff[70]);
  int * sendMessagePtr71 = (int*)(&sendMessageBuff[71]);
  int * sendMessagePtr72 = (int*)(&sendMessageBuff[72]);
  int * sendMessagePtr73 = (int*)(&sendMessageBuff[73]);
  int * sendMessagePtr74 = (int*)(&sendMessageBuff[74]);
  int * sendMessagePtr75 = (int*)(&sendMessageBuff[75]);
  int * sendMessagePtr76 = (int*)(&sendMessageBuff[76]);
  int * sendMessagePtr77 = (int*)(&sendMessageBuff[77]);
  int * sendMessagePtr78 = (int*)(&sendMessageBuff[78]);
  int * sendMessagePtr79 = (int*)(&sendMessageBuff[79]);
  int * sendMessagePtr80 = (int*)(&sendMessageBuff[80]);
  int * sendMessagePtr81 = (int*)(&sendMessageBuff[81]);
  int * sendMessagePtr82 = (int*)(&sendMessageBuff[82]);
  int * sendMessagePtr83 = (int*)(&sendMessageBuff[83]);
  int * sendMessagePtr84 = (int*)(&sendMessageBuff[84]);

  * sendMessagePtr0 = readVariableValue("I_1");
  * sendMessagePtr1 = readVariableValue("I_2");
  * sendMessagePtr2 = readVariableValue("I_3");
  * sendMessagePtr3 = readVariableValue("I_4");
  * sendMessagePtr4 = readVariableValue("I_5");
  * sendMessagePtr5 = readVariableValue("I_6");
  * sendMessagePtr6 = readVariableValue("I_7");
  * sendMessagePtr7 = readVariableValue("I_8");
  * sendMessagePtr8 = readVariableValue("I_9");
  * sendMessagePtr9 = readVariableValue("I_10");
  * sendMessagePtr10 = readVariableValue("I_11");
  * sendMessagePtr11 = readVariableValue("I_12");
  * sendMessagePtr12 = readVariableValue("I_13");
  * sendMessagePtr13 = readVariableValue("I_14");
  * sendMessagePtr14 = readVariableValue("I_1_i03");
  * sendMessagePtr15 = readVariableValue("I_2_i03");
  * sendMessagePtr16 = readVariableValue("I_3_i03");
  * sendMessagePtr17 = readVariableValue("I_4_i03");
  * sendMessagePtr18 = readVariableValue("I_5_i03");
  * sendMessagePtr19 = readVariableValue("I_6_i03");
  * sendMessagePtr20 = readVariableValue("I_7_i03");
  * sendMessagePtr21 = readVariableValue("I_8_i03");
  * sendMessagePtr22 = readVariableValue("I_9_i03");
  * sendMessagePtr23 = readVariableValue("I_10_i03");
  * sendMessagePtr24 = readVariableValue("I_11_i03");
  * sendMessagePtr25 = readVariableValue("I_12_i03");
  * sendMessagePtr26 = readVariableValue("I_13_i03");
  * sendMessagePtr27 = readVariableValue("I_14_i03");
  * sendMessagePtr28 = readVariableValue("I_1_i04");
  * sendMessagePtr29 = readVariableValue("I_2_i04");
  * sendMessagePtr30 = readVariableValue("I_3_i04");
  * sendMessagePtr31 = readVariableValue("I_4_i04");
  * sendMessagePtr32 = readVariableValue("I_5_i04");
  * sendMessagePtr33 = readVariableValue("I_6_i04");
  * sendMessagePtr34 = readVariableValue("I_7_i04");
  * sendMessagePtr35 = readVariableValue("I_8_i04");
  * sendMessagePtr36 = readVariableValue("I_9_i04");
  * sendMessagePtr37 = readVariableValue("I_10_i04");
  * sendMessagePtr38 = readVariableValue("I_11_i04");
  * sendMessagePtr39 = readVariableValue("I_12_i04");
  * sendMessagePtr40 = readVariableValue("I_13_i04");
  * sendMessagePtr41 = readVariableValue("I_14_i04");
 
  * sendMessagePtr42 = readVariableValue("O_1");
  * sendMessagePtr43 = readVariableValue("O_2");
  * sendMessagePtr44 = readVariableValue("O_3");
  * sendMessagePtr45 = readVariableValue("O_4");
  * sendMessagePtr46 = readVariableValue("O_5");
  * sendMessagePtr47 = readVariableValue("O_6");
  * sendMessagePtr48 = readVariableValue("O_7");
  * sendMessagePtr49 = readVariableValue("O_8");
  * sendMessagePtr50 = readVariableValue("O_9");
  * sendMessagePtr51 = readVariableValue("O_10");
  * sendMessagePtr52 = readVariableValue("O_11");
  * sendMessagePtr53 = readVariableValue("O_12");
  * sendMessagePtr54 = readVariableValue("O_13");
  * sendMessagePtr55 = readVariableValue("O_14");
  * sendMessagePtr56 = readVariableValue("O_1_i03");
  * sendMessagePtr57 = readVariableValue("O_2_i03");
  * sendMessagePtr58 = readVariableValue("O_3_i03");
  * sendMessagePtr59 = readVariableValue("O_4_i03");
  * sendMessagePtr60 = readVariableValue("O_5_i03");
  * sendMessagePtr61 = readVariableValue("O_6_i03");
  * sendMessagePtr62 = readVariableValue("O_7_i03");
  * sendMessagePtr63 = readVariableValue("O_8_i03");
  * sendMessagePtr64 = readVariableValue("O_9_i03");
  * sendMessagePtr65 = readVariableValue("O_10_i03");
  * sendMessagePtr66 = readVariableValue("O_11_i03");
  * sendMessagePtr67 = readVariableValue("O_12_i03");
  * sendMessagePtr68 = readVariableValue("O_13_i03");
  * sendMessagePtr69 = readVariableValue("O_14_i03");
  * sendMessagePtr70 = readVariableValue("O_1_i04");
  * sendMessagePtr71 = readVariableValue("O_2_i04");
  * sendMessagePtr72 = readVariableValue("O_3_i04");
  * sendMessagePtr73 = readVariableValue("O_4_i04");
  * sendMessagePtr74 = readVariableValue("O_5_i04");
  * sendMessagePtr75 = readVariableValue("O_6_i04");
  * sendMessagePtr76 = readVariableValue("O_7_i04");
  * sendMessagePtr77 = readVariableValue("O_8_i04");
  * sendMessagePtr78 = readVariableValue("O_9_i04");
  * sendMessagePtr79 = readVariableValue("O_10_i04");
  * sendMessagePtr80 = readVariableValue("O_11_i04");
  * sendMessagePtr81 = readVariableValue("O_12_i04");
  * sendMessagePtr82 = readVariableValue("O_13_i04");
  * sendMessagePtr83 = readVariableValue("O_14_i04");
  
  * sendMessagePtr84 = step;

  //FD_ZERO(&fdsTCP);
  //tv.tv_sec = 0;
  //tv.tv_usec = 0;

  //n = select(32, NULL, &fdsTCP, NULL, &tv); 
  n = send(newsockfd, sendMessageBuff, 85, 0);
  memset(sendMessageBuff, 0, 85);
}

void receiveMessage()
{
  int i;
  int currentState;
  int lastState;
  lastState = currentState;
  struct timeval timeout;
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;
  FD_ZERO(&fdsTCP);
  FD_SET(newsockfd, &fdsTCP);
  select(newsockfd+1, &fdsTCP, NULL, NULL, &timeout);  
  if(FD_ISSET(newsockfd, &fdsTCP))
  {
    recv(newsockfd, receiveMessageBuff, 8, 0);
    currentState = receiveMessageBuff[1];
    if(receiveMessageBuff[0] != -1)
    {
      if(receiveMessageBuff[0] < 15)
      {
	sprintf(outputWriteBuff, "O_%d",  receiveMessageBuff[0]);
      }
      else if(receiveMessageBuff[0] > 14 && receiveMessageBuff[0] < 29)
      {
	sprintf(outputWriteBuff, "O_%d_i03",  (receiveMessageBuff[0]-14));
      }
      else if(receiveMessageBuff[0] > 28 && receiveMessageBuff[0] < 43)
      {
	sprintf(outputWriteBuff, "O_%d_i04",  (receiveMessageBuff[0]-28));
      }
      if(receiveMessageBuff[1] != -1)
      {
	if(lastState != currentState)
	{
	  writeVariableValue(outputWriteBuff, receiveMessageBuff[1]);
	}
      }
    }
    if(receiveMessageBuff[2])
    {
      step = 1;
    }
    if(receiveMessageBuff[3])
    {
      step++;
    }
    if(receiveMessageBuff[4])
    {
      step = -1;
    }
    press = receiveMessageBuff[5];
    selectedCan = receiveMessageBuff[6];
    pageNum = receiveMessageBuff[7];
    //for(i = 0; i < 9; i++)
    //{
    //  printf("receiveMessageBuff[%d]:%d\n", i, receiveMessageBuff[i]);
    //}
  }
  else
  {
    printf("\t TIMEOUT \n");
  }
}

void diagnostics()
{
  switch(step)
  {
    case -1:
      writeVariableValue("O_5_i03", 0);
      writeVariableValue("O_7_i03", 0);
      writeVariableValue("O_8_i03", 0);
      step = 0;
      break;

    case 0:
      break;
   
    case 1:
    { 
      printf("STEP: %d\n", step);
      int * moveTask1 =  (int*)(&obufMT[0]); 
      int * moveTask9 =  (int*)(&obufMT[13]);
      int * moveTask1Next =  (int*)(&obufMTN[0]); 
      int * moveTask9Next =  (int*)(&obufMTN[13]);
      int * drvSave1 = (int*)(&obufDS[0]);
      int * dinModeChange1 = (int*)(&obufDMC[0]);
      int * dinModeChange9 = (int*)(&obufDMC[13]);
      int * writePosUp1 = (int*)(&writePosUpBuff[0]);
      int * writePosUp9 =  (int*)(&writePosUpBuff[16]);
      int * writePosUp10 = (int*)(&writePosUpBuff[17]);
      int * writePosDown1 = (int*)(&writePosDownBuff[0]);
      int * writePosDown9 =  (int*)(&writePosDownBuff[16]);
      int * writePosDown10 = (int*)(&writePosDownBuff[17]);  
      int * writePosDown11 = (int*)(&writePosDownBuff[21]);
     
      * moveTask1 = transId;
      if(selectedCan == 0)
      {
	* moveTask9 = htonl(1000);                
	* moveTask9Next = htonl(2000);
        * writePosUp9 = 1;       
        * writePosUp10 = htonl((0)*1000); /*some value*/
        * writePosDown9 = 2;       
        * writePosDown10 = htonl((0)*1000); /*some value*/
      }
      else if(selectedCan == 1)
      {
	* moveTask9 = htonl(3000);
	* moveTask9Next = htonl(4000);
        * writePosUp9 = 3;       
        * writePosUp10 = htonl((0)*1000); /*some value*/
        * writePosDown9 = 4;       
        * writePosDown10 = htonl((0)*1000); /*some value*/
      }
      else if(selectedCan == 2)
      {
        * moveTask9 = htonl(5000);
        * moveTask9Next = htonl(6000);     
        * writePosUp9 = 5;       
        * writePosUp10 = htonl((0)*1000); /*some value*/
        * writePosDown9 = 6;       
        * writePosDown10 = htonl((0)*1000); /*some value*/
      }
      else if(selectedCan == 3)
      {
	* moveTask9 = htonl(7000);
	* moveTask9Next = htonl(8000); 
        * writePosUp9 = 7;       
        * writePosUp10 = htonl((0)*1000);
        * writePosDown9 = 8;       
        * writePosDown10 = htonl((35)*1000);
      }

      sendModbus(s, obufMT, 17, ibufMT, 50, "move task 1 - revert to original positions");
      * moveTask1Next = transId;
      sendModbus(s, obufMTN, 17, ibufMTN, 50, "move task 2 - revert to original positions");
   
      /* write template position values */
      * writePosUp1 = transId;       
      sendModbus(s, writePosUpBuff, 53, writePosUpBuff_recv, 50, "template position parameter saved");
      * writePosDown1 = transId;       
      * writePosDown11 = htonl(20000); /* set speed to 20 */
      sendModbus(s, writePosDownBuff, 53, writePosDownBuff_recv, 50, "template position parameter saved");
 
      /* to be added -  change din4 mode to quick stop15 */
       * dinModeChange1 = transId;
       * dinModeChange9 = htonl(15);
      sendModbus(s, obufDMC, 17, ibufDMC, 50, "save to drive");
 
      * drvSave1 = transId;
      sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive");
    

      writeVariableValue("O_5_i03", 0);
      writeVariableValue("O_7_i03", 0);
      writeVariableValue("O_8_i03", 0);
      writeVariableValue("O_1_i03", 0);
 
      writeVariableValue("O_1", 0);
      writeVariableValue("O_2", 1);
      /* priprava izhodov za pomik na zgornjo pozicijo */
      if(selectedCan == 0) /* mala */
      {
        writeVariableValue("O_12", 1);
      }
      else if(selectedCan == 1) /* mala 2 */
      {
        writeVariableValue("O_13", 1);
      }
      else if(selectedCan == 2) /* srednja */
      {
        writeVariableValue("O_12", 1);
        writeVariableValue("O_13", 1);
      }
      else if(selectedCan == 3) /* velika */
      {
        writeVariableValue("O_14", 1);
      }
      usleep(delay_time);
      writeVariableValue("O_1_i03", 0);
      writeVariableValue("O_2", 0);
 
      step = 2;
      break;
    }
    case 2:  /* pomik na zgornjo pozicijo */
      printf("STEP: %d\n", step);
      printf("pomik na zgornjo pozicijo\n");
      writeVariableValue("O_1_i03", 1);
      writeVariableValue("O_9", 1);
      usleep(delay_time);
      writeVariableValue("O_1_i03", 0);
      writeVariableValue("O_9", 0);
      
      writeVariableValue("O_2", 0);
      writeVariableValue("O_11", 0);
      writeVariableValue("O_12", 0);
      writeVariableValue("O_13", 0);
      writeVariableValue("O_14", 0);
      
      /* priprava izhodov za pomik na spodnjo pozicijo */
      if(selectedCan == 0) /* mala */
      {
	writeVariableValue("O_11", 1);
      }
      else if(selectedCan == 1) /* mala 2 */
      {
	writeVariableValue("O_11", 1);
	writeVariableValue("O_12", 1);
      }
      else if(selectedCan == 2) /* srednja */
      {
	writeVariableValue("O_11", 1);
	writeVariableValue("O_13", 1);
      }
      else if(selectedCan == 3) /* velika*/
      {
	writeVariableValue("O_11", 1);
	writeVariableValue("O_12", 1);
	writeVariableValue("O_13", 1);
      } 
      step = 3;
      break;   
    
    case 3:
      printf("STEP: %d\n", step);
      printf("preverim ali je bil pomik izveden\n");
      if(readVariableValue("I_11") && readVariableValue("I_12"))
      { 
        step = 4;
      }
      break;

    case 4: /* presa - premik na pozicijo meritve */
      writeVariableValue("O_10", 1);
      usleep(delay_time); 
      writeVariableValue("O_10", 0);
      step = 5;
      break;

    case 5:
      printf("STEP: %d\n", step);
      printf("preverim ali je bil pomik izveden\n");
      if(readVariableValue("I_13_i03"))
      { 
        step = 6;
      }
      break;
    
    case 6:
      printf("STEP: %d\n", step);
      printf("preberem podatek o trenutni poziciji in ga shranim v ustrezne motion taske");
      int w;
      int * read1 = (int*)(&readBuff[0]);
      int * read2 = (int*)(&readBuff[2]);
      int * read3 = (int*)(&readBuff[4]);
      int * read4 = (int*)(&readBuff[6]);
      int * read5 = (int*)(&readBuff[7]);
      int * read6 = (int*)(&readBuff[8]);
      int * read7 = (int*)(&readBuff[10]);
      int * writePosTen1 = (int*)(&writePosTenBuff[0]);
      int * writePosTen9 =  (int*)(&writePosTenBuff[16]);
      int * writePosTen10 = (int*)(&writePosTenBuff[17]);
      int * writePosDown1 = (int*)(&writePosDownBuff[0]);
      int * writePosDown9 =  (int*)(&writePosDownBuff[16]);
      int * writePosDown10 = (int*)(&writePosDownBuff[17]);
      int * writePosDown11 = (int*)(&writePosDownBuff[21]);
      int * dinModeChange1 =  (int*)(&obufDMC[0]);
      int * dinModeChange9 =  (int*)(&obufDMC[13]);
      int * drvSave1 = (int*)(&obufDS[0]);
   
      memset(readBuff, 0, 12);
      * read2 = htons(0);
      * read3 = htons(6);
      * read4 = 1;
      * read5 = 3;
      * read6 = htons(2072);
      * read7 = htons(2);
      * writePosTen9 = 10;       
      // * moveTask9Next = htonl(10000);                
         
      * read1 = transId;   
      sendModbus(s, readBuff, 12, readBuff_recv, 50, "read feedback position");
      w = ((readBuff_recv[10]<<16) + (readBuff_recv[11]<<8) + readBuff_recv[12]);     
      * writePosTen10 = htonl(w);
      printf("POSITION FEEDBACK:%d\n", w);
     
      * writePosTen1 = transId;       
      sendModbus(s, writePosTenBuff, 53, writePosTenBuff_recv, 50, "position 10 parameter");
    
      if(selectedCan == 0) /* mala */
      {
        * writePosDown9 = 2;    
      }
      else if(selectedCan == 1) /* mala 2 */
      {
        * writePosDown9 = 4;    
      }
      else if(selectedCan == 2) /* srednja */
      {
        * writePosDown9 = 6;       
      }
      else if(selectedCan == 3) /* velika*/
      {
        * writePosDown9 = 8;       
      }
 
      w = ((readBuff_recv[10]<<16) + (readBuff_recv[11]<<8) + readBuff_recv[12]);     
      * writePosDown10 = htonl(w + press);
      * writePosDown1 = transId;       
      * writePosDown11 = htonl(2000000); /* set speed to 2000 */
     
      sendModbus(s, writePosDownBuff, 53, writePosDownBuff_recv, 50, "position 10 parameter");

      * dinModeChange1 = transId;
      * dinModeChange9 = htonl(0);
      sendModbus(s, obufDMC, 17, ibufDMC, 50, "save to drive");
      
      * drvSave1 = transId;
      sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive");
      
      step = 7;
      break;
   
   case 7:	
      printf("STEP: %d\n", step);
      printf(" presa - pomik v zgornjo pozicijo\n");
      writeVariableValue("O_9", 1);
      usleep(delay_time);
      writeVariableValue("O_9", 0);
      step = 8;

   case 8: /* preverim ali je bil pomik izveden */
      printf("STEP: %d\n", step);
      printf("preverim ali je bil pomik izveden\n");
      if(readVariableValue("I_11"))
      { 
        step = 0;
      }
      break;

    case 9: /* premik na spodnjo pozicijo */
      printf("STEP: %d\n", step);
      printf("premik na spodnjo pozicijo\n");
      writeVariableValue("O_1", 1);
      //writeVariableValue("O_10", 1);
      writeVariableValue("O_14_i03", 1); /* premik na vmesno pozicijo*/
      writeVariableValue("O_1_i03", 1);
      usleep(delay_time); 
      writeVariableValue("O_1_i03", 0);        

      writeVariableValue("O_11", 0);
      writeVariableValue("O_12", 0);
      writeVariableValue("O_13", 0);
      writeVariableValue("O_14", 0);
    
      if(selectedCan == 0) /* mala */
      {
	writeVariableValue("O_11", 1);
      }
      else if(selectedCan == 1) /* mala 2 */
      {
	writeVariableValue("O_11", 1);
	writeVariableValue("O_12", 1);
      }
      else if(selectedCan == 2) /* srednja */
      {
	writeVariableValue("O_11", 1);
	writeVariableValue("O_13", 1);
      }
      else if(selectedCan == 3) /* velika*/
      {
	writeVariableValue("O_11", 1);
	writeVariableValue("O_12", 1);
	writeVariableValue("O_13", 1);
      } 
      //writeVariableValue("O_10", 0);
      writeVariableValue("O_14_i03", 0);
      
      step = 10;
      break;
    
    case 10: /* preverim ali sta presa in gripper izvedla pomik */
      printf("STEP: %d\n", step);
      if(readVariableValue("I_12") && readVariableValue("I_14_i03")) /* premik izveden*/
      {
        if(readVariableValue("I_13_i03"))
        {
	  do
	  {
	    cylCond = 0;
	    if(readVariableValue("I_11_i03") == 0 && readVariableValue("I_12_i03") == 1)
	    {    
	      writeVariableValue("O_8_i03", 1);  /* cilinder 4 navzdol - odpiranje celjusti */
	      cylCond = 1;
	    }
	    printf("step:%d, I_11:%d, I_12:%d\n", step, readVariableValue("I_11_i03"), readVariableValue("I_12_i03"));
	  }
	  while(!cylCond);
	  
	  do
	  {
	    cylCond = 0;
	    if(readVariableValue("I_3_i03") == 1 && readVariableValue("I_4_i03") == 0)
	    {
	      writeVariableValue("O_5_i03", 1);  /* cilinder 1 navzgor - zapiranje celjusti */
	      cylCond = 1;
	    }
	    printf("step:%d, I_3:%d, I_4:%d\n", step, readVariableValue("I_3_i03"), readVariableValue("I_4_i03"));
	  }
	  while(!cylCond);
	  printf("preverim ali je pomik izveden I_11:%d I_12:%d\n", readVariableValue("I_11"), readVariableValue("I_12"));
          step = 11;
	}
        else
        {
          step = 0;
          /* handle error */
        }  
      }
      break;
    
    case 11:
      printf("STEP: %d\n", step);
      printf("pomik v zgornjo pozicijo\n");
      writeVariableValue("O_10", 1);
      usleep(delay_time);
      writeVariableValue("O_10", 0);
      step = 12; 
      break;

    case 12: /* pomik v zgornjo pozicijo */
      printf("STEP: %d\n", step);
      printf("pomik v zgornjo pozicijo\n");
      writeVariableValue("O_1_i03", 1);
      writeVariableValue("O_2", 1);
      writeVariableValue("O_1", 0);
      writeVariableValue("O_9", 1);
      usleep(delay_time);
      writeVariableValue("O_9", 0);
      writeVariableValue("O_2", 0);
      writeVariableValue("O_1_i03", 0);      
      writeVariableValue("O_11", 0);
      writeVariableValue("O_12", 0);
      writeVariableValue("O_13", 0);
      writeVariableValue("O_14", 0);
     
      if(selectedCan == 0) /* mala */
      {
        writeVariableValue("O_12", 1);
      }
      else if(selectedCan == 1) /* mala 2 */
      {
        writeVariableValue("O_13", 1);
      }
      else if(selectedCan == 2) /* srednja */
      {
        writeVariableValue("O_12", 1);
        writeVariableValue("O_13", 1);
      }
      else if(selectedCan == 3) /* velika */
      {
        writeVariableValue("O_14", 1);
      }
      
      do
      {
        cylCond = 0;
        if(readVariableValue("I_11_i03") == 1 && readVariableValue("I_12_i03") == 0)
        {
          writeVariableValue("O_8_i03", 0); /* cilinder 4 navzgor - sprostitev */
          cylCond = 1;
        }
        printf("step:%d, I_11:%d, I_12:%d\n", step, readVariableValue("I_11_i03"), readVariableValue("I_12_i03"));
      }
      while(!cylCond);


      do
      {
        cylCond = 1;
        if(readVariableValue("I_9_i03") == 1 && readVariableValue("I_10_i03") == 0)
        {
          writeVariableValue("O_7_i03", 0); /* cilinder 3 navzgor - dviganje celjusti*/
          cylCond= 1;
        }
        printf("step:%d, I_9:%d, I_10:%d\n", step, readVariableValue("I_9_i03"), readVariableValue("I_10_i03"));
      }
      while(!cylCond);
      step = 13;
      break;
    
    case 13:  /* preverim ali je pomik izveden */
      printf("STEP: %d\n", step);
      printf("preverim ali je pomik izveden I_11:%d I_12:%d\n", readVariableValue("I_11"), readVariableValue("I_12"));
      
      if(readVariableValue("I_12") && readVariableValue("I_11"))
      {
        do
        {
          cylCond = 0;
          if(readVariableValue("I_3_i03") == 0 && readVariableValue("I_4_i03") == 1)
          {
            writeVariableValue("O_5_i03", 0);
            cylCond = 1;
          }
          printf("step:%d, I_3:%d, I_4:%d\n", step, readVariableValue("I_3_i03"), readVariableValue("I_4_i03"));
        } 
        while(!cylCond);
        step = 14;
      }
      break;

    case 14: /* miza - pomik za eno dozo */
      printf("STEP: %d\n", step);
      printf("pomik za eno dozo\n");
  
      writeVariableValue("O_7", 1);
      usleep(delay_time);
      writeVariableValue("O_7", 0);
      writeVariableValue("O_1_i04", 1);
      usleep(100000);
      writeVariableValue("O_1_i04", 0);

      step = 15;
      break;

    case 15: /* preverim ali je bil premik izveden */
      printf("STEP: %d\n", step);
      printf("preverim ali je premik izveden I_13:%d\n", readVariableValue("I_13"));
      if(readVariableValue("I_13"))
      {
        do
	{
	  cylCond = 0;  
	  if(readVariableValue("I_9_i03") == 0 && readVariableValue("I_10_i03") == 1)
	  {
	    writeVariableValue("O_7_i03", 1); /* cilinder 3 - potisne celjust navzdol */
	    cylCond = 1;
	  }
          printf("step:%d, I_9:%d, I_10:%d\n", step, readVariableValue("I_9_i03"), readVariableValue("I_10_i03"));
	}
	while(!cylCond);
        step = 9;
      }
      break;
  }
}

void sendModbus(int socket_fd, char *send_buff, int send_buff_size, char *receive_buff, int receive_buff_size, char *print_text)
{
  send(socket_fd, send_buff, send_buff_size, 0);
  printf("%s\n", print_text);
  recv(socket_fd, receive_buff, receive_buff_size , 0);
  transId++;
}


void timers() /* CASOVNI ZAMIK */
{
  clock_gettime(CLOCK_REALTIME, &stop1);
  target1 = ( stop1.tv_sec - start1.tv_sec ) + ( stop1.tv_nsec - start1.tv_nsec ) / MILLION;
  
  if(elapsedTime1 >= 30)
  {
    writeVariableValue("O_1_i03", 0);
    timer1 = 0;
  }
}




void detectFall(const char *var)
{
  int currentValue;
  int oldValue;
  currentValue = 1;
  oldValue = 1;
  fallDetected = 0;
  currentValue = readVariableValue(var);
  
  if(currentValue != oldValue)
  {
    if(currentValue == 0)
    {
      fallDetected = 1;
    } 
    else
    {
      fallDetected = 0;
    }
    oldValue = currentValue; 
  }
}

void detectRise(const char *var)
{
  int currentValue;
  int oldValue;
  currentValue = 0;
  oldValue = 0;
  riseDetected = 0;
  currentValue = readVariableValue(var);
  if(currentValue != oldValue)
  {
    if(currentValue == 1)
    {
      riseDetected = 1;
    }
    else
    {
      riseDetected = 0;
    }
    oldValue = currentValue;  
  }
}


/*
void toggleOutput(const char *output, int delay)
{
  writeVariableValue("%s\n", output
}
*/

/*
void timer(float measure)  CASOVNI ZAMIK 
{
  struct timespec start, stop;
  double accum;
    
  clock_gettime(CLOCK_REALTIME, &start);    
  while(accum < measure)
  {
    clock_gettime(CLOCK_REALTIME, &stop);

    accum = ( stop.tv_sec - start.tv_sec )
     + ( stop.tv_nsec - start.tv_nsec )
     / BILLION;
  }
}
*/
