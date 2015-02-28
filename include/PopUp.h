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