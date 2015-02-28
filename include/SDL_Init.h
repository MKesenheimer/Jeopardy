/*   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Jeopardy  Copyright (C) 2014 Matthias Kesenheimer
 *   This program comes with ABSOLUTELY NO WARRANTY.
 *   This is free software, and you are welcome to redistribute it
 *   under certain conditions.
 */

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