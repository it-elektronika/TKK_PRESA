#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define RPI 1

int program;
int sbarText;
int page;

int page_stage[3];
int curr_page;

char buff_reg[10][10];

int backgroundColor;

FILE *fp_can_size;
char *line;
size_t len;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;
SDL_Point touchLocation;
SDL_Event event;

SDL_Color whiteColor;
SDL_Color blackColor;

TTF_Font *smallText;
TTF_Font *regularText;

int textureWidth;
int textureHeight;

int timestamp;
int oldtimestamp;
int cycleCounter;
int cycleCheck;
int left_button_selected;
int right_button_selected;
int pageNumber;

int pageLoadCount;
int blinkCounter;
int blinkerCounter;

int selected[9];
int noButtonSelected;
int id;

int init();
void initVars();
void freeTexture();
void renderBackground();
void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
int renderText(const char *text, TTF_Font *textFont,  SDL_Color textColor);
void renderContent();
void renderStatusBar();
void renderAdmin(int x, int y, int w, int h, int curr_page, int gotoNum);
void touchUpdate();
void up_button(int x, int y, int *incrementee, int incrementor);
void down_button(int x, int y, int *decrementee, int decrementor);
void left_button(int x, int y);
void right_button(int x, int y);
void button(int x, int y, int w, int h, char *text, int id);
void savebutton(int x, int y, int w, int h, char *text);
void pageOne(void);
void pageTwo(void);
void pageThree(void);
