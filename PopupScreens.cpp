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

#include "PopupScreens.h"
#include "SDL_Init.h"
#include <iostream>

//Konstruktor
PopupScreens::PopupScreens() {
	popup = load_image( "popup.png" );
    answer = load_image( "popup.png" );
    question = load_image( "popup.png" );
    joker = load_image("troll.png");
}

PopupScreens::~PopupScreens() {
    //freeSurfaces();
}

void PopupScreens::freeSurfaces() {
    printf("[DEBUG] Freeing the PopupScreens Surfaces\n");
    
    if (popup != NULL) SDL_FreeSurface( popup );
    if (answer != NULL) SDL_FreeSurface( answer );
    if (question != NULL) SDL_FreeSurface( question );
    if (joker != NULL) SDL_FreeSurface( joker );
    
    printf("[DEBUG] PopupScreens Surfaces freed\n");
}

SDL_Surface* PopupScreens::getAnswer() {
    return answer;
}

SDL_Surface* PopupScreens::getQuestion() {
    return question;
}


SDL_Surface* PopupScreens::getPopup() {
    return popup;
}

SDL_Surface* PopupScreens::getJoker() {
    return joker;
}