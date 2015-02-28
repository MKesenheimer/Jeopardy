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