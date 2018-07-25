#include <stdio.h>
#include "graphics_sdl.h"
#include "main.h"
#include <errno.h>
#include <unistd.h>
void initMain();
void initCommAKDPress();
void initCommTCP();
void readVarTCP();
void error(const char *msg);

int main()
{
  int cycle;
  printf("MAIN\n");
  /* initializing */
  initMain();
  init();

  /* connecting to DRIVEs */
  while(connectiOn == 0)
  {
    renderBackground();
    renderStatusBar();
    renderContent();
    SDL_RenderPresent(renderer);
    cycle++;
    initCommAKDPress();
    initCommTCP();
    touchUpdate();
  } 
  
  /* main program loop */
  while(program == 1)
  {
    touchUpdate();
    renderBackground();
    renderStatusBar();
    renderContent();
    SDL_RenderPresent(renderer);
    readVarTCP();
    cycle++;
    printf("s:%d m:%d b:%d\n", firstPosSmall, firstPosMedium, firstPosBig);
  }
  return 0;
}

void initCommAKDPress() 
{
  
  ip_adrs = "192.168.0.13";
  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  server.sin_family = AF_INET;
  server.sin_port = htons(502);
  server.sin_addr.s_addr = inet_addr(ip_adrs);
  printf("connecting to press drive\n");
  conn = connect(s, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
  if(conn == -1)
  {
    backgroundColor = 2;
    sbarText = 7; 
    page = 7;
    connectiOn = -1; 
  }
  else
  {
    connectiOn = 1; 
    page_stage[6] = 0;
    page = 0;
  }
  printf("%d\n", conn);
  sleep(3);
}

void initCommTCP()
{
  serv_addr.sin_addr.s_addr = inet_addr("192.168.0.12");
  serv_addr.sin_port = htons(PORTNO);
  serv_addr.sin_family = AF_INET;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
  {
    error("ERROR opening socket");
  }
 
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
  {   
    error("ERROR connecting");
    connectiOn = -2;
  }
  else
  {
    if(connectiOn == 1)
    {
      connectiOn = 1;
    }
  }
}

void readVarTCP()
{
  memset(sendBuff, 0, 256);
  int * send0 = (int*)(&sendBuff[0]);
  * send0 = 1;  /* 1 - read data */

  n = send(sockfd,sendBuff,1, 0); /* send read request */

  if(n < 0)
  {
    error("ERROR writing to socket");
  }
  memset(sendBuff, 0, 256);
  n = recv(sockfd, recvBuff, 3, 0); /* recieve read data */

  if (n < 0)
  {
    error("ERROR reading from socket");
  }
  
  for(i=0; i < 3; i++)
  {
    printf("%d\n", recvBuff[i]);
  }
}

void initMain()
{
  backgroundColor = 1;
  page = 6;
  sbarText = 6;
  program = 1;
  connectiOn = 0;
  transId = 1;
  posCounter = 1;
  modifier = 0;
  firstPosSmall = 0;
  firstPosMedium = 0;
  firstPosBig = 0;

  year = 2018;
  month = 1;
  day = 1;
  hour = 0;
  minute = 0;

  int * clear1 =  (int*)(&obufCl[0]);
  int * clear2 =  (int*)(&obufCl[2]);
  int * clear3 =  (int*)(&obufCl[4]);
  int * clear4 =  (int*)(&obufCl[6]);
  int * clear5 =  (int*)(&obufCl[7]);
  int * clear6 =  (int*)(&obufCl[8]);
  int * clear7 =  (int*)(&obufCl[10]);
  int * clear8 =  (int*)(&obufCl[12]);
  int * clear9 =  (int*)(&obufCl[16]);

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

  int * posOneB1 = (int*)(&obufOneB[0]);
  int * posOneB2 = (int*)(&obufOneB[2]);
  int * posOneB3 = (int*)(&obufOneB[4]);
  int * posOneB4 = (int*)(&obufOneB[6]);
  int * posOneB5 = (int*)(&obufOneB[7]);
  int * posOneB6 = (int*)(&obufOneB[8]);
  int * posOneB7 = (int*)(&obufOneB[10]);
  int * posOneB8 = (int*)(&obufOneB[12]);
  int * posOneB11 = (int*)(&obufOneB[21]);
  int * posOneB12 = (int*)(&obufOneB[28]);
  int * posOneB13 = (int*)(&obufOneB[29]);
  int * posOneB14 = (int*)(&obufOneB[33]);
  int * posOneB15 = (int*)(&obufOneB[40]);
  int * posOneB16 = (int*)(&obufOneB[44]);
  int * posOneB17 = (int*)(&obufOneB[48]);
  int * posOneB18 = (int*)(&obufOneB[52]);
      
  memset(obufOneB, 0, 58);
  * posOneB1 = transId;   
  * posOneB2 = htons(0);
  * posOneB3 = htons(47);
  * posOneB4 = 1;
  * posOneB5 = 16;
  * posOneB6 = htons(8192);
  * posOneB7 = htons(20);
  * posOneB8 = 40;
  * posOneB11 = htonl(2000000);   
  * posOneB12 = 16;           
  * posOneB13 = htonl(5000000);  
  * posOneB14 = htonl(5000000);  
  * posOneB15 = 100;            
  * posOneB16 = 0;            
  * posOneB17 = 1;            
  * posOneB18 = 1;  

  int * moveTask1 =  (int*)(&obufMT[0]);
  int * moveTask2 =  (int*)(&obufMT[2]);
  int * moveTask3 =  (int*)(&obufMT[4]);
  int * moveTask4 =  (int*)(&obufMT[6]);
  int * moveTask5 =  (int*)(&obufMT[7]);
  int * moveTask6 =  (int*)(&obufMT[8]);
  int * moveTask7 =  (int*)(&obufMT[10]);
  int * moveTask8 =  (int*)(&obufMT[12]);
  int * moveTask9 =  (int*)(&obufMT[13]);
  
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
 
  int * moveTask1Next =  (int*)(&obufMTN[0]);
  int * moveTask2Next =  (int*)(&obufMTN[2]);
  int * moveTask3Next =  (int*)(&obufMTN[4]);
  int * moveTask4Next =  (int*)(&obufMTN[6]);
  int * moveTask5Next =  (int*)(&obufMTN[7]);
  int * moveTask6Next =  (int*)(&obufMTN[8]);
  int * moveTask7Next =  (int*)(&obufMTN[10]);
  int * moveTask8Next =  (int*)(&obufMTN[12]);
  int * moveTask9Next =  (int*)(&obufMTN[13]);
  
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


  int * drvSave1 =  (int*)(&obufDS[0]);
  int * drvSave2 =  (int*)(&obufDS[2]);
  int * drvSave3 =  (int*)(&obufDS[4]);
  int * drvSave4 =  (int*)(&obufDS[6]);
  int * drvSave5 =  (int*)(&obufDS[7]);
  int * drvSave6 =  (int*)(&obufDS[8]);
  int * drvSave7 =  (int*)(&obufDS[10]);
  int * drvSave8 =  (int*)(&obufDS[12]);
  int * drvSave9 =  (int*)(&obufDS[13]);

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

  /* first position */
  //int * firstClear1 =  (int*)(&obufClFirst[0]);
  //int * firstClear2 =  (int*)(&obufClFirst[2]);
  int * firstClear3 =  (int*)(&obufClFirst[4]);
  int * firstClear4 =  (int*)(&obufClFirst[6]);
  int * firstClear5 =  (int*)(&obufClFirst[7]);
  int * firstClear6 =  (int*)(&obufClFirst[8]);
  int * firstClear7 =  (int*)(&obufClFirst[10]);
  int * firstClear8 =  (int*)(&obufClFirst[12]);
  int * firstClear9 =  (int*)(&obufClFirst[16]);

  memset(obufClFirst, 0, 17);
  //* firstClear1 = transId;   
  //* firstClear2 = htons(0);
  * firstClear3 = htons(11);
  * firstClear4 = 1;
  * firstClear5 = 16;
  * firstClear6 = htons(530);
  * firstClear7 = htons(2);
  * firstClear8 = 4;
  * firstClear9 = 2; 

  //int * posOneA1 = (int*)(&obufOneA[0]);
  int * posOneA2 = (int*)(&obufOneA[2]);
  int * posOneA3 = (int*)(&obufOneA[4]);
  int * posOneA4 = (int*)(&obufOneA[6]);
  int * posOneA5 = (int*)(&obufOneA[7]);
  int * posOneA6 = (int*)(&obufOneA[8]);
  int * posOneA7 = (int*)(&obufOneA[10]);
  int * posOneA8 = (int*)(&obufOneA[12]);
  int * posOneA11 = (int*)(&obufOneA[21]);
  int * posOneA12 = (int*)(&obufOneA[28]);
  int * posOneA13 = (int*)(&obufOneA[29]);
  int * posOneA14 = (int*)(&obufOneA[33]);
  int * posOneA15 = (int*)(&obufOneA[40]);
  int * posOneA16 = (int*)(&obufOneA[44]);
  int * posOneA17 = (int*)(&obufOneA[48]);
  int * posOneA18 = (int*)(&obufOneA[52]);
      
  memset(obufOneA, 0, 58);
  //* posOneA1 = transId;   
  * posOneA2 = htons(0);
  * posOneA3 = htons(47);
  * posOneA4 = 1;
  * posOneA5 = 16;
  * posOneA6 = htons(8192);
  * posOneA7 = htons(20);
  * posOneA8 = 40;
  * posOneA11 = htonl(2000000);   
  * posOneA12 = 16;           
  * posOneA13 = htonl(5000000);  
  * posOneA14 = htonl(5000000);  
  * posOneA15 = 100;            
  * posOneA16 = 0;            
  * posOneA17 = 1;            
  * posOneA18 = 1;  
  
  strcpy(stepCond[0][0], "POGOJ 0.1");
  strcpy(stepCond[0][1], "POGOJ 0.2");
  strcpy(stepCond[0][2], "POGOJ 0.3");
  strcpy(stepCond[1][0], "POGOJ 1.1");
  strcpy(stepCond[1][1], "POGOJ 1.2");
  strcpy(stepCond[1][2], "POGOJ 1.3");
  strcpy(stepCond[2][0], "POGOJ 2.1");
  strcpy(stepCond[2][1], "POGOJ 2.2");
  strcpy(stepCond[2][2], "POGOJ 2.3");
  strcpy(stepCond[3][0], "POGOJ 3.1");
  strcpy(stepCond[3][1], "POGOJ 3.2");
  strcpy(stepCond[3][2], "POGOJ 3.3");
  strcpy(stepCond[4][0], "POGOJ 4.1");
  strcpy(stepCond[4][1], "POGOJ 4.2");
  strcpy(stepCond[4][2], "POGOJ 4.3");
  strcpy(stepCond[5][0], "POGOJ 5.1");
  strcpy(stepCond[5][1], "POGOJ 5.2");
  strcpy(stepCond[5][2], "POGOJ 5.3");
  strcpy(stepCond[6][0], "POGOJ 6.1");
  strcpy(stepCond[6][1], "POGOJ 6.2");
  strcpy(stepCond[6][2], "POGOJ 6.3");
  strcpy(stepCond[7][0], "POGOJ 7.1");
  strcpy(stepCond[7][1], "POGOJ 7.2");
  strcpy(stepCond[7][2], "POGOJ 7.3");
  strcpy(stepCond[8][0], "POGOJ 8.1");
  strcpy(stepCond[8][1], "POGOJ 8.2");
  strcpy(stepCond[8][2], "POGOJ 8.3");
  strcpy(stepCond[9][0], "POGOJ 9.1");
  strcpy(stepCond[9][1], "POGOJ 9.2");
  strcpy(stepCond[9][2], "POGOJ 9.3");
  
  strcpy(stepName[0], "KORAK1");
  strcpy(stepName[1], "KORAK2");
  strcpy(stepName[2], "KORAK3");
  strcpy(stepName[3], "KORAK4");
  strcpy(stepName[4], "KORAK5");
  strcpy(stepName[5], "KORAK6");
  strcpy(stepName[6], "KORAK7");
  strcpy(stepName[7], "KORAK8");
  strcpy(stepName[8], "KORAK9");
  strcpy(stepName[9], "KORAK10");

  #ifdef RPI   
  fp_first_pos = fopen("/home/pi/TKK_PRESA/data/first_pos.txt", "r");
  #endif
  #ifdef LUKA
  fp_first_pos = fopen("/home/luka/TKK_PRESA_/data/first_pos.txt", "r");
  #endif

  for(i = 0; i < 3; ++i)
  {
    getline(&line, &len, fp_first_pos);
    if(i==0)
    {
      firstPosSmall = atoi(line);
    }
    else if(i==1)
    {
      firstPosMedium = atoi(line);
    }
    else if(i==2)
    {
      firstPosBig = atoi(line);
    }
  }
 
}

void error(const char *msg)
{
  perror(msg);
  exit(1);
}

