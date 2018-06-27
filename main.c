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
  /*                                                                    */  
}

void initMain()
{
  program = 1;
  connectiOn = 1;
  transId = 1;
  posCounter = 1;
}



