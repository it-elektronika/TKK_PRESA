#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "main.h"

int init()    /* things needed to start sdl2 properly */
{
  int flags;
  int innited;
 
  flags = IMG_INIT_JPG|IMG_INIT_PNG;
  innited = IMG_Init(flags);
	
  if((SDL_Init(SDL_INIT_VIDEO||SDL_INIT_EVENTS)) != 0)
  {
    SDL_Log("Unable to initialize SDL:%s ", SDL_GetError());
    return 1;                                                                               
  }  

  window = SDL_CreateWindow("IT-Elektronika", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
   

  if(window == NULL)
  {
    return 1;
  }		  

  renderer = SDL_CreateRenderer(window, - 1, SDL_RENDERER_SOFTWARE);
  if(renderer == NULL)
  {
    ;
    /*printf("RENDERER IS NULL\n");*/
  }

  if((innited&flags) != flags)
  {
    
    printf("IMG_INIT: %s\n", IMG_GetError());
  }

  if(TTF_Init() != 0)
  {
    printf("TTF ERROR: %s\n", TTF_GetError());
  }

  #ifdef RPI
  smallText = TTF_OpenFont("/home/pi/TKK_PRESA/font/DejaVuSansMono.ttf", 30);
  if(smallText == NULL)
  {
    printf("NO FONT FOUND:%s\n", TTF_GetError());
  }
  regularText = TTF_OpenFont("/home/pi/TKK_PRESA/font/DejaVuSansMono.ttf", 45);
  if(regularText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  #endif
  #ifdef LUKA
  smallText = TTF_OpenFont("/home/luka/TKK_PRESA_/font/DejaVuSansMono.ttf", 30);
  if(smallText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  regularText = TTF_OpenFont("/home/luka/TKK_PRESA_/font/DejaVuSansMono.ttf", 45);
  if(regularText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  #endif

  return 15;
}


void initVars()
{
 /* color definitions  */
  whiteColor.r = 255;
  whiteColor.g = 255;
  whiteColor.b = 255;
  
  blackColor.r = 0;
  blackColor.g = 0;
  blackColor.b = 0;
}

void freeTexture(void)  
{
  if(texture != NULL)
  {
    SDL_DestroyTexture(texture);	  
    texture = NULL;
    textureWidth = 0;
    textureHeight = 0;
  }
}

void renderBackground(void)     
{
  switch(backgroundColor)
  {
    case 0:
      SDL_SetRenderDrawColor(renderer, 0, 178, 0, 255); /* green */
      break; 
    case 1:
      SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); /* yellow */
      break;
    case 2:
      SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); /* red */
      break;
  }
  SDL_RenderClear(renderer);
}

void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
  SDL_Rect renderQuad;
  renderQuad.x = x;
  renderQuad.y = y;
  renderQuad.w = textureWidth;
  renderQuad.h = textureHeight;

  if(clip != NULL)
  {
    renderQuad.w = clip -> w;
    renderQuad.h = clip -> h;
  }
  SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int renderText(const char *text, TTF_Font *textFont,  SDL_Color textColor)  
{
  SDL_Surface* textSurface;
  textSurface = TTF_RenderText_Solid(textFont, text, textColor);
  freeTexture();

  if(textSurface == NULL)
  {
    printf("Unable to render text surface! SDL Error: %s\n", SDL_GetError());
  }
  else
  {
    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(texture == NULL)
    {
      printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
      textureWidth = textSurface -> w;
      textureHeight = textSurface -> h;
    }
    SDL_FreeSurface(textSurface);
  }
  return texture != NULL;
}

void renderStatusBar()
{
  int i;
  int x1_1;
  int x1_2;
  int y1_1; 
  int y1_2;

  int x2_1;
  int x2_2;
  int y2_1; 
  int y2_2;

  int x3_1;
  int x3_2;
  int y3_1; 
  int y3_2;

  x1_1 = 0;
  y1_1 = 80;
  x1_2 = 1280;
  y1_2 = 80;

  x2_1 = 0;
  y2_1 = 0;
  x2_2 = 1280;
  y2_2 = 0;

  x3_1 = 0;
  y3_1 = 0;
  x3_2 = 0;
  y3_2 = 80;
 
  for(i = 0; i < 10; i++)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, x1_1, y1_1+i, x1_2, y1_2+i);
    SDL_RenderDrawLine(renderer, x2_1, y2_1, x2_2, y2_2);
    SDL_RenderDrawLine(renderer, x3_1, y3_1, x3_2, y3_2);
  }

  switch(sbarText)
  {
    case 0:
      renderText("STATUS", regularText, blackColor); 
      break;

    case 1:
      renderText("IZBIRANJE VELIKOSTI DOZE", regularText, blackColor);
      break;

    case 2:
      renderText("NAPAKA - ni povezave s krmilnikom", regularText, blackColor);
      break;

    case 3:
      renderText("GRID TEST", regularText, blackColor);
      break;
    
    case 4: 
      renderText("IZBIRA SMERI VRTENJA", regularText, blackColor);
      break;

    case 5: 
      renderText("IZBIRA NACINA DELOVANJA", regularText, blackColor);
      break;    

    case 6: 
      renderText("NASTAVITVE", regularText, blackColor);
      break;    
    
    case 7: 
      renderText("IZVIJAC IZVEN POZICIJE", regularText, blackColor);
      break;    
 
    case 8:
      renderText("SMET NA SENZORJU", regularText, blackColor);
      break;

    case 9:
      renderText("SENZORJI - IZVIJAC", regularText, blackColor);
      break;

    case 10:
      renderText("SENZORJI - SMET", regularText, blackColor);
      break;

    case 11:
      renderText("NAPAKA PREOBREMENITEV PRESE", regularText, blackColor);
      break;

    case 12:
      renderText("KOT ZAZNAVANJA", regularText, blackColor);
      break;
  
    case 13: 
      renderText("NAPAKA VARNOSTNA ZAVESA", regularText, blackColor);
      break;
    
    case 14:
      renderText("STOP TOTAL", regularText, blackColor);
      break;

    case 15:
      renderText("NAPAKA DRIVERJA MOTORJA", regularText, blackColor);
      break;

    case 16:
      renderText("NAPAKA SKLOPKE", regularText, blackColor);
      break;

    case 17:
      renderText("NAPAKA POZICIJE", regularText, blackColor);
      break;
    
    case 18:
      renderText("NAPAKA OLJE", regularText, blackColor);
      break;

    case 19:
      renderText("NAPAKA ZRAK", regularText, blackColor);
      break;

    case 20:
      renderText("NAPAKA HORIZONTALNI POMIK", regularText, blackColor);
      break;

    case 21:
      renderText("NAPAKA VERTIKALNI POMIK", regularText, blackColor);
      break;
   
    case 22:
      renderText("USTAVLJANJE MOTORJA", regularText, blackColor);
      break;
  } 
  render(30, 10, NULL, 0.0, NULL, SDL_FLIP_NONE);
}

void renderContent()
{
  switch(page)
  {
    case 0:
      pageOne(); /* main page */
      backgroundColor = 1;
      sbarText = 0;
      break;
    
    case 1:
      pageTwo(); /* can size selection */
      backgroundColor = 1;
      sbarText = 1;
      break;
   
    case 2:
      pageThree();   /*error page */
      backgroundColor = 2;
      sbarText = 2;
      break;
  }
  oldtimestamp=timestamp;
  cycleCounter++;
}

void touchUpdate()   /* handling touch events */
{
  while(SDL_PollEvent(&event) != 0 )
  {
    #ifdef RPI
    if(event.type == SDL_FINGERDOWN)  
    {
      timestamp = event.tfinger.timestamp;
      touchLocation.x = event.tfinger.x;
      touchLocation.y = event.tfinger.y;
    }
    #endif
    #ifdef LUKA
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      timestamp = event.button.timestamp;
      touchLocation.x = event.button.x;
      touchLocation.y = event.button.y;
    }
    #endif
  }  
}



void saveButton(int x, int y, int w, int h, char *text)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    for(i = 0; i < 10; i++)
    {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderDrawLine(renderer, x, y+i, (x+w), y+i);
      SDL_RenderDrawLine(renderer, (x+w+i), y, (x+w+i), (y+h)); 
      SDL_RenderDrawLine(renderer, (x+w), (y+h-i), x, (y+h-i));
      SDL_RenderDrawLine(renderer, x+i, (y+h), x+i, y);
    }

    #ifdef RPI   
    fp_can_size = fopen("/home/pi/TKK_PRESA/data/can_size.txt", "w");
    #endif
    #ifdef LUKA
    fp_can_size = fopen("/home/luka/TKK_PRESA_/data/can_size.txt", "w");
    #endif
    posCounter = 0;
    /* writing position values to AKD registers and saving values to file */
    if(selected[0])
    {
      for(i = 0; i < 2; ++i)
      {
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
        * clear9 = posCounter;           
 
        FD_ZERO(&fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
    
        x = select(32, NULL, &fds, NULL, &tv);
        x = send(s, obufCl, 17, 0);
        printf("Message Sent!\n");
        FD_SET(s, &fds);
        x = select(32, &fds, NULL, NULL, &tv);
        x = recv(s, ibufCl, 50 , 0);
        transId++;
        posCounter++;
      }
  
      int * posOneA1 = (int*)(&obufOneA[0]);
      int * posOneA2 = (int*)(&obufOneA[2]);
      int * posOneA3 = (int*)(&obufOneA[4]);
      int * posOneA4 = (int*)(&obufOneA[6]);
      int * posOneA5 = (int*)(&obufOneA[7]);
      int * posOneA6 = (int*)(&obufOneA[8]);
      int * posOneA7 = (int*)(&obufOneA[10]);
      int * posOneA8 = (int*)(&obufOneA[12]);
      int * posOneA9 =  (int*)(&obufOneA[16]);
      int * posOneA10 = (int*)(&obufOneA[17]);    
      int * posOneA11 = (int*)(&obufOneA[21]);
      int * posOneA12 = (int*)(&obufOneA[28]);
      int * posOneA13 = (int*)(&obufOneA[29]);
      int * posOneA14 = (int*)(&obufOneA[33]);
      int * posOneA15 = (int*)(&obufOneA[40]);
      int * posOneA16 = (int*)(&obufOneA[44]);
      int * posOneA17 = (int*)(&obufOneA[48]);
      int * posOneA18 = (int*)(&obufOneA[52]);
      
      memset(obufOneA, 0, 58);
      * posOneA1 = transId;   
      * posOneA2 = htons(0);
      * posOneA3 = htons(47);
      * posOneA4 = 1;
      * posOneA5 = 16;
      * posOneA6 = htons(8192);
      * posOneA7 = htons(20);
      * posOneA8 = 40;
      * posOneA9 = 0;                 
      * posOneA10 = htonl(1000);  
      * posOneA11 = htonl(1000);   
      * posOneA12 = 16;           
      * posOneA13 = htonl(1000);  
      * posOneA14 = htonl(1000);  
      * posOneA15 = 1;            
      * posOneA16 = 0;            
      * posOneA17 = 1;            
      * posOneA18 = 1;  

      FD_ZERO(&fds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      x = select(32, NULL, &fds, NULL, &tv);
      x = send(s, obufOneA, 53, 0);
      printf("Message Sent!\n");
      FD_SET(s, &fds);
      x = select(32, &fds, NULL, NULL, &tv);
      x = recv(s, ibufOneA, 50 , 0);

      int * posOneB1 = (int*)(&obufOneB[0]);
      int * posOneB2 = (int*)(&obufOneB[2]);
      int * posOneB3 = (int*)(&obufOneB[4]);
      int * posOneB4 = (int*)(&obufOneB[6]);
      int * posOneB5 = (int*)(&obufOneB[7]);
      int * posOneB6 = (int*)(&obufOneB[8]);
      int * posOneB7 = (int*)(&obufOneB[10]);
      int * posOneB8 = (int*)(&obufOneB[12]);
      int * posOneB9 =  (int*)(&obufOneB[16]);
      int * posOneB10 = (int*)(&obufOneB[17]);    
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
      * posOneB9 = 1;                 
      * posOneB10 = htonl(10000);  
      * posOneB11 = htonl(10000);   
      * posOneB12 = 16;           
      * posOneB13 = htonl(10000);  
      * posOneB14 = htonl(10000);  
      * posOneB15 = 2;            
      * posOneB16 = 0;            
      * posOneB17 = 1;            
      * posOneB18 = 1;  
 
      FD_ZERO(&fds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      x = select(32, NULL, &fds, NULL, &tv);
      x = send(s, obufOneB, 53, 0);
      printf("Message Sent!\n");
      FD_SET(s, &fds);
      x = select(32, &fds, NULL, NULL, &tv);
      x = recv(s, ibufOneB, 50 , 0);

      fprintf(fp_can_size, "%d\n", 0);
    }
    else if(selected[1])
    {
      for(i = 0; i < 2; ++i)
      {
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
        * clear9 = posCounter;           
 
        FD_ZERO(&fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
    
        x = select(32, NULL, &fds, NULL, &tv);
        x = send(s, obufCl, 17, 0);
        printf("Message Sent!\n");
        FD_SET(s, &fds);
        x = select(32, &fds, NULL, NULL, &tv);
        x = recv(s, ibufCl, 50 , 0);
        transId++;
        posCounter++;
      }
  
      int * posTwoA1 = (int*)(&obufTwoA[0]);
      int * posTwoA2 = (int*)(&obufTwoA[2]);
      int * posTwoA3 = (int*)(&obufTwoA[4]);
      int * posTwoA4 = (int*)(&obufTwoA[6]);
      int * posTwoA5 = (int*)(&obufTwoA[7]);
      int * posTwoA6 = (int*)(&obufTwoA[8]);
      int * posTwoA7 = (int*)(&obufTwoA[10]);
      int * posTwoA8 = (int*)(&obufTwoA[12]);
      int * posTwoA9 =  (int*)(&obufTwoA[16]);
      int * posTwoA10 = (int*)(&obufTwoA[17]);    
      int * posTwoA11 = (int*)(&obufTwoA[21]);
      int * posTwoA12 = (int*)(&obufTwoA[28]);
      int * posTwoA13 = (int*)(&obufTwoA[29]);
      int * posTwoA14 = (int*)(&obufTwoA[33]);
      int * posTwoA15 = (int*)(&obufTwoA[40]);
      int * posTwoA16 = (int*)(&obufTwoA[44]);
      int * posTwoA17 = (int*)(&obufTwoA[48]);
      int * posTwoA18 = (int*)(&obufTwoA[52]);
      
      memset(obufTwoA, 0, 58);
      * posTwoA1 = transId;   
      * posTwoA2 = htons(0);
      * posTwoA3 = htons(47);
      * posTwoA4 = 1;
      * posTwoA5 = 16;
      * posTwoA6 = htons(8192);
      * posTwoA7 = htons(20);
      * posTwoA8 = 40;
      * posTwoA9 = 0;                 
      * posTwoA10 = htonl(2000);  
      * posTwoA11 = htonl(2000);   
      * posTwoA12 = 16;           
      * posTwoA13 = htonl(2000);  
      * posTwoA14 = htonl(2000);  
      * posTwoA15 = 1;            
      * posTwoA16 = 0;            
      * posTwoA17 = 1;            
      * posTwoA18 = 1;  
 
      FD_ZERO(&fds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      x = select(32, NULL, &fds, NULL, &tv);
      x = send(s, obufTwoA, 53, 0);
      printf("Message Sent!\n");
      FD_SET(s, &fds);
      x = select(32, &fds, NULL, NULL, &tv);
      x = recv(s, ibufTwoA, 50 , 0);

      int * posTwoB1 = (int*)(&obufTwoB[0]);
      int * posTwoB2 = (int*)(&obufTwoB[2]);
      int * posTwoB3 = (int*)(&obufTwoB[4]);
      int * posTwoB4 = (int*)(&obufTwoB[6]);
      int * posTwoB5 = (int*)(&obufTwoB[7]);
      int * posTwoB6 = (int*)(&obufTwoB[8]);
      int * posTwoB7 = (int*)(&obufTwoB[10]);
      int * posTwoB8 = (int*)(&obufTwoB[12]);
      int * posTwoB9 =  (int*)(&obufTwoB[16]);
      int * posTwoB10 = (int*)(&obufTwoB[17]);    
      int * posTwoB11 = (int*)(&obufTwoB[21]);
      int * posTwoB12 = (int*)(&obufTwoB[28]);
      int * posTwoB13 = (int*)(&obufTwoB[29]);
      int * posTwoB14 = (int*)(&obufTwoB[33]);
      int * posTwoB15 = (int*)(&obufTwoB[40]);
      int * posTwoB16 = (int*)(&obufTwoB[44]);
      int * posTwoB17 = (int*)(&obufTwoB[48]);
      int * posTwoB18 = (int*)(&obufTwoB[52]);
      
      memset(obufTwoB, 0, 58);
      * posTwoB1 = transId;   
      * posTwoB2 = htons(0);
      * posTwoB3 = htons(47);
      * posTwoB4 = 1;
      * posTwoB5 = 16;
      * posTwoB6 = htons(8192);
      * posTwoB7 = htons(20);
      * posTwoB8 = 40;
      * posTwoB9 = 1;                 
      * posTwoB10 = htonl(20000);  
      * posTwoB11 = htonl(20000);   
      * posTwoB12 = 16;           
      * posTwoB13 = htonl(20000);  
      * posTwoB14 = htonl(20000);  
      * posTwoB15 = 2;            
      * posTwoB16 = 0;            
      * posTwoB17 = 1;            
      * posTwoB18 = 1;  

      FD_ZERO(&fds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      x = select(32, NULL, &fds, NULL, &tv);
      x = send(s, obufTwoB, 53, 0);
      printf("Message Sent!\n");
      FD_SET(s, &fds);
      x = select(32, &fds, NULL, NULL, &tv);
      x = recv(s, ibufTwoB, 50 , 0);

      fprintf(fp_can_size, "%d\n", 1);   
    }  
    else if(selected[2])
    {  
      for(i = 0; i < 2; ++i)
      {
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
        * clear9 = posCounter;           

        FD_ZERO(&fds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
    
        x = select(32, NULL, &fds, NULL, &tv);
        x = send(s, obufCl, 17, 0);
        printf("Message Sent!\n");
        FD_SET(s, &fds);
        x = select(32, &fds, NULL, NULL, &tv);
        x = recv(s, ibufCl, 50 , 0);
        transId++;
        posCounter++;
      }
        
      int * posThreeA1 = (int*)(&obufThreeA[0]);
      int * posThreeA2 = (int*)(&obufThreeA[2]);
      int * posThreeA3 = (int*)(&obufThreeA[4]);
      int * posThreeA4 = (int*)(&obufThreeA[6]);
      int * posThreeA5 = (int*)(&obufThreeA[7]);
      int * posThreeA6 = (int*)(&obufThreeA[8]);
      int * posThreeA7 = (int*)(&obufThreeA[10]);
      int * posThreeA8 = (int*)(&obufThreeA[12]);
      int * posThreeA9 =  (int*)(&obufThreeA[16]);
      int * posThreeA10 = (int*)(&obufThreeA[17]);    
      int * posThreeA11 = (int*)(&obufThreeA[21]);
      int * posThreeA12 = (int*)(&obufThreeA[28]);
      int * posThreeA13 = (int*)(&obufThreeA[29]);
      int * posThreeA14 = (int*)(&obufThreeA[33]);
      int * posThreeA15 = (int*)(&obufThreeA[40]);
      int * posThreeA16 = (int*)(&obufThreeA[44]);
      int * posThreeA17 = (int*)(&obufThreeA[48]);
      int * posThreeA18 = (int*)(&obufThreeA[52]);
      
      memset(obufThreeA, 0, 58);
      * posThreeA1 = transId;   
      * posThreeA2 = htons(0);
      * posThreeA3 = htons(47);
      * posThreeA4 = 1;
      * posThreeA5 = 16;
      * posThreeA6 = htons(8192);
      * posThreeA7 = htons(20);
      * posThreeA8 = 40;
      * posThreeA9 = 0;                 
      * posThreeA10 = htonl(3000);  
      * posThreeA11 = htonl(3000);   
      * posThreeA12 = 16;           
      * posThreeA13 = htonl(3000);  
      * posThreeA14 = htonl(3000);  
      * posThreeA15 = 1;            
      * posThreeA16 = 0;            
      * posThreeA17 = 1;            
      * posThreeA18 = 1;  

      FD_ZERO(&fds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      x = select(32, NULL, &fds, NULL, &tv);
      x = send(s, obufThreeA, 53, 0);
      printf("Message Sent!\n");
      FD_SET(s, &fds);
      x = select(32, &fds, NULL, NULL, &tv);
      x = recv(s, ibufThreeA, 50 , 0);

      int * posThreeB1 = (int*)(&obufThreeB[0]);
      int * posThreeB2 = (int*)(&obufThreeB[2]);
      int * posThreeB3 = (int*)(&obufThreeB[4]);
      int * posThreeB4 = (int*)(&obufThreeB[6]);
      int * posThreeB5 = (int*)(&obufThreeB[7]);
      int * posThreeB6 = (int*)(&obufThreeB[8]);
      int * posThreeB7 = (int*)(&obufThreeB[10]);
      int * posThreeB8 = (int*)(&obufThreeB[12]);
      int * posThreeB9 =  (int*)(&obufThreeB[16]);
      int * posThreeB10 = (int*)(&obufThreeB[17]);    
      int * posThreeB11 = (int*)(&obufThreeB[21]);
      int * posThreeB12 = (int*)(&obufThreeB[28]);
      int * posThreeB13 = (int*)(&obufThreeB[29]);
      int * posThreeB14 = (int*)(&obufThreeB[33]);
      int * posThreeB15 = (int*)(&obufThreeB[40]);
      int * posThreeB16 = (int*)(&obufThreeB[44]);
      int * posThreeB17 = (int*)(&obufThreeB[48]);
      int * posThreeB18 = (int*)(&obufThreeB[52]);
      
      memset(obufThreeB, 0, 58);
      * posThreeB1 = transId;   
      * posThreeB2 = htons(0);
      * posThreeB3 = htons(47);
      * posThreeB4 = 1;
      * posThreeB5 = 16;
      * posThreeB6 = htons(8192);
      * posThreeB7 = htons(20);
      * posThreeB8 = 40;
      * posThreeB9 = 1;                 
      * posThreeB10 = htonl(30000);  
      * posThreeB11 = htonl(30000);   
      * posThreeB12 = 16;           
      * posThreeB13 = htonl(30000);  
      * posThreeB14 = htonl(30000);  
      * posThreeB15 = 2;            
      * posThreeB16 = 0;            
      * posThreeB17 = 1;            
      * posThreeB18 = 1;  

      FD_ZERO(&fds);
      tv.tv_sec = 0;
      tv.tv_usec = 0;
    
      x = select(32, NULL, &fds, NULL, &tv);
      x = send(s, obufThreeB, 53, 0);
      printf("Message sent!\n");
      FD_SET(s, &fds);
      x = select(32, &fds, NULL, NULL, &tv);
      x = recv(s, ibufThreeB, 50 , 0);
   
      fprintf(fp_can_size, "%d\n", 2);
    }
    fclose(fp_can_size);

  }
  renderText(text, smallText,  blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
}

void renderAdmin(int x, int y, int w, int h, int curr_page, int gotoNum) 
{
  int i;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  for(i = 0; i < 5; ++i)
  {
    SDL_RenderDrawLine(renderer, x, y+i, (x+w), y+i);
    SDL_RenderDrawLine(renderer, (x+w+i), y, (x+w+i), (y+h)); 
  
    SDL_RenderDrawLine(renderer, x+i, (y+h), x+i, y);
  }
  renderText("...", regularText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2+10)), NULL, 0.0, NULL, SDL_FLIP_NONE); 

  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp && cycleCounter != cycleCheck)
  {
    cycleCheck = cycleCounter;
    page = gotoNum;
    page_stage[curr_page] = 2;
  }
}

void up_button(int x,  int y, int *incrementee, int incrementor)   
{
  SDL_Surface *imageSurface;
  freeTexture();
  #ifdef RPI
  imageSurface = IMG_Load("/home/pi/TKK_PRESA/images/up_black.png");
  #endif
  #ifdef LUKA
  imageSurface = IMG_Load("/home/luka/TKK_PRESA_/images/up_black.png");
  #endif
  if(imageSurface == NULL)
  {
    printf("Unable to render image surface! SDL_ImageError: %s\n", IMG_GetError());
  }
  else
  {
    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(texture == NULL)
    {
      printf("Unable to create texture from rendered image! SDL_ImageError: %s\n", SDL_GetError());
    }
    else
    {
      textureWidth = imageSurface -> w;
      textureHeight = imageSurface -> h;
    }
    SDL_FreeSurface(imageSurface);
  }

  render(x, y, NULL, 0.0, NULL, SDL_FLIP_NONE);

  if(touchLocation.x > x && touchLocation.x < x+imageSurface->w && touchLocation.y > y && touchLocation.y < y + imageSurface->h && timestamp > oldtimestamp)
  {
    incrementee = incrementee + incrementor;
  }
}

void down_button(int x, int y, int *decrementee, int decrementor)     
{
  SDL_Surface *imageSurface;
  freeTexture();
  #ifdef RPI
  imageSurface = IMG_Load("/home/pi/TKK_PRESA/images/down_black.png");
  #endif
  #ifdef LUKA
  imageSurface = IMG_Load("/home/luka/TKK_PRESA_/images/down_black.png");
  #endif
  if(imageSurface == NULL)
  {
    printf("Unable to render image surface! SDL_ImageError: %s\n", IMG_GetError());
  }
  else
  {
    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(texture == NULL)
    {
      printf("Unable to create texture from rendered image! SDL_ImageError: %s\n", SDL_GetError());
    }
    else
    {
      textureWidth = imageSurface -> w;
      textureHeight = imageSurface -> h;
    }
    SDL_FreeSurface(imageSurface);
  }	
  render(x, y, NULL, 0.0, NULL, SDL_FLIP_NONE);

  if(touchLocation.x > x && touchLocation.x < x+imageSurface->w && touchLocation.y > y && touchLocation.y < y + imageSurface->h && timestamp > oldtimestamp)
  {
    decrementee = decrementee - decrementor;
  }
}

void left_button(int x,  int y)   
{
  SDL_Surface *imageSurface;
  freeTexture();
  #ifdef RPI
  imageSurface = IMG_Load("/home/pi/TKK_PRESA/images/left_200.png");
  #endif
  #ifdef LUKA
  imageSurface = IMG_Load("/home/luka/TKK_PRESA_/images/left_200.png");
  #endif
  
  if(imageSurface == NULL)
  {
    printf("Unable to render image surface! SDL_ImageError: %s\n", IMG_GetError());
  }
  else
  {
    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(texture == NULL)
    {
      printf("Unable to create texture from rendered image! SDL_ImageError: %s\n", SDL_GetError());
    }
    else
    {
      textureWidth = imageSurface -> w;
      textureHeight = imageSurface -> h;
    }
    SDL_FreeSurface(imageSurface);
  }

  render(x, y, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
  if(touchLocation.x > x && touchLocation.x < x+imageSurface->w && touchLocation.y > y && touchLocation.y < y + imageSurface->h && timestamp > oldtimestamp)
  {
    ;
  }
}

void right_button(int x,  int y)   
{
  SDL_Surface *imageSurface;
  freeTexture();
  #ifdef RPI
  imageSurface = IMG_Load("/home/pi/TKK_PRESA/images/right_200.png");
  #endif
  #ifdef LUKA
  imageSurface = IMG_Load("/home/luka/TKK_PRESA_/images/right_200.png");
  #endif
  
  if(imageSurface == NULL)
  {
    printf("Unable to render image surface! SDL_ImageError: %s\n", IMG_GetError());
  }
  else
  {
    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    if(texture == NULL)
    {
      printf("Unable to create texture from rendered image! SDL_ImageError: %s\n", SDL_GetError());
    }
    else
    {
      textureWidth = imageSurface -> w;
      textureHeight = imageSurface -> h;
    }
    SDL_FreeSurface(imageSurface);
  }

  render(x, y, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
  if(touchLocation.x > x && touchLocation.x < x+imageSurface->w && touchLocation.y > y && touchLocation.y < y + imageSurface->h && timestamp > oldtimestamp)
  {
    ;
  }
}

void button(int x, int y, int w, int h, char *text, int id)  
{
  int i;
  if(selected[id]==0)
  {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderDrawLine(renderer, x, y, (x+w), y);
    SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
    SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
    SDL_RenderDrawLine(renderer, x, (y+h), x, y);
    renderText(text, smallText,  blackColor);
    render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
  }
  else if(selected[id]==1)
  {
    for(i = 0; i < 10; i++)
    {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
      SDL_RenderDrawLine(renderer, x, y+i, (x+w), y+i);
      SDL_RenderDrawLine(renderer, (x+w+i), y, (x+w+i), (y+h)); 
      SDL_RenderDrawLine(renderer, (x+w), (y+h-i), x, (y+h-i));
      SDL_RenderDrawLine(renderer, x+i, (y+h), x+i, y);
    }
    renderText(text, smallText,  blackColor);
    render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE);
  }
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp && selected[id] == 0)
  {
    selected[0] = 0;
    selected[1] = 0;
    selected[2] = 0;
    selected[id] = 1;
  }
}
