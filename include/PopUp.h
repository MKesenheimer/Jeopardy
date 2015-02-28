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
#include "PopupScreens.h"
#include "Button.h"

class PopUp {
	
private:
	//The attributes of the PopUp
	SDL_Rect box;
	
	//The part of the Popup sprite sheet that will be shown
	SDL_Rect* clip;
    SDL_Rect clips[4];
    
    //PopUp image
    SDL_Surface* popup;
    SDL_Surface* answer;
    SDL_Surface* question;
    SDL_Surface* joker;
    
    int CLIP_MOUSEOVER;
    int CLIP_MOUSEOUT;
    int CLIP_MOUSEDOWN;
    int CLIP_MOUSEUP;
    
    //Logik
    bool showAnswer;
    bool refresh;
    bool isJoker;
    bool jokerMusicFinished;
	
    //Text
    string textQuestion, textAnswer;
    
    Button* playMusicButton;
    Mix_Music *music;
    
public:
	//Initialize the variables
	PopUp( int x, int y, int w, int h, PopupScreens popupSheet, string theQuestion, string theAnswer);
	PopUp( int x, int y, int w, int h, PopupScreens popupSheet, string theQuestion, string theAnswer, Mix_Music *theMusic);
    PopUp( int x, int y, int w, int h, PopupScreens popupSheet, string joker, Mix_Music *theMusic);
    
    //Initialize the Screens
    void init(int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer);
    
    //apply the surfaces
    void refresh_popup();
    
	//Handles events and set the button's sprite region
	int handle_events(SDL_Event* event); // 1 = Mouse over Popup, 2 = Mouse pressed over Popup, 3 = Mouse released over Popup
	
	//Shows the button on the screen
	void show(SDL_Surface* screen);
    
    //Set the Button Clips
    void set_clips();
    
    void musicDone();
};