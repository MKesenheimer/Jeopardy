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