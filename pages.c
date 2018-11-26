#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "main.h"

void pageZero()  /* LANDING PAGE */
{
  
  int i;
  if(page_stage == ENTER) /* loading page */
  {
    printf("PAGE_ZERO - ENTER\n");
    #ifdef RPI   
    fp_can_size = fopen("/home/pi/TKK_PRESA/data/can_size.txt", "r");
    #endif
    #ifdef LUKA
    fp_can_size = fopen("/home/luka/TKK_PRESA_/data/can_size.txt", "r");
    #endif
    clearError = 0;

    for(i = 0; i < 1; ++i)
    {
      getline(&line, &len, fp_can_size);
      if(i==0)
      {
        if(atoi(line) == 0)
        {
          selectedCan = 0;
          selected[0]=1;
          selected[1]=0;
          selected[2]=0;
          selected[3]=0;     
        }
        else if(atoi(line) == 1)
        {
          selectedCan = 1;
          selected[0]=0;
          selected[1]=1;
          selected[2]=0;
          selected[3]=0;  
        }
        else if(atoi(line) == 2)
        {
          selectedCan = 2;
          selected[0]=0;
          selected[1]=0;
          selected[2]=1;  
          selected[3]=0;
        }
        else if(atoi(line) == 3)
        {
          selectedCan = 3;
          selected[0]=0;
          selected[1]=0;
          selected[2]=0;
          selected[3]=1;  
        }
      }
    }
    fclose(fp_can_size);

    #ifdef RPI   
    fp_first_pos = fopen("/home/pi/TKK_PRESA/data/first_pos.txt", "r");
    #endif
    #ifdef LUKA
    fp_first_pos = fopen("/home/luka/TKK_PRESA_/data/first_pos.txt", "r");
    #endif

    for(i = 0; i < 4; ++i)
    {
      getline(&line, &len, fp_first_pos);
      if(i==0)
      {
	firstPosSmall = atoi(line);
      }
      else if(i==1)
      {
	firstPosSmall2 = atoi(line);
      }
      else if(i==2)
      {
	firstPosMedium = atoi(line);
      }
      else if(i==3)
      {
	firstPosBig = atoi(line);
      }
    }
    fclose(fp_first_pos);

    #ifdef RPI   
    AKD_pos = fopen("/home/pi/TKK_PRESA/data/AKD_pos.txt", "r");
    #endif
    #ifdef LUKA
    AKD_pos = fopen("/home/luka/TKK_PRESA_/data/AKD_pos.txt", "r");
    #endif

    for(i = 0; i < 4; ++i)
    {
      getline(&line, &len, AKD_pos);
      if(i==0)
      {
	AKD_frame_posSmall = atoi(line);
      }
      else if(i==1)
      {
	AKD_frame_posSmall2 = atoi(line);
      }
      else if(i==2)
      {
	AKD_frame_posMedium = atoi(line);
      }
      else if(i==3)
      {
	AKD_frame_posBig = atoi(line);
      }
    }
    fclose(AKD_pos);
  
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    printf("PAGE ZERO - ENABLE\n");
    if(!inCycle)
    {
      renderAdmin(1200, 0, 80, 80, 1);
    }
    if(selected[0])
    {
      renderText("VELIKOST DOZE: MALA", regularText, blackColor);
    }
    else if(selected[1])
    {   
      renderText("VELIKOST DOZE: MALA2", regularText, blackColor);
    }  
    else if(selected[2])
    {  
      renderText("VELIKOST DOZE: SREDNJA", regularText, blackColor);
    }
   
    else if(selected[3])
    {  
      renderText("VELIKOST DOZE: VELIKA", regularText, blackColor);
    }
    render(30, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageOne() /* MAIN MENU */
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 0);
    goToButton(30, 200, 350, 100, "IZBIRA DOZE", 2);
    goToButton(30, 350, 500, 100, "ROCNO NASTAVLJANJE", 10);
    goToButton(30, 500, 350, 100, "DIAGNOSTIKA", 4);
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageTwo() /* CAN SIZE SELECTION */
{
 if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 1);
    button(30, 150, 200, 100, "MALA", 0);
    button(30, 300, 200, 100, "MALA2", 1);
    button(30, 450, 200, 100, "SREDNJA", 2);
    button(30, 600, 200, 100, "VELIKA", 3);

    //renderText("POPRAVEK:", smallText, blackColor);
    //render(400, 180, NULL, 0.0, NULL, SDL_FLIP_NONE);
   
    //sprintf(modifierBuff, "%d mm", modifier);
    //renderText(modifierBuff, smallText, blackColor);
    //render(650, 180, NULL, 0.0, NULL, SDL_FLIP_NONE);
    
    //up_button(800,180, &modifier, 1, 5);
    //down_button(900, 180, &modifier, 1, -5);

    saveButton(400, 600, 200, 100, "SHRANI");
  }
  if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageThree()  /* I/O STATUS */
{
  int i;
  int y;
  y = 100;
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 10);
    
    for(i = 0; i < 5; ++i)
    {
      SDL_RenderDrawLine(renderer, 1200+i, 75, 1200+i, 800);
      SDL_RenderDrawLine(renderer, 1200, 180+i, 1280, 180+i);
      SDL_RenderDrawLine(renderer, 1200, 700+i, 1280, 700+i);
    }
    for(i = 0; i < ioPins; ++i)
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
        sprintf(buff_inputs_val[i], "%s: %s", buff_inputs[i], inputs[i]);
        renderText(buff_inputs_val[i], regularText, blackColor);
        render(30, y+modY, NULL, 0.0, NULL, SDL_FLIP_NONE);
       
        outputButton(500, y+modY, 100, 50, i);
      }
      y = y + 70;
    }
    
    up_button(1220, 120, &modY, 100, 0);
    down_button(1220, 720, &modY, 100, -2200);
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageFour()  /* DIAGNOSTICS */
{
  int i;
  if(page_stage == ENTER)
  { 
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 1);
    continue_button(30, 200, 350, 100, lastStep);
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

   /* 
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
    }*/
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageFive() /* TIME */
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
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
    renderAdmin(1200, 0, 80, 80, 0);
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageSix() /* CONNECTING */
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 1); 
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageSeven() /* ERROR DRIVES */
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    if(conn_presa == 0)
    {
      renderText("DRIVE PRESA: OK", regularText, blackColor);
    }
    else
    {
      renderText("DRIVE PRESA: NOK", regularText, blackColor);
    }
    render(50, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
   
    if(conn_hmi == 0)
    {
      renderText("HMI: OK", regularText, blackColor);
    }
    else
    {
      renderText("HMI: NOK", regularText, blackColor);
    }
    render(50, 400, NULL, 0.0, NULL, SDL_FLIP_NONE);
    
/*
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
    render(50, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);*/
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageEight()  /* ERROR */
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 0);
    switch(errorNumber)
    {  
      sprintf(errorMessageBuff, "MALA:%d mm", step);
      case 1:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder zapiranje celjusti", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 2:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder zapiranje celjusti", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 3:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder spuscanje celjusti", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 4:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder spuscanje celjusti", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 5:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder odpiranje celjusti", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 6:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder odpiranje celjusti", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 7:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder -", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 8:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder -", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 9:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder -", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 10:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder -", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 11:
        sprintf(errorMessageBuff, "KORAK_%d: cilinder -", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 12:
        sprintf(errorMessageBuff, "KORAK_%d: na dozi ni pokrovcka", step);
        renderText(errorMessageBuff, regularText, blackColor);
        break;
      case 13:
        renderText("- PREVERI DOTOK ZRAKA", regularText, blackColor);
        break;
      case 14:
        renderText("- PREVERI DOTOK ZRAKA", regularText, blackColor);
        break;
      case 15:
        renderText("- potreben je ponoven vklop stroja", regularText, blackColor);
        break;
      case 16:  
        renderText("- potreben je ponoven vklop stroja", regularText, blackColor);
        break; 
      case 17:  
        renderText("- preveri dotok zraka", regularText, blackColor);
        break;
      case 18:
        renderText("- preveri dotok zraka", regularText, blackColor);
        break;
      case 19:  
        renderText("- vstavi nov pokrovcek v celjust / odstrani pokrovcek iz senzorja", regularText, blackColor);
        break;
      case 20:
        renderText("- pokrovcka ni bilo v celjusti  ", regularText, blackColor);
        break;
      
      default:
        break;

    }
    render(50, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
 
  }
  else if(page_stage == EXIT)
  {
    errorNumber = 0;
    page_stage = ENTER;
  }
}


void pageNine()  
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 10);
    /*
    sprintf(smallBuff, "MALA:%d mm", firstPosSmall);
    renderText(smallBuff, smallText, blackColor);
    render(30, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 140, &firstPosSmall, 1, 200);
    down_button(700, 140, &firstPosSmall, 1, 0);
    renderText("ZGORAJ", smallText, blackColor);
    render(800, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
    sprintf(AKD_smallBuff, "MALA:%d mm", AKD_frame_posSmall);
    renderText(AKD_smallBuff, smallText, blackColor);
    render(30, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 190, &AKD_frame_posSmall, 1, 200);
    down_button(700, 190, &AKD_frame_posSmall, 1, 0);
    renderText("SPODAJ", smallText, blackColor);
    render(800, 200, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
    sprintf(small2Buff, "MALA2:%d mm", firstPosSmall2);
    renderText(small2Buff, smallText, blackColor);
    render(30, 300, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("ZGORAJ", smallText, blackColor);
    render(800, 300, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 290, &firstPosSmall2, 1, 200);
    down_button(700, 290, &firstPosSmall2, 1, 0);

    sprintf(AKD_small2Buff, "MALA2:%d mm", AKD_frame_posSmall2);
    renderText(AKD_small2Buff, smallText, blackColor);
    render(30, 350, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 340, &AKD_frame_posSmall2, 1, 200);
    down_button(700, 340, &AKD_frame_posSmall2, 1, 0);
    renderText("SPODAJ", smallText, blackColor);
    render(800, 350, NULL, 0.0, NULL, SDL_FLIP_NONE);
 
    sprintf(mediumBuff, "SREDNJA:%d mm", firstPosMedium);
    renderText(mediumBuff, smallText, blackColor);
    render(30, 450, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 440, &firstPosMedium, 1, 200);
    down_button(700, 440, &firstPosMedium, 1, 0);
    renderText("ZGORAJ", smallText, blackColor);
    render(800, 450, NULL, 0.0, NULL, SDL_FLIP_NONE);

    sprintf(AKD_mediumBuff, "SREDNJA:%d mm", AKD_frame_posMedium);
    renderText(AKD_mediumBuff, smallText, blackColor);
    render(30, 500, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 490, &AKD_frame_posMedium, 1, 200);
    down_button(700, 490, &AKD_frame_posMedium, 1, 0);
    renderText("SPODAJ", smallText, blackColor);
    render(800, 500, NULL, 0.0, NULL, SDL_FLIP_NONE);
 
    sprintf(bigBuff, "VELIKA:%d mm", firstPosBig);
    renderText(bigBuff, smallText, blackColor);
    render(30, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 590, &firstPosBig, 1, 200);
    down_button(700, 590, &firstPosBig, 1, 0);
    renderText("ZGORAJ", smallText, blackColor);
    render(800, 600, NULL, 0.0, NULL, SDL_FLIP_NONE);

    sprintf(AKD_bigBuff, "VELIKA:%d mm", AKD_frame_posBig);
    renderText(AKD_bigBuff, smallText, blackColor);
    render(30, 650, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(500, 640, &AKD_frame_posBig, 1, 200);
    down_button(700, 640, &AKD_frame_posBig, 1, 0);
    renderText("SPODAJ", smallText, blackColor);
    render(800, 650, NULL, 0.0, NULL, SDL_FLIP_NONE);
    */
    sprintf(pressBuff, "STISK:%d mm", press);
    renderText(pressBuff, smallText, blackColor);
    render(950, 150, NULL, 0.0, NULL, SDL_FLIP_NONE);
    up_button(1150, 140, &press, 1, 10);
    down_button(1200, 140, &press, 1, 0);
 
    savePos(30, 720, 200, 50);
 }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageTen()
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 1);
    goToButton(30, 200, 500, 100, "NASTAVITVE POZICIJ", 9); 
    goToButton(30, 400, 350, 100, "DRIVE ROCNO", 11);
    goToButton(30, 600, 350, 100, "I / O ", 3);
    
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageEleven()
{
  int i;
  if(page_stage == ENTER)
  {
    
    #ifdef RPI   
    fp_first_pos = fopen("/home/pi/TKK_PRESA/data/first_pos.txt", "r");
    #endif
    #ifdef LUKA
    fp_first_pos = fopen("/home/luka/TKK_PRESA_/data/first_pos.txt", "r");
    #endif

    for(i = 0; i < 4; ++i)
    {
      getline(&line, &len, fp_first_pos);
      if(i==0)
      {
	firstPosSmall = atoi(line);
      }
      else if(i==1)
      {
	firstPosSmall2 = atoi(line);
      }
      else if(i==2)
      {
	firstPosMedium = atoi(line);
      }
      else if(i==3)
      {
	firstPosBig = atoi(line);
      }
    }
    fclose(fp_first_pos);

    #ifdef RPI   
    AKD_pos = fopen("/home/pi/TKK_PRESA/data/AKD_pos.txt", "r");
    #endif
    #ifdef LUKA
    AKD_pos = fopen("/home/luka/TKK_PRESA_/data/AKD_pos.txt", "r");
    #endif

    for(i = 0; i < 4; ++i)
    {
      getline(&line, &len, AKD_pos);
      if(i==0)
      {
	AKD_frame_posSmall = atoi(line);
      }
      else if(i==1)
      {
	AKD_frame_posSmall2 = atoi(line);
      }
      else if(i==2)
      {
	AKD_frame_posMedium = atoi(line);
      }
      else if(i==3)
      {
	AKD_frame_posBig = atoi(line);
      }
    }
    fclose(AKD_pos);
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 10);
    
    renderText("MALA", smallText, blackColor);
    render(30, 180, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("MALA2", smallText, blackColor);
    render(30, 330, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("SREDNJA", smallText, blackColor);
    render(30, 480, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("VELIKA", smallText, blackColor);
    render(30, 630, NULL, 0.0, NULL, SDL_FLIP_NONE);
 
    renderText("1.", smallText, blackColor);
    render(265, 100, NULL, 0.0, NULL, SDL_FLIP_NONE);
    renderText("2.", smallText, blackColor);
    render(465, 100, NULL, 0.0, NULL, SDL_FLIP_NONE);
 

    posButton(200, 150, 150, 100, "", firstPosSmall);
    posButton(200, 300, 150, 100, "", firstPosSmall2);
   
    posButton(200, 450, 150, 100, "", firstPosMedium);
    posButton(200, 600, 150, 100, "", firstPosBig);
  
    posButton(400, 150, 150, 100, "", AKD_frame_posSmall);
    posButton(400, 300, 150, 100, "", AKD_frame_posSmall2);
   
    posButton(400, 450, 150, 100, "", AKD_frame_posMedium);
    posButton(400, 600, 150, 100, "", AKD_frame_posBig);
   
   
    sprintf(posManBuff, "POZICIJA:%d mm", posMan);
    renderText(posManBuff, smallText, blackColor);
    render(800, 210, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
    up_button(1075, 200, &posMan, 1, 150);
    down_button(1150, 200, &posMan, 1, 0);

    enableButton(800, 400, 200, 100);
    disableButton(1000, 400, 200, 100);
    
    startButton(800, 600, 200, 100);
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}

void pageTwelve()
{
  if(page_stage == ENTER)
  {
    page_stage = ENABLE;
  }
  else if(page_stage == ENABLE)
  {
    renderAdmin(1200, 0, 80, 80, 1);
    sprintf(posUpBuff, "ZGORNJA POZICIJA: %d mm", posUp);
    renderText(posUpBuff, smallText, blackColor);
    render(30, 160, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
    up_button(600, 150, &posUp, 1, 150);
    down_button(700, 150, &posUp, 1, 0);

    sprintf(posDownBuff, "SPODNJA POZICIJA: %d mm", posDown);
    renderText(posDownBuff, smallText, blackColor);
    render(30, 260, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
    up_button(600, 250, &posDown, 1, 150);
    down_button(700, 250, &posDown, 1, 0);
  }
  else if(page_stage == EXIT)
  {
    page_stage = ENTER;
  }
}
