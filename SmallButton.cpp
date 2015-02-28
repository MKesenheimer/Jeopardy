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

#include "SmallButton.h"
#include "SDL_Init.h"

//Konstruktor
SmallButton::SmallButton( int x, int y, int w, int h, SDL_Surface* theButton,  SDL_Surface* theCaption) {
	
	//Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
    
    CLIP_MOUSEOVER = 0;
    CLIP_MOUSEOUT = 1;
    CLIP_MOUSEDOWN = 2;
    CLIP_MOUSEUP = 3;
	
    caption = theCaption;
    button = theButton;
    
    buttonWasClicked = false;
    
    set_clips();
    
    //Set the default sprite
	clip = &clips[ CLIP_MOUSEOUT ];
}

int SmallButton::handle_events(SDL_Event* event) {
	//The mouse offsets
	int x = 0, y = 0;
    int action = 0;
    
	//If the mouse moved
	if( event->type == SDL_MOUSEMOTION ) {
		
		//Get the mouse offsets
		x = event->motion.x;
		y = event->motion.y;
		
		//If the mouse is over the button
		if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
			
			//Set the button sprite
			clip = &clips[ CLIP_MOUSEOVER ];
            action = 1;
		}
		
		//If not
		else {
			//Set the button sprite
			clip = &clips[ CLIP_MOUSEOUT ];
            action = 0;
		}
	}
	
	//If a mouse button was pressed
	if( event->type == SDL_MOUSEBUTTONDOWN ) {
		
		//If the left mouse button was pressed
		if( event->button.button == SDL_BUTTON_LEFT ) {
			
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
			
			//If the mouse is over the button
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
				//Set the button sprite
				clip = &clips[ CLIP_MOUSEDOWN ];
                buttonWasClicked = true;
                action = 2;
			}
		}
	}
	
	//If a mouse button was released
	if( event->type == SDL_MOUSEBUTTONUP ) {
		//If the left mouse button was released
		
		if( event->button.button == SDL_BUTTON_LEFT ) {
			
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
			
			//If the mouse is over the button
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
				//Set the button sprite
				clip = &clips[ CLIP_MOUSEUP ];
                action = 3;
			}
		}
	}
    
    return action;
}

void SmallButton::show(SDL_Surface* screen) {
    
    //Show the button
	apply_surface( box.x, box.y, button, screen, clip );
    apply_surface( box.x, box.y, caption, screen, NULL );
}

void SmallButton::set_clips() {
	//Clip the sprite sheet
	clips[ CLIP_MOUSEOVER ].x = 0; //Mouse Over
	clips[ CLIP_MOUSEOVER ].y = 0;
	clips[ CLIP_MOUSEOVER ].w = 50;
	clips[ CLIP_MOUSEOVER ].h = 37;
	clips[ CLIP_MOUSEOUT ].x = 50; //Mouse Out
	clips[ CLIP_MOUSEOUT ].y = 0;
	clips[ CLIP_MOUSEOUT ].w = 50;
	clips[ CLIP_MOUSEOUT ].h = 37;
	clips[ CLIP_MOUSEDOWN ].x = 0; //Mous Down
	clips[ CLIP_MOUSEDOWN ].y = 37;
	clips[ CLIP_MOUSEDOWN ].w = 50;
	clips[ CLIP_MOUSEDOWN ].h = 37;
	clips[ CLIP_MOUSEUP ].x = 50; //Mouse Up
	clips[ CLIP_MOUSEUP ].y = 37;
	clips[ CLIP_MOUSEUP ].w = 50;
	clips[ CLIP_MOUSEUP ].h = 37;
}