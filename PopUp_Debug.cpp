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

#include "PopUp.h"
#include "SDL_Init.h"
#include <string.h>
#include <iostream>

using namespace std;

void PopUp::init(int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer) {
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
    popup = popupSheet.getPopup();
    answer = popupSheet.getAnswer();
    question = popupSheet.getQuestion();
    
    textQuestion = theQuestion;
    textAnswer = theAnswer;
    
    //Logik
    popUpWasClicked = false;
    showAnswer = false;
}

//Konstruktor
PopUp::PopUp( int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer) {
	init(x, y, w, h, popupSheet, theQuestion, theAnswer);
    
    playMusicButton = NULL;
}

//überladener Konstruktor
PopUp::PopUp( int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer, Mix_Chunk *theMusic) {
	init(x, y, w, h, popupSheet, theQuestion, theAnswer);
    music = theMusic;
    
    TTF_Font* font = TTF_OpenFont( "lazy.ttf", 28 );
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface *buttonsheet = NULL;
    
    buttonsheet = load_image( "play.png" );
    playMusicButton = new Button(box.x+box.w/2-200/2, box.y+box.h/2, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "", white));
}

//überladener Joker-Konstruktor
PopUp::PopUp( int x, int y, int w, int h, PopupScreens popupSheet,  string joker, Mix_Chunk *theMusic) {
	init(x, y, w, h, popupSheet, joker, joker);
    
    playMusicButton = NULL;
    music = theMusic;
}

int PopUp::handle_events(SDL_Event* event) {
    //DEBUG
    printf("Point 1\n");
    
	//The mouse offsets
	int x = 0, y = 0;
    int action = 0;
    
    //Falls es eine Musikfrage ist und keine Antwort angezeigt wird
    if (playMusicButton != NULL && !showAnswer && music != NULL) {
        if( playMusicButton->handle_events(event) == 2 ) {
            //Mix_PlayChannel( -1, music, 0);
        }
    }
    
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
        //DEBUG
        printf("Point 2\n");
        
		//If the left mouse button was pressed
		if( event->button.button == SDL_BUTTON_LEFT ) {
			
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
            
            //falls es keine Musikfrage ist
            if (playMusicButton == NULL && showAnswer) {
                //falls Maus im Popup gedrückt
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                    //Set the button sprite
                    clip = &clips[ CLIP_MOUSEDOWN ];
                    popUpWasClicked = true;
                    action = 2;
                    //lösche den Popup Bildschirm
                    apply_surface( 0, 0, popup, answer, NULL );
                    apply_surface( 0, 0, popup, question, NULL );
                }
            }
            
            //falls es eine Musikfrage ist
            if (playMusicButton != NULL && showAnswer && music != NULL) {
                //falls Maus im Popup gedrückt
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                    //Set the button sprite
                    clip = &clips[ CLIP_MOUSEDOWN ];
                    popUpWasClicked = true;
                    action = 2;
                    //lösche den Popup Bildschirm
                    apply_surface( 0, 0, popup, answer, NULL );
                    apply_surface( 0, 0, popup, question, NULL );
                }
            }
            
            //falls es ein Joker ist
            if (textAnswer.compare("Joker\n") == 0 && music != NULL) {
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                    //Set the button sprite
                    clip = &clips[ CLIP_MOUSEDOWN ];
                    popUpWasClicked = true;
                    action = 2;
                    //lösche den Popup Bildschirm
                    apply_surface( 0, 0, popup, answer, NULL );
                    apply_surface( 0, 0, popup, question, NULL );
                }
            }
            
		}
        
        //If the right mouse button was pressed
		if( event->button.button == SDL_BUTTON_RIGHT ) {
            //DEBUG
            printf("Point 3\n");
            
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
			
			//If the mouse is over the button
			if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
				//Set the button sprite
				clip = &clips[ CLIP_MOUSEDOWN ];
                showAnswer = true;
			}
		}
	}
	
	//If a mouse button was released
	if( event->type == SDL_MOUSEBUTTONUP ) {
        //DEBUG
        printf("Point 4\n");
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

void PopUp::show(SDL_Surface* screen) {
    //DEBUG
    printf("Point 5a\n");
    //Falls es ein Joker ist und die Musik nicht läuft
    if (textAnswer.compare("Joker\n") == 0) {
        //Mix_PlayMusic( music, 0 );
        //Mix_HookMusicFinished(musicDone);
        //Mix_PlayChannel( -1, music, 0);
    }
    
    //Text
    TTF_Font* font = TTF_OpenFont( "lazy.ttf", 28 );
    SDL_Color black = { 0, 0, 0 };
    size_t posA, posQ;
    string substrAnswer, substrQuestion;
    
    //DEBUG
    printf("Point 5b\n");
    
    //DEBUG
    printf("Point 5b1\n"); posQ = textQuestion.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
    printf("Point 5b2\n"); substrQuestion = textQuestion.substr(0,posQ); //kopiere den String bis dahin
    printf("Point 5b3\n"); textQuestion = textQuestion.substr( posQ + 1 ); //kürze den alten String bis dahin
    printf("Point 5b4\n"); char* q = const_cast<char*>(substrQuestion.c_str()); //char cast
    //Hier passiert der Memory leak wenn die if-Abfrage fehlt! font wird irgendwo im Programm auf NULL gesetzt
    printf("Point 5b5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 20, 10, TTF_RenderText_Solid(font, q, black), question, clip ); //String auf Screen ausgeben
    
    //DEBUG
    printf("Point 5c\n");
    
    printf("Point 5c1\n"); posA = textAnswer.find_first_of( '\n' );
    printf("Point 5c2\n"); substrAnswer = textAnswer.substr(0,posA);
    printf("Point 5c3\n"); textAnswer = textAnswer.substr( posA + 1  );
    printf("Point 5c4\n"); char* a = const_cast<char*>(substrAnswer.c_str());
    printf("Point 5c5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 20, 10, TTF_RenderText_Solid(font, a, black), answer, clip );
    
    //DEBUG
    printf("Point 5d\n");
    
    for (int i = 0; i < 10; i++) {
        printf("Point 5d1\n"); posQ = textQuestion.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
        printf("Point 5d2\n"); substrQuestion = textQuestion.substr(0,posQ); //kopiere den String bis dahin
        printf("Point 5d3\n"); textQuestion = textQuestion.substr( posQ + 1 ); //kürze den alten String bis dahin
        printf("Point 5d4\n"); q = const_cast<char*>(substrQuestion.c_str()); //char cast
        printf("Point 5d5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 40, 60 + i * 40, TTF_RenderText_Solid(font, q, black), question, clip ); //String auf Screen ausgeben
        
        printf("Point 5d6\n"); posA = textAnswer.find_first_of( '\n' );
        printf("Point 5d7\n"); substrAnswer = textAnswer.substr(0,posA);
        printf("Point 5d8\n"); textAnswer = textAnswer.substr( posA + 1  );
        printf("Point 5d9\n"); a = const_cast<char*>(substrAnswer.c_str());
        printf("Point 5d10\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 40, 60 + i * 40, TTF_RenderText_Solid(font, a, black), answer, clip );
    }
    
    //DEBUG
    printf("Point 5e\n");
    
    if (!showAnswer) {
        apply_surface( box.x, box.y, question, screen, clip );
        if (playMusicButton != NULL) {
            playMusicButton->show(screen);
        }
    }

    if (showAnswer) {
        apply_surface( box.x, box.y, answer, screen, clip );
    }
    //DEBUG
    printf("Point 6\n");
}

void PopUp::set_clips() {
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
}

void PopUp::musicDone() {
    Mix_HaltMusic();
    Mix_FreeMusic(music);
    //Mix_FreeChunk( music );
    //music = NULL;
}

PopUp::~PopUp(){
    if (music != NULL) {
        //musicDone();
    }
}
