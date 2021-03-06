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
void moveAKD(const char* akd);
void error(const char *msg)
{
  perror(msg);
}
/*PROGRAM*/
int main()
{
  initVars();
  initMain();

  initServer();
  while(conn_AKD != 0)
  {
    initCommAKDPress();
    sleep(1);
  }
  
  usleep(10000000);


  while(program == 1)
  {
    printf("*************************************\n");
    printf("Step:%d\n", step);
    printf("ErrorNum:%d\n", errorNum);
    checkTableClear();
    checkStartStop();
    checkInCycle();  

    receiveMessage();
    sendMessage();
    resetSafetyDoor();
    resetStopTotal(); 
    doorLock();
    prepareSteps();
    if(pressing)
    {
      if(doMeasurement)
      {
	coreLoop();
      }
      else
      {
	coreLoop2();
      }
    }
    else
    {
      noPress();
    }
    checkOutputs();
    resetPower();
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
  if(listen(sockfd,5) < 0)
  {
    error("listen error\n");
  }
  
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
  printf("s before socket:%d\n", s);
  ip_adrs = "192.168.1.13";
  if((s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))<0)
  {
    error("s socket error\n");
  }
  printf("s after socket:%d\n", s);
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
  int * sendMessagePtr85 = (int*)(&sendMessageBuff[85]);
  int * sendMessagePtr86 = (int*)(&sendMessageBuff[86]);
  int * sendMessagePtr87 = (int*)(&sendMessageBuff[87]);



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
  * sendMessagePtr85 = errorNum;
  * sendMessagePtr86 = tableClear;
  * sendMessagePtr87 = w;


 /*//FD_ZERO(&fdsTCP);
  //tv.tv_sec = 0;
  //tv.tv_usec = 0;

  //n = select(32, NULL, &fdsTCP, NULL, &tv); */
  //for(i = 0; i < 86; i++)
  //{
  //  printf("sendMessageBuff[%d]:%d\n", i, sendMessageBuff[i]);
 /// }
 
  n = send(newsockfd, sendMessageBuff, 88, 0);
  memset(sendMessageBuff, 0, 88);
}

void receiveMessage()
{
  //int i;
  struct timeval timeout;
  lastState = currentState;
  lastOutput = currentOutput;
  timeout.tv_sec = 5;
  timeout.tv_usec = 0;
  FD_ZERO(&fdsTCP);
  FD_SET(newsockfd, &fdsTCP);
  select(newsockfd+1, &fdsTCP, NULL, NULL, &timeout);  
  if(FD_ISSET(newsockfd, &fdsTCP))
  {
    recv(newsockfd, receiveMessageBuff, 10, 0);
    currentState = receiveMessageBuff[1];
    currentOutput = receiveMessageBuff[0];
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
        else if(lastState == currentState && lastOutput != currentOutput)
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
      step = -2;
    }
    press = receiveMessageBuff[5];
    selectedCan = receiveMessageBuff[6];
    pageNum = receiveMessageBuff[7];
    doMeasurement = receiveMessageBuff[8];
    pressing = receiveMessageBuff[9];
    /*
    for(i = 0; i < 8; i++)
    {
      printf("receiveMessageBuff[%d]:%d\n", i, receiveMessageBuff[i]);
    }*/
  }
  else
  {
    printf("\t TIMEOUT \n");
  }
}

void sendModbus(int socket_fd, char *send_buff, int send_buff_size, char *receive_buff, int receive_buff_size, char *print_text)
{
  send(socket_fd, send_buff, send_buff_size, 0);
  printf("%s\n", print_text);
  
  if(recv(socket_fd, receive_buff, receive_buff_size , 0) == -1)
  {
    error("receive modbus message\n");
  }
  transId++;
}


void timers() /* CASOVNI ZAMIK */
{
  clock_gettime(CLOCK_REALTIME, &stop1);
  target1 = ( stop1.tv_sec - start1.tv_sec ) + ( stop1.tv_nsec - start1.tv_nsec ) / THOUSAND;
  
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


int checkCylinder(const char* input1, int input1_val, const char* input2, int input2_val, int nextStep)
{
  printf("check Cylinder\n");
  printf("step:%d, %s:%d %s:%d\n", step, input1, readVariableValue(input1), input2, readVariableValue(input2));
  if(readVariableValue(input1) == input1_val && readVariableValue(input2) == input2_val)
  {
    return nextStep;
  }
  else
  {
    return 0;
  }
}

void preCheckCylinder(const char *input1, int input1_val, const char* input2, int input2_val, const char* output, int output_val)
{
  int cylCond = 0;
  do
  {
    cylCond = 0;
    if(readVariableValue(input1) == input1_val && readVariableValue(input2) == input2_val)
    {    
      writeVariableValue(output, output_val);    
      cylCond = 1;
    }
    printf("step:%d, %s:%d, %s:%d\n", step, input1, readVariableValue(input1), input2, readVariableValue(input2));
  }
  while(!cylCond);
}  

int moveCylinder(int id, const char *input1, int input1_val, const char* input2, int input2_val, const char* output, int output_val, int nextStep)
{
  struct timespec start1, stop1;
  double elapsedTime1;  
  int inWhile1 = 0;
  struct timespec start2, stop2;
  double elapsedTime2;  
  int inWhile2 = 0;
    
  while(!(readVariableValue(input1) == input1_val && readVariableValue(input2) == input2_val))
  {
    printf("precheck Cylinder\n");
    printf("step:%d, %s:%d %s:%d\n", step, input1, readVariableValue(input1), input2, readVariableValue(input2));
    
    if(!inWhile1)
    {  
      clock_gettime(CLOCK_REALTIME, &start1);
      inWhile1 = 1;
    }
    clock_gettime(CLOCK_REALTIME, &stop1);
    elapsedTime1 = ( stop1.tv_sec - start1.tv_sec );
    
    if(elapsedTime1 > 1)
    {
      step = -2;
      switch(id)
      {
        case 1:
          errorNum = 1;
          break;
        case 2:
          errorNum = 3;
          break;
        case 3: 
          errorNum = 5; 
          break;
        case 4:
          errorNum = 7;
          break;
      }
      return step;  
    }
    printf("elapsedTime:%f\n", elapsedTime1);
  }
  writeVariableValue(output, output_val); 
  printf("check Cylinder\n");
  printf("step:%d, %s:%d %s:%d\n", step, input1, readVariableValue(input1), input2, readVariableValue(input2));
 
  while(readVariableValue(input1) != abs(input1_val*(-1)) && readVariableValue(input2) != abs(input2_val*(-1)))
  {    
    if(!inWhile2)
    {  
      clock_gettime(CLOCK_REALTIME, &start2);
      inWhile2 = 1;
    }
    clock_gettime(CLOCK_REALTIME, &stop2);
    elapsedTime2 = ( stop2.tv_sec - start2.tv_sec );
    if(elapsedTime2 > 1)
    { 
      switch(id)
      {
        case 1:
          errorNum = 2;
          break;
        case 2:
          errorNum = 4;
          break;
        case 3: 
          errorNum = 6; 
          break;
        case 4:
          errorNum = 8;
          break;
      }
      step = -2;
      printf("Error step:%d, %s:%d %s:%d\n", step, input1, readVariableValue(input1), input2, readVariableValue(input2));
      return step;  
    }
    printf("elapsedTime:%f\n", elapsedTime2);
  }
  return nextStep;
}

void downPosPrep()
{
  writeVariableValue("O_11", 0);
  writeVariableValue("O_12", 0);
  writeVariableValue("O_13", 0);
  writeVariableValue("O_14", 0);
  /* priprava izhodov za pomik v spodnjo pozicijo */   
  if(selectedCan == 0) /* 2 */
  {
    writeVariableValue("O_12", 1);
  }
  else if(selectedCan == 1) /* 4 */
  {
    writeVariableValue("O_13", 1);
  }
  else if(selectedCan == 2) /* 6 */
  {
    writeVariableValue("O_12", 1);
    writeVariableValue("O_13", 1);
  }
  else if(selectedCan == 3) /* 8 */
  {
    writeVariableValue("O_14", 1);
  }
  else if(selectedCan == 4) /* 10 */
  {
    writeVariableValue("O_14", 1);
    writeVariableValue("O_12", 1);
  }
}

void upPosPrep()
{
  writeVariableValue("O_11", 0);
  writeVariableValue("O_12", 0);
  writeVariableValue("O_13", 0);
  writeVariableValue("O_14", 0);
  /* priprava izhodov za pomik na zgornjo pozicijo */  
  if(selectedCan == 0) /* 1 */
  {
    writeVariableValue("O_11", 1);
  }
  else if(selectedCan == 1) /* 3 */
  {
    writeVariableValue("O_11", 1);
    writeVariableValue("O_12", 1);
  }
  else if(selectedCan == 2) /* 5 */
  {
    writeVariableValue("O_11", 1);
    writeVariableValue("O_13", 1);
  }
  else if(selectedCan == 3) /* 7 */
  {
    writeVariableValue("O_11", 1);
    writeVariableValue("O_12", 1);
    writeVariableValue("O_13", 1);
  } 
  else if(selectedCan == 4) /* 9 */
  {
    writeVariableValue("O_11", 1);
    writeVariableValue("O_14", 1);
  }
} 

void coreLoop()
{
  switch(step)
  {
    case 1: /* prepare drive for measurement step */
      moveUpper();
      setup();
      step = 2;
      break;

    case 2: /* letting in cans */
      writeVariableValue("O_12_i03", 0);
      conveyorBelt();
      usleep(1000000);
      step = checkCanSize(3);
      if(step != 99)
      {
        ;
      }
      else
      {
        if(step != -2)
        {
          step = 2;
        }
      }
      break;
    
    case 3:
      turnTable();
      if(turnTableDone)
      {
        if(readVariableValue("I_2_i04"))
        {
          step = 4;
        }
      }   
      break;
  
    case 4: /* gripper - moving to low position */
      conveyorBelt();
      moveGripperLower();
      blockTable();
      
      if(moveGripperLowerDone && blockTableDone)
      {
        blockTableDone = 0;
        step = 5;
      }
      break;
  
    case 5: /* measuring position & updating drive data */
      conveyorBelt();
      usleep(1000000);
      step = moveCylinder(3, "I_11_i03", 0, "I_12_i03", 1,  "O_8_i03", 1, 6);      
      break;
    
    case 6:  /* press - moving to low position */  
      conveyorBelt();
      usleep(1000000);
      moveAKD("O_10");
      while(!readVariableValue("I_11") && !readVariableValue("I_13_i03"))
      {
        ;
      }
      if(readVariableValue("I_13_i03"))
      {
        movePressLowerDone = 0;
        movePressLowerStep = 0;
        step = 7;
      }
      else
      { 
        step  = moveCylinder(3, "I_11_i03", 0, "I_12_i03", 1,  "O_8_i03", 1, -2);
        usleep(400000);
        step = moveCylinder(3, "I_11_i03", 1, "I_12_i03", 0, "O_8_i03", 0, -2);
        errorNum = 20;
      }
      break;

    case 7: /* pressing cap */
      measurement();
      conveyorBelt();
      usleep(1000000);
      movePressLower(); 
      if(movePressLowerDone)
      {
        step = moveCylinder(3, "I_11_i03", 1, "I_12_i03", 0, "O_8_i03", 0, 8);
      }
      break;

    case 8: /* press - moving to up position */
      conveyorBelt();
      usleep(1000000);
      movePressUpper(); 
      if(movePressUpperDone)
      {
        step = 9;
      }
      break;

    case 9: /* gripper - moving to up position */
      conveyorBelt();
      moveGripperUpper();
      unblockTable();
      if(moveGripperUpperDone && unblockTableDone)
      {
        unblockTableDone = 0;
        step = 10;
      }
      break;

    case 10: /* reseting values - pressing loop */
      turnTableDone = 0;
      moveGripperLowerDone = 0;
      moveGripperUpperDone = 0;
      movePressLowerDone = 0;
      movePressUpperDone = 0;
      movePressMiddleDone = 0;
      //conveyorOff = 0;
      //conveyorOn = 0;
      conveyorBelt();
      pickCap();
      if(pickCapDone)
      {
        step = 11;
      }
      break;

    case 11:
      conveyorBelt();
      step = checkCanSize(12);
      if(step != 99)
      {  
        ;
      }   
      else
      {
        if(step != -2)
        {
          step = 11;
        }
      }
      break;

    case 12: /* turn table */
      conveyorBelt();
      turnTable();
      if(turnTableDone)
      {
        if(readVariableValue("I_2_i04"))
        {
          pickCapDone = 0;
          step = 13;
        }
        else
        {
         pickCapDone = 0;
         step = 10;
        }
      }
      break;

    case 13: /* gripper - moving to low position && blocking table */
      conveyorBelt();
      pickCap();
      moveGripperLower();
      blockTable();
      
      if(moveGripperLowerDone && blockTableDone)
      {
        blockTableDone = 0;
        step = 14;
      }
      break;

    case 14: /* press - moving to middle position - checking if cap present */
      conveyorBelt();
      pickCap();
      movePressMiddle();
      if(movePressMiddleDone)
      {
        step = 15;
      }
      break;

    case 15: /* if cap present - release cap and start press measurement */
      conveyorBelt();
      pickCap();
      if(readVariableValue("I_13_i03"))
      { 
        step = moveCylinder(3, "I_11_i03", 0, "I_12_i03", 1,  "O_8_i03", 1, 16);  
        writeVariableValue("O_1", 1);
      }
      else
      {
        alarmReset = 0;
        releaseCap(15);
        if(readVariableValue("I_1_i03"))
        {
          step = 18;
          releaseCapDone = 0;
        }
        errorNum = 20;
      }
      break;

    case 16: /* press - moving to low position - pressing cap*/
      if(!alarmReset)
      {
        errorNum = 0;
        alarmReset = 1; 
      }
      conveyorBelt();
      pickCap();
      movePressLower();
      if(movePressLowerDone)
      {
        step = 17;
      } 
      break;
    
    case 17: /* cap release cylinder to initial position*/
      conveyorBelt();
      pickCap();
      step = moveCylinder(3, "I_11_i03", 1, "I_12_i03", 0, "O_8_i03", 0, 18);
      break;
   
    case 18: /* press - moving to up position && stopping press measurement*/
      conveyorBelt();
      pickCap();
      movePressUpper(); 
      if(movePressUpperDone)
      {
        writeVariableValue("O_1", 0);
        writeVariableValue("O_2", 1);
        step = 19;
      }      
      break;

    case 19: /* gripper - moving to up position && unblocking table*/
      conveyorBelt();
      pickCap();
      moveGripperUpper();
      unblockTable();
      if(moveGripperUpperDone && unblockTableDone)
      {
        unblockTableDone = 0;
        writeVariableValue("O_2", 0);
        step = 10;
      }
      break;
  }
}

void turnTable()
{
  int cond1 = 0;
  int cond2 = 0;
  int cond3 = 0;
  printf("turnTableStep:%d, turnTableDone:%d\n", turnTableStep, turnTableDone);
  if(!turnTableDone)
  { 
    switch(turnTableStep)
    {
      case 0:
	if(readVariableValue("I_4_i04"))
        {
	  cond1 = checkCylinder("I_11_i03", 0, "I_12_i03", 1, 1);
	  cond2 = checkCylinder("I_9_i03", 0, "I_10_i03", 1, 1);
          cond3 = checkCylinder("I_11_i04", 0, "I_12_i04", 1, 1);
          printf("cond1:%d\n", cond1);
          printf("cond2:%d\n", cond1);
          printf("cond3:%d\n", cond1);
	
  	  if(cond1 && cond2 && cond3)
	  {
	    moveAKD("O_7");
	    turnTableStep = 1;
	  }
	  else
	  {
	    printf("cilinder ovira premik mize\n");
	  }
        }
	break;

      case 1:
	printf("case 1\n");
        if(readVariableValue("I_13"))
	{
	  printf("move completed\n");
          turnTableDone = 1;
          turnTableStep = 0;
	}
	break;
    }
  }
}


void turnTableFree()
{
  int cond1 = 0;
  int cond2 = 0;
  int cond3 = 0;
  printf("turnTableFreeStep:%d, turnTableFreeDone:%d\n", turnTableStep, turnTableDone);
  if(!turnTableDone)
  { 
    switch(turnTableStep)
    {
      case 0:
	cond1 = checkCylinder("I_11_i03", 0, "I_12_i03", 1, 1);
	cond2 = checkCylinder("I_9_i03", 0, "I_10_i03", 1, 1);
        cond3 = checkCylinder("I_11_i04", 0, "I_12_i04", 1, 1);
        printf("cond1:%d\n", cond1);
        printf("cond2:%d\n", cond2);
        printf("cond3:%d\n", cond3);
	
        if(cond1 && cond2 && cond3)
	{
	  moveAKD("O_7");
	  turnTableStep = 1;
	}
	else
	{
	  printf("cilinder ovira premik mize\n");
	}
	break;

      case 1:
	printf("case 1\n");
        if(readVariableValue("I_13"))
	{
	  printf("move completed\n");
          turnTableDone = 1;
          turnTableStep = 0;
	}
	break;
    }
  }
}


void noPress()
{
  switch(step)
  {
    case 1:
      writeVariableValue("O_12_i03", 0);
      moveMaxUpper();
      step = 2;
      break;

    case 2:
      turnTable();
      if(turnTableDone)
      {
        turnTableDone = 0;
        step = 2;
      }
      break;
  }
}

void movePressLower()
{
  printf("movePressLowerStep:%d, movePressLowerDone:%d\n", movePressLowerStep, movePressLowerDone);
  if(!movePressLowerDone)
  {
    switch(movePressLowerStep)
    {
      case 0:
	moveAKD("O_10");
	movePressLowerStep = 1;
        break;

      case 1:
	if(readVariableValue("I_11"))
	{
	  movePressLowerDone = 1;
	  movePressLowerStep = 0;
	}
	break;
    }
  }
}

void movePressUpper()
{
  printf("movePressUpperStep:%d, movePressUpperDone:%d\n", movePressUpperStep, movePressUpperDone);
  if(!movePressUpperDone)
  {
    switch(movePressUpperStep)
    {
      case 0:
	moveAKD("O_9");
	movePressUpperStep = 1;
        break;

      case 1:
	if(readVariableValue("I_11"))
	{
	  movePressUpperDone = 1;
	  movePressUpperStep = 0;
	}
	break;
    }
  }
}

void movePressMiddle()
{
  printf("movePressMiddleStep:%d, movePressMiddleDone:%d\n", movePressMiddleStep, movePressMiddleDone);
  if(!movePressMiddleDone)
  {
    switch(movePressMiddleStep)
    {
      case 0:
	moveAKD("O_14_i03");
	movePressMiddleStep = 1;
        break;
    
      case 1:
	if(readVariableValue("I_11"))
	{
	  movePressMiddleDone = 1;
	  movePressMiddleStep = 0;
	}
	break;
    }
  }
}

void moveGripperLower()
{
  printf("moveGripperLowerStep:%d, moveGripperLowerDone:%d\n", moveGripperLowerStep, moveGripperLowerDone);
  if(!moveGripperLowerDone)
  {
    switch(moveGripperLowerStep)
    {
      case 0:
	downPosPrep();
	usleep(delay_time);
	moveAKD("O_1_i03");
	moveGripperLowerStep = 1;
        break;

      case 1:
	if(readVariableValue("I_12"))
	{
	  moveGripperLowerDone = 1;
	  moveGripperLowerStep = 0;
	}
        break;
    }
  }
}

void moveGripperUpper()
{
  printf("moveGripperUpperStep:%d, moveGripperUpperDone:%d\n", moveGripperUpperStep, moveGripperUpperDone);
  if(!moveGripperUpperDone)
  {
    switch(moveGripperUpperStep)
    {
      case 0:
	upPosPrep();
	usleep(delay_time);
	moveAKD("O_1_i03");
	moveGripperUpperStep = 1;
        break;    
       
      case 1:
	if(readVariableValue("I_12"))
	{
	  moveGripperUpperDone = 1;
	  moveGripperUpperStep = 0;
	}
        break;
    }
  }
}

void pickCap()
{
  printf("pickCapStep:%d, pickCapDone:%d\n", pickCapStep, pickCapDone);
  if(!pickCapDone)
  {
    switch(pickCapStep)
    {
      case 0:
        if(!readVariableValue("I_14_i03"))
        {
          if(readVariableValue("I_1_i04") && readVariableValue("I_3_i04"))
          {
            pickCapStep = moveCylinder(2, "I_9_i03", 0, "I_10_i03", 1, "O_7_i03", 1, 1);
          }
          else if(readVariableValue("I_1_i04") && !readVariableValue("I_3_i04"))
          {
            writeVariableValue("O_9_i03", 1);
            usleep(200000);
            writeVariableValue("O_9_i03", 0);
            pickCapStep = 0;
          }
        }
        else
        {
          pickCapStep = 6;
        }
        break;
      
      case 1:
        if(readVariableValue("I_1_i04") && readVariableValue("I_3_i04"))
        {
          usleep(200000);
          pickCapStep = moveCylinder(1, "I_3_i03", 1, "I_4_i03", 0, "O_5_i03", 1, 2);
        }
        break;

      case 2:
        if(!readVariableValue("I_13_i04"))
        {
          pickCapStep = 3;
        }
        else
        {
          step = -2;
          errorNum = 19;
        }
        break;

      case 3:
        usleep(400000);
        pickCapStep = moveCylinder(2, "I_9_i03", 1, "I_10_i03", 0, "O_7_i03", 0, 4);
        break;

      case 4:
        //if(!readVariableValue("I_3_i04"))
        //{
          pickCapStep = 5;
        //}   
        //else
        //{
        //  errorNum = 18;
        //}
        break;

      case 5:
        pickCapStep = moveCylinder(1, "I_3_i03", 0, "I_4_i03", 1, "O_5_i03", 0, 6);
        break;

      case 6:
        pickCapStep = 0; 
        pickCapDone = 1;
        break;

    }
  }
}


void conveyorBelt()
{
  printf("conveyorOff:%d\n", conveyorOff);
  printf("conveyorOn:%d\n", conveyorOn);
  if(readVariableValue("I_1_i04"))
  {
    if(!conveyorOff) 
    {
      writeVariableValue("O_2_i03", 0);
      conveyorOff = 1;
      conveyorOn = 0;
    }
  }
  else
  {
    if(!conveyorOn)
    {
      writeVariableValue("O_2_i03", 1);
      conveyorOn = 1;
      conveyorOff = 0;
    }
  }
}

void moveAKD(const char* akd)
{
  writeVariableValue(akd, 1);
  usleep(delay_time);
  writeVariableValue(akd, 0);
}


void measurement()
{
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
  printf("STEP: %d\n", step);
  printf("preberem podatek o trenutni poziciji in ga shranim v ustrezne motion taske");
  
  memset(readBuff, 0, 12);
  * read2 = htons(0);
  * read3 = htons(6);
  * read4 = 1;
  * read5 = 3;
  * read6 = htons(2072);
  * read7 = htons(2);
  * writePosTen9 = 11;       
  * read1 = transId;   
  sendModbus(s, readBuff, 12, readBuff_recv, 50, "read feedback position");
  
  w = ((readBuff_recv[10]<<16) + (readBuff_recv[11]<<8) + readBuff_recv[12]);     
  * writePosTen10 = htonl(w);
  printf("POSITION FEEDBACK:%d\n", w);
 
  * writePosTen1 = transId;       
  sendModbus(s, writePosTenBuff, 53, writePosTenBuff_recv, 50, "position 11 parameter");

  if(selectedCan == 0)  
  {
    * writePosDown9 = 2;    
  }
  else if(selectedCan == 1)
  {
    * writePosDown9 = 4;    
  }
  else if(selectedCan == 2)
  {
    * writePosDown9 = 6;       
  }
  else if(selectedCan == 3)
  {
    * writePosDown9 = 8;       
  }
  else if(selectedCan == 4)
  {
    * writePosDown9 = 10;       
  }
  * writePosDown10 = htonl(w + press*1000);
  * writePosDown1 = transId;       
  * writePosDown11 = htonl(2000000); 
 
  sendModbus(s, writePosDownBuff, 53, writePosDownBuff_recv, 50, "position 11 parameter");

  * dinModeChange1 = transId;
  * dinModeChange9 = htonl(0);
  sendModbus(s, obufDMC, 17, ibufDMC, 50, "save to drive");
  
  * drvSave1 = transId;
  sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive");
}


void setup()
{
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
  printf("SETUP - STEP: %d\n", step);
  
  * moveTask1 = transId;
  if(selectedCan == 0)
  {
    * moveTask9 = htonl(1000);                
    * moveTask9Next = htonl(2000);
    * writePosUp9 = 1;       
    * writePosUp10 = htonl((0)*1000); 
    * writePosDown9 = 2;       
    * writePosDown10 = htonl((0)*1000); 
  }
  else if(selectedCan == 1)
  {
    * moveTask9 = htonl(3000);
    * moveTask9Next = htonl(4000);
    * writePosUp9 = 3;       
    * writePosUp10 = htonl((138)*1000); 
    * writePosDown9 = 4;       
    * writePosDown10 = htonl((173)*1000); 
  }
  else if(selectedCan == 2)
  {
    * moveTask9 = htonl(5000);
    * moveTask9Next = htonl(6000);     
    * writePosUp9 = 5;       
    * writePosUp10 = htonl((104)*1000); 
    * writePosDown9 = 6;       
    * writePosDown10 = htonl((135)*1000); 
  }
  else if(selectedCan == 3)
  {
    * moveTask9 = htonl(7000);
    * moveTask9Next = htonl(8000); 
    * writePosUp9 = 7;       
    * writePosUp10 = htonl((60)*1000);
    * writePosDown9 = 8;       
    * writePosDown10 = htonl((90)*1000);
  }
  else if(selectedCan == 4)
  {
    * moveTask9 = htonl(9000);
    * moveTask9Next = htonl(10000); 
    * writePosUp9 = 9;       
    * writePosUp10 = htonl((-2)*1000);
    * writePosDown9 = 10;       
    * writePosDown10 = htonl((33)*1000);
  }

  sendModbus(s, obufMT, 17, ibufMT, 50, "move task 1 - revert to original positions");
  * moveTask1Next = transId;
  sendModbus(s, obufMTN, 17, ibufMTN, 50, "move task 2 - revert to original positions");

  * writePosUp1 = transId;       
  sendModbus(s, writePosUpBuff, 53, writePosUpBuff_recv, 50, "template position parameter saved");
  * writePosDown1 = transId;       
  * writePosDown11 = htonl(100000);   
  sendModbus(s, writePosDownBuff, 53, writePosDownBuff_recv, 50, "template position parameter saved");

   * dinModeChange1 = transId;
   * dinModeChange9 = htonl(15);
  sendModbus(s, obufDMC, 17, ibufDMC, 50, "save to drive");

  * drvSave1 = transId;
  sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive");
  
}

void checkOutputs()
{
  if(inCycle)
  {
    if(readVariableValue("Output_Status") != 0)
    {
      printf("ODPRTA VRATA\n");
      step = -2;
      if(step != -2)
      {
	errorNum = 15;
      }
    }
    if(readVariableValue("Output_Status_i04") != 0)
    {
      if(step != 0 && step !=-2)
      { 
	step = -2;
	errorNum = 16; 
      }
    }
    if(readVariableValue("I_14") == 0)
    {
      step = -2;
      errorNum = 17;
    }
    if(!readVariableValue("I_10"))
    {
      step = -2;
      errorNum = 25;
    }
  }
}


void blockTable()
{
  printf("blockTableStep:%d, blockTableDone:%d\n", blockTableStep, blockTableDone);
  if(!blockTableDone)
  {
    switch(blockTableStep) 
    { 
      case 0:
        blockTableStep = moveCylinder(4, "I_11_i04", 0, "I_12_i04", 1,  "O_11_i03", 1, 1);
        break;

      case 1:
        blockTableStep = 0;
        blockTableDone = 1;        
        break;
    }
  }
}


void unblockTable()
{
  printf("unblockTableStep:%d, unblockTableDone:%d\n", unblockTableStep, unblockTableDone);
  if(!unblockTableDone)
  {
    switch(unblockTableStep) 
    { 
      case 0:
        unblockTableStep = moveCylinder(4, "I_11_i04", 1, "I_12_i04", 0,  "O_11_i03", 0, 1);
        break;
 
      case 1:
        unblockTableStep = 0;
        unblockTableDone = 1;        
        break;
    }
  }
}

void clearTable()
{
  switch(clearTableStep)
  {
    case 0:
      conveyorBelt();
      turnTableStep = 0;
      turnTableDone = 0;
      moveGripperLowerStep = 0;
      moveGripperLowerDone = 0;
      moveGripperUpperStep = 0;
      moveGripperUpperDone = 0;
      movePressLowerStep = 0;
      movePressLowerDone = 0;
      movePressUpperStep = 0;
      movePressUpperDone = 0;
      movePressMiddleStep = 0;
      movePressMiddleDone = 0;
      pickCapStep = 0;
      pickCapDone = 0;
      blockTableStep = 0;
      blockTableDone = 0;
      unblockTableStep = 0;
      unblockTableDone = 0;
      if(readVariableValue("I_8_i04"))
      {
	clearTableDone = 0;
      }
      if(!clearTableDone)
      {
	clearTableStep = 1;
      }
      break;

    case 1:
      conveyorBelt();
      turnTableFree();
      if(turnTableDone)
      {
	turnTableDone = 0;
	clearTableStep = 2;
      }  
      break;

    case 2:
      conveyorBelt();
      pickCap();
      if(pickCapDone)
      {
	clearTableStep = 3;
	pickCapDone = 0;
      }
      break;
    
    case 3:
      conveyorBelt();
      if(readVariableValue("I_2_i04"))
      {  
	moveGripperLower();
	blockTable();
	if(moveGripperLowerDone && blockTableDone)
	{
	  blockTableDone = 0;
	  clearTableStep = 4;
	}
      }
      else
      {
	clearTableStep = 0;
        clearTableDone = 1;
      }
      break;

    case 4:
      conveyorBelt();
      movePressMiddle();
      if(movePressMiddleDone)
      {
	clearTableStep = 5;
	movePressMiddleDone = 0;
      }
      break;
    
    case 5:
      conveyorBelt();
      if(readVariableValue("I_13_i03"))
      { 
	clearTableStep = moveCylinder(3, "I_11_i03", 0, "I_12_i03", 1,  "O_8_i03", 1, 6);  
      }
      else
      {
	clearTableStep = 8;
      }
      break;

    case 6: /* press - moving to low position - pressing cap*/
      conveyorBelt();
      movePressLower();
      if(movePressLowerDone)
      {
	clearTableStep = 7;
      } 
      break;
    
    case 7: /* cap release cylinder to initial position*/
      conveyorBelt();
      clearTableStep = moveCylinder(3, "I_11_i03", 1, "I_12_i03", 0, "O_8_i03", 0, 8);
      break;
   
    case 8: /* press - moving to up position && stopping press measurement*/
      conveyorBelt();
      movePressUpper(); 
      if(movePressUpperDone)
      {
	clearTableStep = 9;
      }      
      break;

    case 9: /* gripper - moving to up position && unblocking table*/
      conveyorBelt();
      moveGripperUpper();
      unblockTable();
      if(moveGripperUpperDone && unblockTableDone)
      {
	unblockTableDone = 0;
	moveGripperUpperDone = 0;
	clearTableStep = 0;
	clearTableDone = 1;
      }
      break;
  }
}

void tableHome()
{
  int cond1 = 0;
  int cond2 = 0;
  int cond3 = 0;
  int cond4 = 0;
  if(readVariableValue("I_9_i04"))
  {
    cond1 = checkCylinder("I_11_i03", 0, "I_12_i03", 1, 1);
    cond2 = checkCylinder("I_9_i03", 0, "I_10_i03", 1, 1);
    cond3 = checkCylinder("I_11_i04", 0, "I_12_i04", 1, 1);
    if(!readVariableValue("I_2_i04") && !readVariableValue("I_4_i04"))
    {
      cond4 = 1;
    }

    if(cond1 && cond2 && cond3 && cond4)
    {
      writeVariableValue("O_8", 1);
      usleep(delay_time);
      writeVariableValue("O_8", 0);
      while(!readVariableValue("I_5_i04"))
      {
	;
      }
    }
  }
}

void tableHomeFree()
{
  int cond1 = 0;
  int cond2 = 0;
  int cond3 = 0;
  int cond4 = 0;
  cond1 = checkCylinder("I_11_i03", 0, "I_12_i03", 1, 1);
  cond2 = checkCylinder("I_9_i03", 0, "I_10_i03", 1, 1);
  cond3 = checkCylinder("I_11_i04", 0, "I_12_i04", 1, 1);
  if(!readVariableValue("I_2_i04") && !readVariableValue("I_4_i04"))
  {
    cond4 = 1;
  }

  if(cond1 && cond2 && cond3 && cond4)
  {
    writeVariableValue("O_8", 1);
    usleep(delay_time);
    writeVariableValue("O_8", 0);
    while(!readVariableValue("I_5_i04"))
    {
      ;
    }
  }
}


void doorLock()
{
  printf("doorLockOff:%d\n", doorLockOff);
  printf("doorLockOn:%d\n", doorLockOn);
  if(step == 0)
  {
    if(!doorLockOff) 
    {
      usleep(100000);      
      writeVariableValue("O_13_i03", 0);
      doorLockOff = 1;
      doorLockOn = 0;
    }
  }
  else
  {
    if(!doorLockOn)
    {
      writeVariableValue("O_13_i03", 1);
      doorLockOn = 1;
      doorLockOff = 0;
    }
  }
}

int checkCanSize(int nextStep)  
{  
  struct timespec start, stop;
  double elapsedTime;  
  int inWhile = 0;
  int cond = 0;

  printf("selectedCan:%d, I_4_i04:%d, i_6_i04:%d, i_7_i04:%d, i_14_i04:%d\n", selectedCan, readVariableValue("I_4_i04"), readVariableValue("I_6_i04"), readVariableValue("I_7_i04"), readVariableValue("I_14_i04"));
  if(readVariableValue("I_4_i04"))
  {
    switch(selectedCan)
    {
      case 0:
        return -2;

      case 1:
        if(!readVariableValue("I_6_i04") && !readVariableValue("I_7_i04") && !readVariableValue("I_14_i04"))
        {
          return nextStep;
        }
        else
        {
          errorNum = 23;
          return -2;
        }
        
      case 2:
        while(!cond)
        { 
          if(readVariableValue("I_14_i04"))
          {
            cond = 1;  
          }
          else
          {
            cond = 0;
          }
         
          if(!inWhile)
          {  
            clock_gettime(CLOCK_REALTIME, &start);
            inWhile = 1;
          }
  
          clock_gettime(CLOCK_REALTIME, &stop);
          elapsedTime = ( stop.tv_sec - start.tv_sec );

          if(readVariableValue("I_6_i04") || readVariableValue("I_7_i04"))
          {
            errorNum = 23;
            return -2;
          } 
          else if(elapsedTime > 1)
          {
            errorNum = 23;
            return -2;
          }
        }
        return nextStep;
        
        case 3:
          while(!cond)
          {
            if(readVariableValue("I_14_i04") && readVariableValue("I_7_i04"))
            {
              cond = 1;  
            }
            else
            {
              cond = 0;
            }
          
            if(!inWhile)
            {  
              clock_gettime(CLOCK_REALTIME, &start);
              inWhile = 1;
            }
  
            clock_gettime(CLOCK_REALTIME, &stop);
            elapsedTime = ( stop.tv_sec - start.tv_sec );

            if(readVariableValue("I_6_i04"))
            {
              errorNum = 23;
              return -2;
            } 
            else if(elapsedTime > 1)
            {
              errorNum = 23;
              return -2;
            }
          }
          return nextStep;
        
        case 4:
          while(!cond)
          {
            if(readVariableValue("I_14_i04") && readVariableValue("I_7_i04") && readVariableValue("I_6_i04"))
            {
              cond = 1;  
            }
            else
            {
              cond = 0;
            }
            printf("inWhile - selectedCan:%d, I_4_i04:%d, i_6_i04:%d, i_7_i04:%d, i_14_i04:%d\n", selectedCan, readVariableValue("I_4_i04"), readVariableValue("I_6_i04"), readVariableValue("I_7_i04"), readVariableValue("I_14_i04"));
            if(!inWhile)
            {  
              clock_gettime(CLOCK_REALTIME, &start);
              inWhile = 1;
            }
  
            clock_gettime(CLOCK_REALTIME, &stop);
            elapsedTime = ( stop.tv_sec - start.tv_sec );

            if(elapsedTime > 1)
            {
              errorNum = 23;
              return -2;
            }
          }
          return nextStep;
     
        default:
          return -2;
    }
  }
  else
  {
    return 99;
  }
}

void coreLoop2()
{
  printf("CORE LOOP2\n");
  switch(step)
  {
    case 1:
      if(readVariableValue("I_2_i04"))
      {
        moveUpper();
        step = 2;
      }
      step = 2;
      break;

    case 2: /* reseting values - pressing loop */
      turnTableDone = 0;
      moveGripperLowerDone = 0;
      moveGripperUpperDone = 0;
      movePressLowerDone = 0;
      movePressUpperDone = 0;
      movePressMiddleDone = 0;
      //conveyorOff = 0;
      //conveyorOn = 0;
      writeVariableValue("O_12_i03", 0);
      conveyorBelt();
      pickCap();
      if(pickCapDone)
      {
        step = 3;
      }
      break;

    case 3:
      conveyorBelt();
      step = checkCanSize(4);
      if(step != 99)
      {  
        ;
      }   
      else
      {
        if(step != -2)
        {
          step = 3;
        }
      }
      break;

    case 4: /* turn table */
      conveyorBelt();
      turnTable();
      if(turnTableDone)
      {
        if(readVariableValue("I_2_i04"))
        {
          pickCapDone = 0;
          step = 5;
        }
        else
        {
         pickCapDone = 0;
         step = 2;
        }
      }
      break;

    case 5: /* gripper - moving to low position && blocking table */
      conveyorBelt();
      pickCap();
      moveGripperLower();
      blockTable();
      
      if(moveGripperLowerDone && blockTableDone)
      {
        blockTableDone = 0;
        step = 6;
      }
      break;

    case 6: /* press - moving to middle position - checking if cap present */
      conveyorBelt();
      pickCap();
      movePressMiddle();
      if(movePressMiddleDone)
      {
        step = 7;
      }
      break;

    case 7: /* if cap present - release cap and start press measurement */
      conveyorBelt();
      pickCap();
      if(readVariableValue("I_13_i03"))
      { 
        step = moveCylinder(3, "I_11_i03", 0, "I_12_i03", 1,  "O_8_i03", 1, 8);  
        writeVariableValue("O_1", 1);
      }
      else
      {
        releaseCap(7);
        if(readVariableValue("I_1_i03"))
        {
          step = 10;
          releaseCapDone = 0;
        }
        errorNum = 20; 
      }
      break;

    case 8: /* press - moving to low position - pressing cap*/
      if(!alarmReset)
      {
        errorNum = 0;
        alarmReset = 1; 
      }
      conveyorBelt();
      pickCap();
      movePressLower();
      if(movePressLowerDone)
      {
        step = 9;
      } 
      break;
    
    case 9: /* cap release cylinder to initial position*/
      conveyorBelt();
      pickCap();
      step = moveCylinder(3, "I_11_i03", 1, "I_12_i03", 0, "O_8_i03", 0, 10);
      break;
   
    case 10: /* press - moving to up position && stopping press measurement*/
      conveyorBelt();
      pickCap();
      movePressUpper(); 
      if(movePressUpperDone)
      {
        writeVariableValue("O_1", 0);
        writeVariableValue("O_2", 1);
        step = 11;
      }      
      break;

    case 11: /* gripper - moving to up position && unblocking table*/
      conveyorBelt();
      pickCap();
      moveGripperUpper();
      unblockTable();
      if(moveGripperUpperDone && unblockTableDone)
      {
        unblockTableDone = 0;
        writeVariableValue("O_2", 0);
        step = 2;
      }
      break;
  }
}


void resetSafetyDoor()
{
  safetyDoorLastState = safetyDoorCurrentState;
  safetyDoorCurrentState = readVariableValue("Output_Status");

  if(safetyDoorLastState != safetyDoorCurrentState)
  {
    if(safetyDoorCurrentState == 0)
    {
      writeVariableValue("O_1_i04", 1);
      usleep(500000);
      writeVariableValue("O_1_i04", 0);
    }
  }
}

void resetStopTotal()
{
  stopTotalLastState = stopTotalCurrentState;
  stopTotalCurrentState = readVariableValue("Output_Status_i04");

  if(stopTotalLastState != stopTotalCurrentState)
  {
    if(stopTotalCurrentState == 0)
    {
      writeVariableValue("O_1_i04", 1);
      usleep(500000);
      writeVariableValue("O_1_i04", 0);
    }
  }
}

void resetPower()
{
  powerLastState = powerCurrentState;
  powerCurrentState = readVariableValue("I_9");

  if(powerLastState != powerCurrentState)
  {
    if(powerCurrentState == 1)
    {
      usleep(5000000);
      writeVariableValue("O_1_i04", 1);
      usleep(500000);
      writeVariableValue("O_1_i04", 0);
    }
  }
}


void prepareSteps()
{
  switch(step)
  {
    case -3:
      writeVariableValue("O_5_i03", 0);
      writeVariableValue("O_7_i03", 0); 
      writeVariableValue("O_8_i03", 0);
      writeVariableValue("O_2_i03", 0); 
      writeVariableValue("O_11_i03", 0);
      writeVariableValue("O_12_i03", 1);
      writeVariableValue("O_11", 0);
      writeVariableValue("O_12", 0);
      writeVariableValue("O_13", 0);
      writeVariableValue("O_14", 0);
	 
      if(readVariableValue("I_10")) /*ce je napaka je 0*/
      {
	moveAKD("O_4_i03");
	while(!readVariableValue("I_11"))
	 {
	   ;
	 }
	 usleep(1000000);
	 writeVariableValue("O_11", 1);
	 writeVariableValue("O_14", 1); 
	 usleep(1000000);
	 moveAKD("O_1_i03");
	 while(!readVariableValue("I_12"))
	 {
	   ;
	 }
	 tableHomeFree();
	 step = 0;
       }
       else
       {
	 errorNum = 24;
       }
       break;

    case -2: /* reset to zero */
      writeVariableValue("O_5_i03", 0);
      writeVariableValue("O_7_i03", 0); 
      writeVariableValue("O_8_i03", 0);
      writeVariableValue("O_2_i03", 0); 
      writeVariableValue("O_11_i03", 0);
      writeVariableValue("O_12_i03", 1);
      writeVariableValue("O_11", 0);
      writeVariableValue("O_12", 0);
      writeVariableValue("O_13", 0);
      writeVariableValue("O_14", 0);
      conveyorOff = 0;
      conveyorOn = 0;
      turnTableDone = 0;
      moveGripperLowerDone = 0;
      moveGripperUpperDone = 0;
      movePressLowerDone = 0;
      movePressUpperDone = 0;
      movePressMiddleDone = 0;
      pickCapDone = 0;
      moveGripperLowerStep = 0;
      moveGripperUpperStep = 0;
      movePressLowerStep = 0;
      movePressUpperStep = 0;
      movePressMiddleStep = 0;
      pickCapStep = 0;
      if(pressing)
      {
        moveUpper();
      }
      step = 0;
      break;

    case -1: /* reset to zero */
      writeVariableValue("O_5_i03", 0);
      writeVariableValue("O_7_i03", 0); 
      writeVariableValue("O_8_i03", 0);
      writeVariableValue("O_2_i03", 0); 
      writeVariableValue("O_11_i03", 0);
      writeVariableValue("O_12_i03", 1);
      writeVariableValue("O_11", 0);
      writeVariableValue("O_12", 0);
      writeVariableValue("O_13", 0);
      writeVariableValue("O_14", 0);
      conveyorOff = 0;
      conveyorOn = 0;
      turnTableDone = 0;
      moveGripperLowerDone = 0;
      moveGripperUpperDone = 0;
      movePressLowerDone = 0;
      movePressUpperDone = 0;
      movePressMiddleDone = 0;
      pickCapDone = 0;
      moveGripperLowerStep = 0;
      moveGripperUpperStep = 0;
      movePressLowerStep = 0;
      movePressUpperStep = 0;
      movePressMiddleStep = 0;
      pickCapStep = 0;
      step = 1;
      break;
      
    case 0: 
      errorNum = 0;
      tableHome();
      clearTable();
      //step = checkCanSize(0);
      break;
  }
}


void moveUpper()
{   
  writeVariableValue("O_11", 0);
  writeVariableValue("O_12", 0);
  writeVariableValue("O_13", 0);
  writeVariableValue("O_14", 0);
 
  moveAKD("O_4_i03");
  while(!readVariableValue("I_11"))
  {
    ;
  }
  writeVariableValue("O_11", 1);
  writeVariableValue("O_14", 1);
  usleep(1000000);
  moveAKD("O_1_i03");
  while(!readVariableValue("I_12"))
  {
    ;
  }
}

void moveMaxUpper()
{   
  writeVariableValue("O_11", 0);
  writeVariableValue("O_12", 0);
  writeVariableValue("O_13", 0);
  writeVariableValue("O_14", 0);
 
  moveAKD("O_4_i03");
  while(!readVariableValue("I_11"))
  {
    ;
  }
  writeVariableValue("O_13", 1);
  writeVariableValue("O_14", 1);
  usleep(1000000);
  moveAKD("O_1_i03");
  while(!readVariableValue("I_12"))
  {
    ;
  }
}

void checkStartStop()
{
  if(readVariableValue("I_1_i03") && !inCycle)
  {
    if(tableClear)
    {
      step = 1;
    }
    else
    {
      errorNum = 21;
    }
  }
  else if(readVariableValue("I_2_i03"))
  {
    step = -2;
  }
}


void checkInCycle()
{
  if(step <= 0 )
  {
    inCycle = 0;
  }
  else
  { 
    inCycle = 1;
  }
}

void initVars()
{
  alarmReset = 1;
  releaseCapDone = 0;
  w = 0;
  tableClear = 0;
  turnTableStep = 0;
  turnTableDone = 0;
  movePressZeroPosStep = 0;
  movePressZeroPosDone = 0;
  moveGripperLowerStep = 0;
  moveGripperLowerDone = 0;
  moveGripperUpperStep = 0;
  moveGripperUpperDone = 0;
  movePressLowerStep = 0;
  movePressLowerDone = 0;
  movePressUpperStep = 0;
  movePressUpperDone = 0;
  movePressMiddleStep = 0;
  movePressMiddleDone = 0;
  pickCapStep = 0;
  pickCapDone = 0;
  blockTableStep = 0;
  blockTableDone = 0;
  unblockTableStep = 0;
  unblockTableDone = 0;
  clearTableStep = 0;
  clearTableDone = 1;
  conveyorOff = 0;
  conveyorOn = 0;
  doorLockOff = 0;
  doorLockOn = 0;
  safetyDoorLastState = 0;
  safetyDoorCurrentState = 0;
  stopTotalLastState = 0;
  stopTotalCurrentState = 0;
  powerLastState = 0;
  powerCurrentState = 0;
  doMeasurement = 1;
  pressing = 1;
  s = -99;
  conn_AKD = 100;
  n = 0;
  pageNum = 2;
  program = 1;
  PiControlHandle_g = -1; 
  step = -3;
  memset(sendMessageBuff, 0, 86);
  lastState = 0;
  currentState = 0;
}
 
void checkTableClear()
{
  if(!readVariableValue("I_2_i04") && !readVariableValue("I_4_i04"))
  {
    tableClear = 1;
  }
  else
  {
    tableClear = 0;
  }
  printf("TABLE CLEAR:%d\n", tableClear);
}


void releaseCap(int nextStep)
{
  if(!releaseCapDone)
  {
    step  = moveCylinder(3, "I_11_i03", 0, "I_12_i03", 1,  "O_8_i03", 1, nextStep);
    usleep(400000);
    step = moveCylinder(3, "I_11_i03", 1, "I_12_i03", 0, "O_8_i03", 0, nextStep);
    releaseCapDone = 1;
  }
}
