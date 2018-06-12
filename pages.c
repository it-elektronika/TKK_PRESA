#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "main.h"

void pageOne()
{
  int i;
  int y = 250;
  if(page_stage[0] == 0) /* loading page */
  {
    
    #ifdef RPI   
    fp_can_size = fopen("/home/pi/TKK_PRESA/data/can_size.txt", "r");
    #endif
    #ifdef LUKA
    fp_can_size = fopen("/home/luka/TKK_PRESA/data/can_size.txt", "r");
    #endif
 
    for(i = 0; i < 1; ++i)
    {
      printf("HERE\n");
      getline(&line, &len, fp_can_size);
      printf("pageone\n");

      if(i==0)
      {
        if(atoi(line) == 0)
        {
          selected[0]=1;
          selected[1]=0;
          selected[2]=0;     
        }
        else if(atoi(line) == 1)
        {
          selected[0]=0;
          selected[1]=1;
          selected[2]=0;  
        }
        else if(atoi(line) == 2)
        {
          selected[0]=0;
          selected[1]=0;
          selected[2]=1;  
        }
      }
    }
    fclose(fp_can_size);
    
    page_stage[0] = 1;
  }
  else if(page_stage[0] == 1)
  {
      
    renderAdmin(1200, 0, 80, 80, 0, 1);
    

    if(selected[0])
    {
      renderText("VELIKOST DOZE: MALA", regularText, blackColor);
    }
    else if(selected[1])
    {   
      renderText("VELIKOST DOZE: SREDNJA", regularText, blackColor);
    }  
    else if(selected[2])
    {  
      renderText("VELIKOST DOZE: VELIKA", regularText, blackColor);
    }
    render(30, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);

    for(i = 0; i < 10; i++)
    {
      sprintf(buff_reg[i], "REG%d:%d", i, regs[i]);
      renderText(buff_reg[i], regularText, blackColor);
      render(30, y, NULL, 0.0, NULL, SDL_FLIP_NONE);
      y = y + 50;
    }
    
    
  }
  else if(page_stage[0] == 2)
  {


    page_stage[0] = 0;
  }
}

void pageTwo()
{
  if(page_stage[1] == 0)
  {
    page_stage[1] = 1;
  }
  if(page_stage[1] == 1)
  {
    renderAdmin(1200, 0, 80, 80, 1, 0);
    button(200, 200, 200, 100, "MALA", 0);
    button(200, 400, 200, 100, "SREDNJA", 1);
    button(200, 600, 200, 100, "VELIKA", 2);
    saveButton(500, 600, 200, 100, "SHRANI");
  }
  if(page_stage[1] == 2)
  {
    page_stage[1] = 0;
  }
}

void pageThree()
{
  if(page_stage[2] == 0)
  {
    page_stage[2] = 1;
  }
  else if(page_stage[2] == 1)
  {
    renderAdmin(1200, 0, 80, 80, 2, 0);
  }
  else if(page_stage[2] == 2)
  {
    page_stage[2] = 0;
  }
}


