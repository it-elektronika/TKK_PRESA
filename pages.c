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
    fp_can_size = fopen("/home/luka/TKK_PRESA_/data/can_size.txt", "r");
    #endif
 
    for(i = 0; i < 1; ++i)
    {
      getline(&line, &len, fp_can_size);

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

    renderText("POPRAVEK:", smallText, blackColor);
    render(550, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
   
    sprintf(modifierBuff, "%d mm", modifier);
    renderText(modifierBuff, smallText, blackColor);
    render(800, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
    
    up_button(1000, 200, &modifier, 1, 5);
    down_button(1100, 200, &modifier, 1, -5);

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

void pageFour() /* waiting for drives to connect */
{
  if(page_stage[3] == 0)
  {
    page_stage[3] = 1;
  }
  else if(page_stage[3] == 1)
  {
    if(connectiOn)
    {
      renderText("DRIVE PRESA: OK", regularText, blackColor);
    }
    else
    {
      renderText("DRIVE PRESA: NOK", regularText, blackColor);
    }
    render(50, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);

    if(connectiOn)
    {
      renderText("DRIVE OGRODJE: OK", regularText, blackColor);
    }
    else
    {
      renderText("DRIVE OGRODJE: NOK", regularText, blackColor);
    }
    render(50, 400, NULL, 0.0, NULL, SDL_FLIP_NONE);
    if(connectiOn)
    {
      renderText("DRIVE MIZA: OK", regularText, blackColor);
    }
    else
    {
      renderText("DRIVE MIZA: NOK", regularText, blackColor);
    }
    render(50, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);
  }
  else if(page_stage[3] == 2)
  {
    page_stage[3] = 0;
  }
}

void pageFive() /* set time */
{
  if(page_stage[3] == 0)
  {
    page_stage[3] = 1;
  }
  else if(page_stage[3] == 1)
  {
    sprintf(yearBuff, "LETO: %04d", year);
    sprintf(monthBuff, "MESEC: %02d", month);
    sprintf(dayBuff, "DAN: %02d", day);
    sprintf(hourBuff, "URE: %02d", hour);
    sprintf(minuteBuff, "MINUTE: %02d", minute);

    renderText(yearBuff, regularText, blackColor);
    render(50, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(400, 200, &year, 1, 2100);
    down_button(500, 200, &year, 1, 2018);


    renderText(monthBuff, regularText, blackColor);
    render(50, 300, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(400, 300, &month, 1, 12);
    down_button(500, 300, &month, 1, 1);

    renderText(dayBuff, regularText, blackColor);
    render(50, 400, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(400, 400, &day, 1, 31);
    down_button(500, 400, &day, 1, 1);

    renderText(hourBuff, regularText, blackColor);
    render(50, 500, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(400, 500, &hour, 1, 24);
    down_button(500, 500, &hour, 1, 0);

    renderText(minuteBuff, regularText, blackColor);
    render(50, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(400, 600, &minute, 1, 60);
    down_button(500, 600, &minute, 1, 0);

    saveTime(50, 700, 100, 100, "SHRANI");
    renderAdmin(1200, 0, 80, 80, 4, 0);
  }
  else if(page_stage[3] == 2)
  {
    page_stage[3] = 0;
  }
}
