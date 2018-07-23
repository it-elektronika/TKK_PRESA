#include <stdio.h>
#include "graphics_sdl.h"
#include "main.h"
#include <errno.h>

void initMain();
void initComm();

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
    initComm();
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
    cycle++;
  }
  return 0;
}



void initComm()
{
  /*
  printf("FUNCTION CALLED\n");
  ctx = modbus_new_tcp("192.168.0.13", 502);  
  if(modbus_connect(ctx) == -1) 
  {
    fprintf(stderr,"Connection failed: %s\n",modbus_strerror(errno));
    modbus_free(ctx);
    
    exit(100);
    
    page = 2; 
    sbarText = 2;
    connectiOn = 0;
  }

  nb = sizeof(regs)/sizeof(int16_t);   
  modbus_set_debug(ctx, FALSE); 
  */

  /* AKD CONN */
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
  }
  else
  {
    connectiOn = 1; 
    page_stage[6] = 0;
    page = 0;
  }
  printf("%d\n", conn);
  usleep(3000);
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
  * posOneB11 = htonl(5000000);   
  * posOneB12 = 16;           
  * posOneB13 = htonl(10000000);  
  * posOneB14 = htonl(10000000);  
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

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 3; j++)
    {
      printf("stepCond[%d][%d]:%s\n", i, j, stepCond[i][j]);
    }
  }
  
  for(int i = 0; i < 10; i++)
  {
    printf("stepName[%d]:%s\n", i, stepName[i]);
  }
}



