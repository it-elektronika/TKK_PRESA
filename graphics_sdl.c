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

  window = SDL_CreateWindow("IT-Elektronika", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_BORDERLESS);
  
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
  smallText = TTF_OpenFont("/home/luka/TKK_PRESA/font/DejaVuSansMono.ttf", 30);
  if(smallText == NULL)
  {
    printf("NO FONT FOUND\n");
  }
  regularText = TTF_OpenFont("/home/luka/TKK_PRESA/font/DejaVuSansMono.ttf", 45);
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

void up_button(int x,  int y, int *incrementee, int incrementor)   
{
  SDL_Surface *imageSurface;
  freeTexture();
  #ifdef RPI
  imageSurface = IMG_Load("/home/pi/TKK_PRESA/images/up_black.png");
  #endif
  #ifdef LUKA
  imageSurface = IMG_Load("/home/luka/TKK_PRESA/images/up_black.png");
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
  imageSurface = IMG_Load("/home/luka/TKK_PRESA/images/down_black.png");
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
  imageSurface = IMG_Load("/home/luka/TKK_PRESA/images/left_200.png");
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
  imageSurface = IMG_Load("/home/luka/TKK_PRESA/images/right_200.png");
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
    fp_can_size = fopen("/home/luka/TKK_PRESA/data/can_size.txt", "w");
    #endif

    /* writing position values to AKD registers and saving values to file */
    if(selected[0])
    {
      fprintf(fp_can_size, "%d\n", 0);
      nb = sizeof(regsSmall)/sizeof(int16_t); 
      tc = modbus_write_registers(ctx, 1, nb, regsSmall);
    }
    else if(selected[1])
    {
      fprintf(fp_can_size, "%d\n", 1);   
      nb = sizeof(regsMedium)/sizeof(int16_t);
      tc = modbus_write_registers(ctx, 1, nb, regsMedium);
    }  
    else if(selected[2])
    {  
      fprintf(fp_can_size, "%d\n", 2);
      nb = sizeof(regsLarge)/sizeof(int16_t); 
      tc = modbus_write_registers(ctx, 1, nb, regsLarge);
    }
    fclose(fp_can_size);
    printf("NB:%d\n", bb);

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


