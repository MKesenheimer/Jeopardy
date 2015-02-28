#pragma once

#include <list>
#include <string>
#include <curses.h>
using namespace std;
#include "SDL/SDL.h"
#include "SDL_ttf/SDL_ttf.h"
#include "SDL_image/SDL_image.h"
#include "SDL_mixer/SDL_mixer.h"

using namespace std;

SDL_Surface *load_image(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
SDL_Surface* init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP);