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

#include "SDL_Init.h"

class Splash {
	
private:
	//The attributes of the PopUp
	SDL_Rect box;
	
	//The part of the Popup sprite sheet that will be shown
	SDL_Rect* clip;
    SDL_Rect clips[4];
    
    //PopUp image
    SDL_Surface* splash;
    
    //Music
    Mix_Music* music;
    
    int CLIP_MOUSEOVER;
    int CLIP_MOUSEOUT;
    int CLIP_MOUSEDOWN;
    int CLIP_MOUSEUP;
    
    bool splashWasClicked;
    bool refresh;
	
    string text;
    
public:
	//Initialize the variables
	Splash( int x, int y, int w, int h, SDL_Surface *splashSheet, string theText, Mix_Music* theMusic);
  
    //apply the surfaces
    void refresh_splash();
    
	//Handles events and set the button's sprite region
	int handle_events(SDL_Event* event); // 1 = Mouse over Popup, 2 = Mouse pressed over Popup, 3 = Mouse released over Popup
	
	//Shows the button on the screen
	void show(SDL_Surface* screen);
    
    //Set the Button Clips
    void set_clips();
    
    //Stop and free the Music
    void musicDone();
};