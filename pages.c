#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "main.h"

void pageZero(int pageNum)  /* LANDING PAGE */
{
  int i;
  int y = 250;
  if(page_stage[pageNum] == 0) /* loading page */
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
    
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 1);

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

    for(i = 0; i < 10; ++i)
    {
      sprintf(buff_reg[i], "REG%d:%d", i, regs[i]);
      renderText(buff_reg[i], regularText, blackColor);
      render(30, y, NULL, 0.0, NULL, SDL_FLIP_NONE);
      y = y + 50;
    }
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageOne(int pageNum) /* MAIN MENU */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 0);
    goToButton(30, 200, 350, 100, "IZBIRA DOZE", pageNum, 2);
    goToButton(30, 400, 500, 100, "ROCNO NASTAVLJANJE", pageNum, 10);
    goToButton(30, 600, 350, 100, "DIAGNOSTIKA", pageNum, 4);
    
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageTwo(int pageNum) /* CAN SIZE SELECTION */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 1);
    button(30, 200, 200, 100, "MALA", 0);
    button(30, 400, 200, 100, "SREDNJA", 1);
    button(30, 600, 200, 100, "VELIKA", 2);

    renderText("POPRAVEK:", smallText, blackColor);
    render(400, 220, NULL, 0.0, NULL, SDL_FLIP_NONE);
   
    sprintf(modifierBuff, "%d mm", modifier);
    renderText(modifierBuff, smallText, blackColor);
    render(650, 220, NULL, 0.0, NULL, SDL_FLIP_NONE);
    
    up_button(800, 210, &modifier, 1, 5);
    down_button(900, 210, &modifier, 1, -5);

    saveButton(400, 600, 200, 100, "SHRANI");
  }
  if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageThree(int pageNum)  /* I/O STATUS */
{
  int i;
  int y;
  y = 100;
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 10);
    
    for(i = 0; i < 5; ++i)
    {
      SDL_RenderDrawLine(renderer, 1200+i, 75, 1200+i, 800);
      SDL_RenderDrawLine(renderer, 1200, 180+i, 1280, 180+i);
      SDL_RenderDrawLine(renderer, 1200, 700+i, 1280, 700+i);
    }
    for(i = 0; i < 14; ++i)
    {
      if((y + modY >= 100))
      {
        scrollArr[i] = 0;
      } 
      else if((y + modY) < 100)
      {
        scrollArr[i] = 1;
      }
 
      if(scrollArr[i] < 1)
      {
        sprintf(buff_inputs[i], "I_%d:%s", i+1, inputs[i]);
        renderText(buff_inputs[i], regularText, blackColor);
        render(30, y+modY, NULL, 0.0, NULL, SDL_FLIP_NONE);
        outputButton(300, y+modY, 100, 50, i);
      }
      y = y + 70;
    }
    
    up_button(1220, 120, &modY, 100, 0);
    down_button(1220, 720, &modY, 100, -1300);
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageFour(int pageNum)  /* DIAGNOSTICS */
{
  int i;
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 1);
    continue_button(30, 200, 350, 100, 9);
    start_button(700, 200, 250, 100);
    stop_button(1000, 200, 250, 100);
         
    sprintf(stepCounter, "%d/9", step); 
    renderText(stepCounter, regularText, blackColor);
    render(430, 230, NULL, 0.0, NULL, SDL_FLIP_NONE);

    for(i = 0; i < 10; ++i)
    {
      SDL_RenderDrawLine(renderer, 0, 400+i, 1280, 400+i);
    }
    for(i = 0; i < 5; ++i)
    {
      SDL_RenderDrawLine(renderer, 0, 450+i, 1280, 450+i);
    }

    for(i = 0; i < 10; ++i)
    {
      SDL_RenderDrawLine(renderer, 640+i, 400, 640+i, 800);
    }

    renderText("TRENUTNI KORAK", smallText, blackColor);
    render(30, 415, NULL, 0.0, NULL, SDL_FLIP_NONE);

    renderText("NASLEDNJI KORAK", smallText, blackColor);
    render(680, 415, NULL, 0.0, NULL, SDL_FLIP_NONE);

    
    renderText(stepCond[step][0], smallText, blackColor);
    render(30, 500, NULL, 0.0, NULL, SDL_FLIP_NONE);

    renderText(stepCond[step][1], smallText, blackColor);
    render(30, 550, NULL, 0.0, NULL, SDL_FLIP_NONE);

    renderText(stepCond[step][2], smallText, blackColor);
    render(30, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);

    if(step != lastStep)
    {
      renderText(stepCond[step+1][0], smallText, blackColor);
      render(700, 500, NULL, 0.0, NULL, SDL_FLIP_NONE);

      renderText(stepCond[step+1][1], smallText, blackColor);
      render(700, 550, NULL, 0.0, NULL, SDL_FLIP_NONE);

      renderText(stepCond[step+1][2], smallText, blackColor);
      render(700, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);
    }
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageFive(int pageNum) /* TIME */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
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
    renderAdmin(1200, 0, 80, 80, pageNum, 0);
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageSix(int pageNum) /* CONNECTING */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 1); 
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageSeven(int pageNum) /* ERROR DRIVES */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
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
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageEight(int pageNum)  /* ERROR */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 0);
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}


void pageNine(int pageNum)  /* ERROR */
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 10);
    
    sprintf(smallBuff, "MALA:%d mm", firstPosSmall);
    renderText(smallBuff, smallText, blackColor);
    render(30, 220, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 220, &firstPosSmall, 1, 100);
    down_button(700, 220, &firstPosSmall, 1, 0);

 
    sprintf(smallBuff, "SREDNJA:%d mm", firstPosMedium);
    renderText(smallBuff, smallText, blackColor);
    render(30, 320, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 320, &firstPosMedium, 1, 100);
    down_button(700, 320, &firstPosMedium, 1, 0);


    sprintf(smallBuff, "VELIKA:%d mm", firstPosBig);
    renderText(smallBuff, smallText, blackColor);
    render(30, 420, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 420, &firstPosBig, 1, 100);
    down_button(700, 420, &firstPosBig, 1, 0);

    savePos(30, 600, 200, 100);
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageTen(int pageNum)
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 1);
    goToButton(30, 200, 500, 100, "NASTAVITVE POZICIJ" , pageNum, 9); 
    goToButton(30, 400, 350, 100, "DRIVE ROCNO", pageNum, 11);
    goToButton(30, 600, 350, 100, "I / O ", pageNum, 3);
    
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}

void pageEleven(int pageNum)
{
  if(page_stage[pageNum] == 0)
  {
    page_stage[pageNum] = 1;
  }
  else if(page_stage[pageNum] == 1)
  {
    renderAdmin(1200, 0, 80, 80, pageNum, 10);
    
    renderText("MALA", smallText, blackColor);
    render(30, 230, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("SREDNJA", smallText, blackColor);
    render(30, 430, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("VELIKA", smallText, blackColor);
    render(30, 630, NULL, 0.0, NULL, SDL_FLIP_NONE);
 
    renderText("1.", smallText, blackColor);
    render(220, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("2.", smallText, blackColor);
    render(450, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
 

    posButton(200, 200, 150, 100, "", firstPosSmall);
    posButton(200, 400, 150, 100, "", firstPosMedium);
    posButton(200, 600, 150, 100, "", firstPosBig);
  
    posButton(400, 200, 150, 100, "", secondPosSmall);
    posButton(400, 400, 150, 100, "", secondPosMedium);
    posButton(400, 600, 150, 100, "", secondPosBig);
   
   
    sprintf(posManBuff, "POZICIJA:%d mm", posMan);
    renderText(posManBuff, smallText, blackColor);
    render(800, 210, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
    up_button(1100, 200, &posMan, 1, 150);
    down_button(1200, 200, &posMan, 1, 0);

    enableButton(800, 400, 200, 100);
    disableButton(1000, 400, 200, 100);
    
    startButton(800, 600, 200, 100);
  }
  else if(page_stage[pageNum] == 2)
  {
    page_stage[pageNum] = 0;
  }
}
