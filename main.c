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
      rc = modbus_read_registers(ctx, 1, nb, regs);
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
  ctx = modbus_new_tcp("192.168.1.76", 1500);  
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
}


void initMain()
{
  program = 1;
  connectiOn = 1;

  /* parameter values to be send to AKD */
  regsSmall[0] = 7;
  regsSmall[1] = 7;
  regsSmall[2] = 7;
  regsSmall[3] = 7;
  regsSmall[4] = 6;
  regsSmall[5] = 7;
  regsSmall[6] = 7;
  regsSmall[7] = 7;
  regsSmall[8] = 7;
  regsSmall[9] = 7;

  regsMedium[0] = 7;
  regsMedium[1] = 7;
  regsMedium[2] = 7;
  regsMedium[3] = 7;
  regsMedium[4] = 7;
  regsMedium[5] = 6;
  regsMedium[6] = 7;

  regsLarge[0] = 7;
  regsLarge[1] = 7;
  regsLarge[2] = 7;
  regsLarge[3] = 7;
  regsLarge[4] = 7;
  regsLarge[5] = 6;
  regsLarge[6] = 7;
}

