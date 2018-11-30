#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800
#define RPI 1

int program;
int sbarText;
int page;
int backgroundColor;

FILE *fp_can_size;
FILE *fp_first_pos;
FILE *fp_second_pos;
FILE *AKD_pos;
FILE *fp_press;
char *line;
size_t len;

int modY;
int outputButton1;
int outputButton2;
int startButton1;
int stopButton1;
int continueButton1;

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
int pageNumber;

int selected[9];
int selectedMeasure[2];
int init();
void freeTexture();
void renderBackground();
void render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);
int renderText(const char *text, TTF_Font *textFont,  SDL_Color textColor);
void renderContent();
void renderStatusBar();
void renderAdmin(int x, int y, int w, int h, int gotoNum);
void touchUpdate();
void up_button(int x, int y, int *incrementee, int incrementor, int max);
void down_button(int x, int y, int *decrementee, int decrementor, int min);
void left_button(int x, int y);
void right_button(int x, int y);
void button(int x, int y, int w, int h, char *text, int id);
void saveButton(int x, int y, int w, int h, char *text);
void savePos(int x, int y, int w, int h);
void saveTime(int x, int y, int w, int h, char *text);
void clockButton(int x, int y, int w, int h, char *text);
void goToButton(int x, int y, int w, int h, char *text, int goToNum);
void outputButton(int x, int y, int h, int w, int id);
void start_button(int x, int y, int h, int w);
void stop_button(int x, int y, int h, int w);
void continue_button(int x, int y, int h, int w, int stepMax);
void posButton(int x, int y, int w, int h, char *text, int firstPos);
void enableButton(int x, int y, int w, int h);
void disableButton(int x, int y, int w, int h);
void startButton(int x, int y, int w, int h);
void measureButton(int x, int y, int w, int h, char *text, int id);

void pageZero();
void pageOne();
void pageTwo();
void pageThree();
void pageFour();
void pageFive();
void pageSix();
void pageSeven();
void pageEight();
void pageNine();
void pageTen();
void pageEleven();
void pageTwelve();
