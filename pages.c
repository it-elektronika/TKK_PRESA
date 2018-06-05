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
    #ifdef PI   
    fp_can_size = fopen("/home/pi/TKK_PRESA/data/can_size.txt", "r");
    #endif
    #ifdef LUKA
    fp_can_size = fopen("/home/luka/TKK_PRESA/data/can_size.txt", "r");
    #endif

    for(i = 0; i < 1; ++i)
    {
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
    renderAdmin(1200, 700, 80, 80, 1, 3);
    button(200, 200, 200, 100, "MALA", 0);
    button(200, 400, 200, 100, "SREDNJA", 1);
    button(200, 600, 200, 100, "VELIKA", 2);
  }
  if(page_stage[1] == 2)
  {
    #ifdef PI   
    fp_can_size = fopen("/home/pi/TKK_PRESA/data/can_size.txt", "w");
    #endif
    #ifdef LUKA
    fp_can_size = fopen("/home/luka/TKK_PRESA/data/can_size.txt", "w");
    #endif
    
    if(selected[0])
    {
      fprintf(fp_can_size, "%d\n", 0);
    }
    else if(selected[1])
    {
      fprintf(fp_can_size, "%d\n", 1);   
    }  
    else if(selected[2])
    {  
      fprintf(fp_can_size, "%d\n", 2);
    }
    fclose(fp_can_size);

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
    renderAdmin(1200, 0, 80, 80, 1, 0);
  }
  else if(page_stage[2] == 2)
  {
    page_stage[2] = 0;
  }
}

void pageFour()
{
  char * column_names[3];
 /*int cell_edit[3];*/

  column_names[0] = "prvi";
  column_names[1] = "drugi";
  column_names[2] = "tretji";
/*
  cell_values[0] = 10;
  cell_values[1] = 20;
  cell_values[2] = 30;
*/
  if(page_stage[3] == 0)
  {
    page_stage[3] = 1;
  }
  else if(page_stage[3] == 1)
  {
    grid(500, 200, 100, 100, 3, 3, column_names, cell_values);
    renderAdmin(1200, 0, 80, 80, 1, 0);
  }
  else if(page_stage[3] == 2)
  {
    page_stage[3] = 0;
  }
}

void pageFive()
{
  if(page_stage[4] == 0)
  {
    sprintf(editText,"%s", cell_values_buff[idBuff]);
    printf("%s:et  %d:ib \n", editText, idBuff);
    page_stage[4] = 1;
  }
  else if(page_stage[4] == 1)
  {
    renderText(editText, regularText, blackColor);
    render(100, 100, NULL, 0.0, NULL, SDL_FLIP_NONE);
    keypad();
  }
  else if(page_stage[4] == 2)
  {
    printf("%s %d\n", editText, idBuff);
    cell_values[idBuff] = atoi(editText);
    page_stage[4] = 0;
    page = 3;
  }
}
