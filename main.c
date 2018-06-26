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
  initMain();
  init();
  initVars();
  initComm();
   
  while(program == 1)
  {
    if(connectiOn) /* read registers only if connected to controller */
    {
      /*rc = modbus_read_registers(ctx, 1, nb, regs);*/
    }
   
    for(i = 0; i < 10; i++)
    {
      printf("REG%d:%d\n", i, regs[i]);
    }
    
    usleep(1000);
    /*errorCheck();*/
    touchUpdate();
    renderBackground();
    renderStatusBar();
    renderContent();
    SDL_RenderPresent(renderer);
    cycle++;
  }
  return 0;
}



void errorCheck()
{
  if(regs[5] == 7)
  {
    page = 2;
  }
}

void initComm()
{
  printf("FUNCTION CALLED\n");
  ctx = modbus_new_tcp("192.168.0.13", 502);  
  if(modbus_connect(ctx) == -1) 
  {
    
    fprintf(stderr,"Connection failed: %s\n",modbus_strerror(errno));
    modbus_free(ctx);
    /*
    exit(100);
    */
    page = 2; 
    sbarText = 2;
    connectiOn = 0;
  }

  nb = sizeof(regs)/sizeof(int16_t);   
  modbus_set_debug(ctx, FALSE); 

  /* AKD CONN */
  
 
  ip_adrs = "192.168.0.13";
  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  server.sin_family = AF_INET;
  server.sin_port = htons(502);
  server.sin_addr.s_addr = inet_addr(ip_adrs);

  x = connect(s, (struct sockaddr *)&server, sizeof(struct sockaddr_in));
  
}


void initMain()
{
  program = 1;
  connectiOn = 1;
  transId = 1;
  posCounter = 1;
  /* parameter values to be send to AKD */

  memset(obufCl, 0, 17);
  int * clear1 =  (int*)(&obufCl[0]);
  int * clear2 =  (int*)(&obufCl[2]);
  int * clear3 =  (int*)(&obufCl[4]);
  int * clear4 =  (int*)(&obufCl[6]);
  int * clear5 =  (int*)(&obufCl[7]);
  int * clear6 =  (int*)(&obufCl[8]);
  int * clear7 =  (int*)(&obufCl[10]);
  int * clear8 =  (int*)(&obufCl[12]);
  int * clear9 =  (int*)(&obufCl[16]);
  
  * clear1 = transId;  
  * clear2 = htons(0);
  * clear3 = htons(11);
  * clear4 = 1;
  * clear5 = 16;
  * clear6 = htons(530);
  * clear7 = htons(2);
  * clear8 = 4;
  * clear9 = posCounter;           

  memset(obufOne, 0, 58);
  int * posOne1 = (int*)(&obufOne[0]);
  int * posOne2 = (int*)(&obufOne[2]);
  int * posOne3 = (int*)(&obufOne[4]);
  int * posOne4 = (int*)(&obufOne[6]);
  int * posOne5 = (int*)(&obufOne[7]);
  int * posOne6 = (int*)(&obufOne[8]);
  int * posOne7 = (int*)(&obufOne[10]);
  int * posOne8 = (int*)(&obufOne[12]);
  int * posOne9 =  (int*)(&obufOne[16]);
  int * posOne10 = (int*)(&obufOne[17]);    
  int * posOne11 = (int*)(&obufOne[21]);
  int * posOne12 = (int*)(&obufOne[28]);
  int * posOne13 = (int*)(&obufOne[29]);
  int * posOne14 = (int*)(&obufOne[33]);
  int * posOne15 = (int*)(&obufOne[40]);
  int * posOne16 = (int*)(&obufOne[44]);
  int * posOne17 = (int*)(&obufOne[48]);
  int * posOne18 = (int*)(&obufOne[52]);

  * posOne1 = transId;   
  * posOne2 = htons(0);
  * posOne3 = htons(47);
  * posOne4 = 1;
  * posOne5 = 16;
  * posOne6 = htons(8192);
  * posOne7 = htons(20);
  * posOne8 = 40;
  * posOne9 = 0;             /*mtnum*/    
  * posOne10 = htonl(1000);  /*pos - (desired value must be multiplied by 10000) */
  * posOne11 = htonl(1000);  /*vel -  (desired value must be multiplied by 10000) */
  * posOne12 = 16;           /*cntl*/
  * posOne13 = htonl(1000);  /*acc - (desired value must be multiplied by 10000) */  
  * posOne14 = htonl(1000);  /*dec - (desired value must be multiplied by 10000) */  
  * posOne15 = 1;            /*next*/
  * posOne16 = 0;            /*delay*/
  * posOne17 = 1;            /*mtset*/
  * posOne18 = 1;            /*drvsav*/
}

