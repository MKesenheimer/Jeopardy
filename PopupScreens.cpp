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