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

#include "Splash.h"
#include "SDL_Init.h"
#include <string.h>
#include <iostream>

using namespace std;

//Konstruktor
Splash::Splash( int x, int y, int w, int h, SDL_Surface* splashSheet,  string theText, Mix_Music* theMusic) {
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::init() - start\n");
    
    //Set the button's attributes
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
    
    CLIP_MOUSEOVER = 0;
    CLIP_MOUSEOUT = 1;
    CLIP_MOUSEDOWN = 2;
    CLIP_MOUSEUP = 3;
	
    set_clips();
    
    //Set the default sprite
	clip = &clips[ CLIP_MOUSEOUT ];
    
    //Surfaces
    splash = splashSheet;
    
    text = theText;
    
    //Logik
    splashWasClicked = false;
    refresh = true;
    
    music = theMusic;
    
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::init() - end\n");
}

int Splash::handle_events(SDL_Event* event) {
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::handle_events - start\n");
    
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
        refresh = true;
        
		//If the left mouse button was pressed
		if( event->button.button == SDL_BUTTON_LEFT ) {
			
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
            
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                //Set the button sprite
                clip = &clips[ CLIP_MOUSEDOWN ];
                splashWasClicked = true;
                action = 2;
                if (Mix_PlayingMusic() == 1) {
                    musicDone();
                }
            }
        }
        
        //If the right mouse button was pressed
		if( event->button.button == SDL_BUTTON_RIGHT ) {
			
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
			
			//If the mouse is over the button
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
				//Set the button sprite
				clip = &clips[ CLIP_MOUSEDOWN ];
                
                if (Mix_PlayingMusic() == 1) {
                    musicDone();
                }
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
    
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::handle_events - end\n");
    
    return action;
}

void Splash::refresh_splash() {
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::refresh_splash - start\n");
    
    //DEBUG
    printf("[DEBUG] Start debugging Splash::refresh_splash...\n");
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1a\n");
    //Text
    TTF_Font* font = TTF_OpenFont( "lazy.ttf", 28 );
    TTF_Font* jeopFont = TTF_OpenFont("gyparody.ttf", 60);
    SDL_Color white = { 255, 255, 255 };
    size_t posT;
    string substrText;
    
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1b\n");
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1b1\n"); posT = text.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1b2\n"); substrText = text.substr(0,posT); //kopiere den String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1b3\n"); text = text.substr( posT + 1 ); //kürze den alten String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1b4\n"); char* t = const_cast<char*>(substrText.c_str()); //char cast
    //Hier passiert der Memory leak wenn die if-Abfrage fehlt! font wird irgendwo im Programm auf NULL gesetzt
    if(font != NULL && t != NULL && splash != NULL){
        printf("[DEBUG] Checkpoint Splash::refresh_splash 1b5\n"); apply_surface( 110, 140, TTF_RenderText_Solid(jeopFont, t, white), splash, clip ); //String auf Screen ausgeben
    }
    
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1d1\n"); posT = text.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1d2\n"); substrText = text.substr(0,posT); //kopiere den String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1d3\n"); text = text.substr( posT + 1 ); //kürze den alten String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1d4\n"); t = const_cast<char*>(substrText.c_str()); //char cast
    if(font != NULL && t != NULL && splash != NULL){
        printf("[DEBUG] Checkpoint Splash::refresh_splash 1d5\n"); apply_surface( 60, 250, TTF_RenderText_Solid(font, t, white), splash, clip ); //String auf Screen ausgeben
    }
    
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1e1\n"); posT = text.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1e2\n"); substrText = text.substr(0,posT); //kopiere den String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1e3\n"); text = text.substr( posT + 1 ); //kürze den alten String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1e4\n"); t = const_cast<char*>(substrText.c_str()); //char cast
    if(font != NULL && t != NULL && splash != NULL) {
        printf("[DEBUG] Checkpoint Splash::refresh_splash 1e5\n"); apply_surface( 60, 250, TTF_RenderText_Solid(font, t, white), splash, clip ); //String auf Screen ausgeben
    }
    
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1f1\n"); posT = text.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1f2\n"); substrText = text.substr(0,posT); //kopiere den String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1f3\n"); text = text.substr( posT + 1 ); //kürze den alten String bis dahin
    printf("[DEBUG] Checkpoint Splash::refresh_splash 1f4\n"); t = const_cast<char*>(substrText.c_str()); //char cast
    if(font != NULL && t != NULL && splash != NULL) {
        printf("[DEBUG] Checkpoint Splash::refresh_splash 1f5\n"); apply_surface( 200, 300, TTF_RenderText_Solid(font, t, white), splash, clip ); //String auf Screen ausgeben
    }
    
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::refresh_splash - end\n");
}

void Splash::show(SDL_Surface* screen) {
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::show - start\n");

    if ( (Mix_PlayingMusic() == 0) || (Mix_PausedMusic() == 1) ) {
        Mix_PlayMusic( music, 0 );
        //Mix_HookMusicFinished(musicDone);
    }
    
    //Apply the text to the surfaces
    if (refresh) refresh_splash();
    refresh = false;
    
    apply_surface( box.x, box.y, splash, screen, clip );
    
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::show - end\n");
}

void Splash::set_clips() {
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::set_clips - start\n");
    
	//Clip the sprite sheet
	clips[ CLIP_MOUSEOVER ].x = 0; //Mouse Over
	clips[ CLIP_MOUSEOVER ].y = 0;
	clips[ CLIP_MOUSEOVER ].w = 640;
	clips[ CLIP_MOUSEOVER ].h = 480;
	clips[ CLIP_MOUSEOUT ].x = 0; //Mouse Out
	clips[ CLIP_MOUSEOUT ].y = 0;
	clips[ CLIP_MOUSEOUT ].w = 640;
	clips[ CLIP_MOUSEOUT ].h = 480;
	clips[ CLIP_MOUSEDOWN ].x = 0; //Mous Down
	clips[ CLIP_MOUSEDOWN ].y = 0;
	clips[ CLIP_MOUSEDOWN ].w = 640;
	clips[ CLIP_MOUSEDOWN ].h = 480;
	clips[ CLIP_MOUSEUP ].x = 0; //Mouse Up
	clips[ CLIP_MOUSEUP ].y = 0;
	clips[ CLIP_MOUSEUP ].w = 640;
	clips[ CLIP_MOUSEUP ].h = 480;
    
    //DEBUG
    printf("[DEBUG] Checkpoint Splash::set_clips - end\n");
}

void Splash::musicDone() {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::musicDone - start\n");
    
    Mix_HaltMusic();
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::musicDone - end\n");
}