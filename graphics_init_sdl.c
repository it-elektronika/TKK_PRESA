#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Texture *texture;
SDL_Event event;

SDL_Point touchLocation = {-1, -1};
TTF_Font *smallText;
TTF_Font *regularText;

int program = 1;
int sbarText = 0;
int backgroundColor = 0;
int page = 0;
int textureWidth = 0;
int textureHeight = 0;

int timestamp = 0;
int oldtimestamp = 0;

int pageNumber = 0;
int cycleCounter = 0;
int cycleCheck = 0;


