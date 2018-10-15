#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "graphics_sdl.h"
#include "main.h"
#include <unistd.h>
#include <time.h>

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
    printf("RENDERER IS NULL\n");
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
    printf("STEP: %d\n", step);
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
 
  for(i = 0; i < 10; ++i)
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
      renderText("MENU", regularText, blackColor);
      break;
    
    case 2:
      renderText("IZBIRA VELIKOSTI DOZE", regularText, blackColor);
      break;
    
    case 3:
      renderText("I / O STATUS", regularText, blackColor);
      break;

    case 4: 
      renderText("DIAGNOSTIKA", regularText, blackColor);
      break;

    case 5: 
      renderText("NASTAVLJANJE CASA", regularText, blackColor);
      break;    

    case 6: 
      renderText("POVEZOVANJE", regularText, blackColor);
      break;    
    
    case 7: 
      renderText("NAPAKA - povezovanje", regularText, blackColor);
      break;    
 
    case 8:
      renderText("NAPAKA - ", regularText, blackColor);
      break;

    case 9:
      renderText("POZICIJE", regularText, blackColor);
      break;

    case 10:
      renderText("ROCNO NASTAVLJANJE", regularText, blackColor);
      break;

    case 11:
      renderText("DRIVE ROCNO ", regularText, blackColor);
      break;

    case 12:
      renderText("UREJEVALNIK", regularText, blackColor);
      break;
  
    case 13: 
      renderText("NAPAKA -", regularText, blackColor);
      break;
    
    case 14:
      renderText("NAPAKA -", regularText, blackColor);
      break;

    case 15:
      renderText("NAPAKA -", regularText, blackColor);
      break;

    case 16:
      renderText("NAPAKA -", regularText, blackColor);
      break;

    case 17:
      renderText("NAPAKA -", regularText, blackColor);
      break;
    
    case 18:
      renderText("NAPAKA -", regularText, blackColor);
      break;

    case 19:
      renderText("NAPAKA -", regularText, blackColor);
      break;

    case 20:
      renderText("NAPAKA -", regularText, blackColor);
      break;

    case 21:
      renderText("NAPAKA -", regularText, blackColor);
      break;
   
    case 22:
      renderText("NAPAKA -", regularText, blackColor);
      break;
  } 
  render(30, 10, NULL, 0.0, NULL, SDL_FLIP_NONE);
  clockButton(1050, 20, 50, 100, tmBuff); 
}

void renderContent()
{
  switch(page)
  {
    case 0:
      pageZero(); /* main - landing page */
      backgroundColor = 1;
      sbarText = 0;
      break;
    
    case 1:
      pageOne(); /* menu */
      backgroundColor = 1;
      sbarText = 1;
      break;
   
    case 2:
      pageTwo();   /* can size */
      backgroundColor = 1;
      sbarText = 2;
      break;
    
    case 3:
      pageThree();   /*i/o status */
      backgroundColor = 1;
      sbarText = 3;
      break;
    
    case 4:
      pageFour();  /* diagnostics */
      backgroundColor = 1;
      sbarText = 4;
      break;

    case 5:
      pageFive();  /* clock */
      backgroundColor = 1;
      sbarText = 5;
      break;

    case 6:  
      pageSix();  /* connecting */
      backgroundColor = 1;
      sbarText = 6;
      break;

    case 7:
      pageSeven(); /* error connecting */
      backgroundColor = 2;
      sbarText = 7;
      break;

    case 8:
      pageEight(); /* error */
      backgroundColor = 2;
      sbarText = 8;
      break;
    
    case 9:
      pageNine();
      backgroundColor = 1;
      sbarText = 9;
      break;
    
    case 10:  
      pageTen();
      backgroundColor = 1;
      sbarText = 10;
      break;

    case 11:
      pageEleven();
      backgroundColor = 1;
      sbarText = 11;
      break;
   
    case 12:
      pageTwelve();
      backgroundColor = 1;
      sbarText = 12;
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
    if(event.type == SDL_KEYDOWN)
    {
      if(event.key.keysym.sym == SDLK_ESCAPE)
      {
        program = 0;        
      }
    }
    #endif
    #ifdef LUKA
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
      timestamp = event.button.timestamp;
      touchLocation.x = event.button.x;
      touchLocation.y = event.button.y;
    }
    if(event.type == SDL_KEYDOWN)
    {
      if(event.key.keysym.sym == SDLK_ESCAPE)
      {
        program = 0;        
      }
      
    }
    #endif
  }  
}

void saveButton(int x, int y, int w, int h, char *text) /* sending values to AKD drive */
{
  int i;
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    for(i = 0; i < 10; ++i)
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
    //int * clear1 =  (int*)(&obufCl[0]);
    //int * clear9 =  (int*)(&obufCl[16]);
    //int * posOneB1 = (int*)(&obufOneB[0]);
    //int * posOneB9 =  (int*)(&obufOneB[16]);
    //int * posOneB10 = (int*)(&obufOneB[17]);
    int * moveTask1 =  (int*)(&obufMT[0]); 
    int * moveTask9 =  (int*)(&obufMT[13]);
    int * moveTask1Next =  (int*)(&obufMTN[0]); 
    int * moveTask9Next =  (int*)(&obufMTN[13]);
    int * drvSave1 = (int*)(&obufDS[0]);
 
    * moveTask1 = transId;
    if(selected[0])
    {
      * moveTask9 = htonl(1000);                
      * moveTask9Next = htonl(2000);
      fprintf(fp_can_size, "%d\n", 0);   
      selectedCan = 0;
    }
    else if(selected[1])
    {
      * moveTask9 = htonl(3000);
      * moveTask9Next = htonl(4000);
      fprintf(fp_can_size, "%d\n", 1);
      selectedCan = 1;
    }
    else if(selected[2])
    {
     * moveTask9 = htonl(5000);
     * moveTask9Next = htonl(6000);     
     fprintf(fp_can_size, "%d\n", 2); 
     selectedCan = 2;               
    }
    else if(selected[3])
    {
      * moveTask9 = htonl(7000);
      * moveTask9Next = htonl(8000); 
      fprintf(fp_can_size, "%d\n", 3); 
      selectedCan = 3;            
    }

    /*
    FD_ZERO(&fds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
  
    conn_presa = select(32, NULL, &fds, NULL, &tv);
    conn_presa = send(s, obufMT, 17, 0);
    printf("Message Sent! - motion task 1 - press\n");
    FD_SET(s, &fds);
    conn_presa = select(32, &fds, NULL, NULL, &tv);
    conn_presa = recv(s, ibufMT, 50 , 0);
    transId++;
    */

    sendModbus(s, obufMT, 17, ibufMT, 50, "motion task 1 - press");
    * moveTask1Next = transId;
   
    sendModbus(s, obufMTN, 17, ibufMTN, 50, "motion task - press");    
    * drvSave1 = transId;
    
    sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive");

    fclose(fp_can_size);
  }
  renderText(text, smallText,  blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
}

void renderAdmin(int x, int y, int w, int h, int gotoNum) 
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
    page_stage = EXIT;
  }
}

void up_button(int x,  int y, int *incrementee, int incrementor, int max)   
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
    if(*incrementee < max)
    {
      *incrementee = *incrementee + incrementor;
    }
  }
}

void down_button(int x, int y, int *decrementee, int decrementor, int min)     
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
    if(*decrementee > min)
    {
      *decrementee = *decrementee - decrementor;
    }
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
    for(i = 0; i < 10; ++i)
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
    selected[3] = 0;
    selected[id] = 1;
  }
}

void goToButton(int x, int y, int w, int h, char *text, int goToNum)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);
  renderText(text, regularText,  blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
 
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    cycleCheck = cycleCounter;
    page = goToNum;
    page_stage = EXIT;
  }
}


void saveTime(int x, int y, int w, int h, char *text)
{
  renderText(text, smallText,  blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE);
  
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    sprintf(setTBuff, "echo ine36dun2f1 | sudo -S timedatectl set-time '%04d-%02d-%02d %02d:%02d:00'", year, month, day, hour, minute);
    system("echo ine36dun2f1 | sudo -S timedatectl set-ntp 0");
    system(setTBuff);
    system("echo ine36dun2f1 | sudo -S timedatectl set-ntp 1");
  } 
}

void clockButton(int x, int y, int h, int w, char *tmBuff)
{

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(tmBuff, "%02d:%02d", tm.tm_hour, tm.tm_min);
  renderText(tmBuff, smallText, blackColor);
  render(1050, 23, NULL, 0.0, NULL, SDL_FLIP_NONE);
  
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    page = 5;
    page_stage = ENTER;
  }
}

void outputButton(int x, int y, int w, int h, int id)
{
  sprintf(buff_outputs_val[id], "%s: %s",buff_outputs[id], outputs[id]);
  renderText(buff_outputs_val[id], regularText, blackColor);
  render(x, y, NULL, 0.0, NULL, SDL_FLIP_NONE);

  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    if(strcmp(outputs[id], "0") == 0)
    {
      outputButton1 = id+1;
      outputButton2 = 1;
    }
    else if(strcmp(outputs[id], "1") == 0)
    {
      outputButton1 = id+1;
      outputButton2 = 0;
    }
  }
  else
  {
    //outputButton1 = -1;
    //outputButton2 = -1;
  }
}

void start_button(int x, int y, int w, int h)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    if(step == 0)
    {
      startButton1 = 1;
    } 
  }
  else
  {
    startButton1 = 0;
  }
  renderText("START", regularText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
}

void stop_button(int x, int y, int w, int h)
{
   SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
   SDL_RenderDrawLine(renderer, x, y, (x+w), y);
   SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
   SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
   SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    stopButton1 = 1;
  }
  else
  {
    stopButton1 = 0;
  }
  renderText("STOP", regularText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
}

void continue_button(int x, int y, int w, int h, int stepMax)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    if(step > 0 && step < stepMax)
    {
      continueButton1 = 1;
    }
  }
  else
  { 
    continueButton1 = 0;
  }
  renderText("NADALJUJ", regularText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
}


void savePos(int x, int y, int w, int h)
{
  int i;
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

    posCounter = 0;

    /* writing position values to AKD registers and saving values to file */
    int * firstClear1 =  (int*)(&obufClFirst[0]);
    int * firstClear9 =  (int*)(&obufClFirst[16]);
    int * posOneA1 = (int*)(&obufOneA[0]);
    int * posOneA9 =  (int*)(&obufOneA[16]);
    int * posOneA10 = (int*)(&obufOneA[17]);
    int * drvSave1 = (int*)(&obufDS[0]);
   
    int * clear1 =  (int*)(&obufCl[0]);
    int * clear9 =  (int*)(&obufCl[16]);
    int * posOneB1 = (int*)(&obufOneB[0]);
    int * posOneB9 =  (int*)(&obufOneB[16]);
    int * posOneB10 = (int*)(&obufOneB[17]);
   

    /* small */
    * firstClear9 = 1;      
    * posOneA9 = 1;       
    * posOneA10 = htonl((firstPosSmall)*1000);
    * clear9 = 2;      
    * posOneB9 = 2;       
    * posOneB10 = htonl((AKD_frame_posSmall)*1000);

    * firstClear1 = transId;
    sendModbus(s, obufClFirst, 17, ibufClFirst, 50, "clear position - small");
	  
    * posOneA1 = transId;       
    sendModbus(s, obufOneA, 53, ibufOneA, 50, "position parameter - small");

    * clear1 = transId;
    sendModbus(s, obufCl, 17, ibufCl, 50, "clear position 2 - small");
  
    * posOneB1 = transId;       
    sendModbus(s, obufOneB, 53, ibufOneB, 50, "position parameter 2 - small");
    
    * drvSave1 = transId;
    sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive - small");


    /* small 2 */
    * firstClear9 = 3;      
    * posOneA9 = 3;       
    * posOneA10 = htonl((firstPosSmall2)*1000);
    * clear9 = 4;      
    * posOneB9 = 4;       
    * posOneB10 = htonl((AKD_frame_posSmall2)*1000);

    * firstClear1 = transId;
    sendModbus(s, obufClFirst, 17, ibufClFirst, 50, "clear position - small");
  
    * posOneA1 = transId;       
    sendModbus(s, obufOneA, 53, ibufOneA, 50, "position parameter - small");

    * clear1 = transId;
    sendModbus(s, obufCl, 17, ibufCl, 50, "clear position 2 - small");

    * posOneB1 = transId;       
    sendModbus(s, obufOneB, 53, ibufOneB, 50, "position parameter 2 - small");
        
    * drvSave1 = transId;
    sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive - small");


    /* medium */
    * firstClear9 = 5;           
    * posOneA9 = 5;
    * posOneA10 = htonl((firstPosMedium)*1000); 
    * clear9 = 6;      
    * posOneB9 = 6;       
    * posOneB10 = htonl((AKD_frame_posMedium)*1000);
    
    * firstClear1 = transId;           
    sendModbus(s, obufClFirst, 17, ibufClFirst, 50, "clear position - small");

    * posOneA1 = transId; 
    sendModbus(s, obufOneA, 53, ibufOneA, 50, "position parameter - small");
  
    * clear1 = transId;
    sendModbus(s, obufCl, 17, ibufCl, 50, "clear position 2 - small");
 
    * posOneB1 = transId;       
    sendModbus(s, obufOneB, 53, ibufOneB, 50, "position parameter 2 - small");
   
    * drvSave1 = transId;
    sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive - small");


    /* big */  
    * firstClear9 = 7;           
    * posOneA9 = 7;  
    * posOneA10 = htonl((firstPosBig)*1000);  
    * clear9 = 8;      
    * posOneB9 = 8;       
    * posOneB10 = htonl((AKD_frame_posBig)*1000);
    
    * firstClear1 = transId;           
    sendModbus(s, obufClFirst, 17, ibufClFirst, 50, "clear position - small");

    * posOneA1 = transId;  
    sendModbus(s, obufOneA, 53, ibufOneA, 50, "position parameter - small");

    * clear1 = transId;
    sendModbus(s, obufCl, 17, ibufCl, 50, "clear position 2 - small");
  
    * posOneB1 = transId;       
    sendModbus(s, obufOneB, 53, ibufOneB, 50, "position parameter 2 - small");
   
    * drvSave1 = transId;
    sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive - small");


    #ifdef RPI   
    fp_first_pos = fopen("/home/pi/TKK_PRESA/data/first_pos.txt", "w");
    #endif
    #ifdef LUKA
    fp_first_pos = fopen("/home/luka/TKK_PRESA_/data/first_pos.txt", "w");
    #endif
 
    fprintf(fp_first_pos, "%d\n", firstPosSmall);
    fprintf(fp_first_pos, "%d\n", firstPosSmall2);
    fprintf(fp_first_pos, "%d\n", firstPosMedium);
    fprintf(fp_first_pos, "%d\n", firstPosBig);
    fclose(fp_first_pos);

 
    #ifdef RPI   
    AKD_pos = fopen("/home/pi/TKK_PRESA/data/AKD_pos.txt", "w");
    #endif
    #ifdef LUKA
    AKD_pos = fopen("/home/luka/TKK_PRESA_/data/AKD_pos.txt", "w");
    #endif
 
    fprintf(AKD_pos, "%d\n", AKD_frame_posSmall);
    fprintf(AKD_pos, "%d\n", AKD_frame_posSmall2);
    fprintf(AKD_pos, "%d\n", AKD_frame_posMedium);
    fprintf(AKD_pos, "%d\n", AKD_frame_posBig);
    fclose(AKD_pos);

    #ifdef RPI   
    fp_press = fopen("/home/pi/TKK_PRESA/data/press.txt", "w");
    #endif
    #ifdef LUKA
    fp_press = fopen("/home/luka/TKK_PRESA_/data/press.txt", "w");
    #endif
 
    fprintf(fp_press, "%d\n", press);
    fclose(fp_press);
  }
  renderText("SAVE", smallText,  blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
}


void posButton(int x, int y, int w, int h, char *text, int firstPos)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  sprintf(tmBuff, "%s %d", text, firstPos);
  renderText(tmBuff, smallText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    posMan = firstPos;
  }
}


void enableButton(int x, int y, int w, int h)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  renderText("ENABLE", smallText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    int * intloc1_ed = (int*)(&obufEd[0]);
    int * intloc2_ed = (int*)(&obufEd[2]);
    int * intloc3_ed = (int*)(&obufEd[4]);
    int * intloc4_ed = (int*)(&obufEd[6]);
    int * intloc5_ed = (int*)(&obufEd[7]);
    int * intloc6_ed = (int*)(&obufEd[8]);
    int * intloc7_ed = (int*)(&obufEd[10]);
    int * intloc8_ed = (int*)(&obufEd[12]);
    int * intloc9_ed = (int*)(&obufEd[13]);
            
    * intloc1_ed = htons(0);  
    * intloc2_ed = htons(0);
    * intloc3_ed = htons(11);
    * intloc4_ed = 1;
    * intloc5_ed = 16;
    * intloc6_ed = htons(254);
    * intloc7_ed = htons(2);
    * intloc8_ed = 4;
    * intloc9_ed = htonl(1);
            
    sendModbus(s, obufEd, 17, ibufEd, 50, "enable drive - presa");
  }
}

void disableButton(int x, int y, int w, int h)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  renderText("DISABLE", smallText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    int * intloc1_ed = (int*)(&obufEd[0]);
    int * intloc2_ed = (int*)(&obufEd[2]);
    int * intloc3_ed = (int*)(&obufEd[4]);
    int * intloc4_ed = (int*)(&obufEd[6]);
    int * intloc5_ed = (int*)(&obufEd[7]);
    int * intloc6_ed = (int*)(&obufEd[8]);
    int * intloc7_ed = (int*)(&obufEd[10]);
    int * intloc8_ed = (int*)(&obufEd[12]);
    int * intloc9_ed = (int*)(&obufEd[13]);
            
    * intloc1_ed = htons(0);  
    * intloc2_ed = htons(0);
    * intloc3_ed = htons(11);
    * intloc4_ed = 1;
    * intloc5_ed = 16;
    * intloc6_ed = htons(236);
    * intloc7_ed = htons(2);
    * intloc8_ed = 4;
    * intloc9_ed = htonl(1);
            
    sendModbus(s, obufEd, 17, ibufEd, 50, "disable drive - presa");
  }
}

void startButton(int x, int y, int w, int h)
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderDrawLine(renderer, x, y, (x+w), y);
  SDL_RenderDrawLine(renderer, (x+w), y, (x+w), (y+h)); 
  SDL_RenderDrawLine(renderer, (x+w), (y+h), x, (y+h));
  SDL_RenderDrawLine(renderer, x, (y+h), x, y);

  renderText("START", smallText, blackColor);
  render(x+((w/2)-(textureWidth/2)), y + ((h/2)-(textureHeight/2)), NULL, 0.0, NULL, SDL_FLIP_NONE); 
  
  if(touchLocation.x > x && touchLocation.x < x+w && touchLocation.y > y && touchLocation.y < y + h && timestamp > oldtimestamp)
  {
    int * firstClear1 =  (int*)(&obufClFirst[0]);
    int * firstClear9 =  (int*)(&obufClFirst[16]);
    int * posOneA1 = (int*)(&obufOneA[0]);
    int * posOneA9 =  (int*)(&obufOneA[16]);
    int * posOneA10 = (int*)(&obufOneA[17]);
    int * posOneA15 = (int*)(&obufOneA[40]);
    int * drvSave1 = (int*)(&obufDS[0]);
   
    * firstClear9 = 9;      
    * posOneA9 = 9;       
    * posOneA10 = htonl((posMan)*1000);
    * posOneA15 = 100;
    
    * firstClear1 = transId;
    sendModbus(s, obufClFirst, 17, ibufClFirst, 50, "clear position - presa");
   
    * posOneA1 = transId;       
    sendModbus(s, obufOneA, 53, ibufOneA, 50, "position parameter - presa");
       
    * drvSave1 = transId;
    sendModbus(s, obufDS, 17, ibufDS, 50, "save to drive - presa");
   
    int * intloc1_ed = (int*)(&obufEd[0]);
    int * intloc2_ed = (int*)(&obufEd[2]);
    int * intloc3_ed = (int*)(&obufEd[4]);
    int * intloc4_ed = (int*)(&obufEd[6]);
    int * intloc5_ed = (int*)(&obufEd[7]);
    int * intloc6_ed = (int*)(&obufEd[8]);
    int * intloc7_ed = (int*)(&obufEd[10]);
    int * intloc8_ed = (int*)(&obufEd[12]);
    int * intloc9_ed = (int*)(&obufEd[13]);
            
    * intloc1_ed = htons(0);  
    * intloc2_ed = htons(0);
    * intloc3_ed = htons(11);
    * intloc4_ed = 1;
    * intloc5_ed = 16;
    * intloc6_ed = htons(544);
    * intloc7_ed = htons(2);
    * intloc8_ed = 4;
    * intloc9_ed = htonl(9);
            
    sendModbus(s, obufEd, 17, ibufEd, 50, "start motion task - presa");
  }
}






