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
#include "SDL_Init.h"

class PopupScreens {
	
private:
    SDL_Surface* answer;
    SDL_Surface* question;
    SDL_Surface* popup;
    SDL_Surface* joker;
	
public:
    SDL_Surface* getAnswer();
    SDL_Surface* getQuestion();
    SDL_Surface* getPopup();
    SDL_Surface* getJoker();
    PopupScreens();
    ~PopupScreens();
    void freeSurfaces();
};