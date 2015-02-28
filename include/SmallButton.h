#pragma once

#include "SDL_Init.h"

class SmallButton {
	
private:
	//The attributes of the button
	SDL_Rect box;
	
	//The part of the button sprite sheet that will be shown
	SDL_Rect* clip;
    
    SDL_Rect clips[4];
    
    //Button image
    SDL_Surface* button;
    
    //Name of the button
    SDL_Surface* caption;
    
    int CLIP_MOUSEOVER;
    int CLIP_MOUSEOUT;
    int CLIP_MOUSEDOWN;
    int CLIP_MOUSEUP;
    
    bool buttonWasClicked;
	
public:
	//Initialize the variables
	SmallButton( int x, int y, int w, int h, SDL_Surface* theButton, SDL_Surface* caption);
	
	//Handles events and set the button's sprite region
	int handle_events(SDL_Event* event); // 1 = Mouse over Button, 2 = Mouse pressed over Button, 3 = Mouse released over Button
	
	//Shows the button on the screen
	void show(SDL_Surface* screen);
    
    //Set the Button Clips
    void set_clips();
};