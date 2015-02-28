#include "PopUp.h"
#include "SDL_Init.h"
#include <string.h>
#include <iostream>

using namespace std;

void PopUp::init(int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer) {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::init() - start\n");
    
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
    joker = popupSheet.getJoker();
    
    textQuestion = theQuestion;
    textAnswer = theAnswer;
    
    //Logik
    showAnswer = false;
    refresh = true;
    isJoker = false;
    jokerMusicFinished = false;
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::init() - end\n");
}

//Konstruktor
PopUp::PopUp( int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer) {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::PopUp()_1 - start\n");
	init(x, y, w, h, popupSheet, theQuestion, theAnswer);
    
    playMusicButton = NULL;
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::PopUp()_1 - end\n");
}

//überladener Konstruktor
PopUp::PopUp( int x, int y, int w, int h, PopupScreens popupSheet,  string theQuestion, string theAnswer, Mix_Music *theMusic) {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::PopUp()_2 - start\n");
    
	init(x, y, w, h, popupSheet, theQuestion, theAnswer);
    music = theMusic;
    
    TTF_Font* font = TTF_OpenFont( "lazy.ttf", 28 );
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface *buttonsheet = NULL;
    
    buttonsheet = load_image( "play.png" );
    playMusicButton = new Button(box.x+box.w/2-200/2, box.y+box.h/2, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "", white));
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::PopUp()_2 - end\n");
}

//überladener Joker-Konstruktor
PopUp::PopUp( int x, int y, int w, int h, PopupScreens popupSheet,  string joker, Mix_Music *theMusic) {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::PopUp()_3 - start\n");
    
	init(x, y, w, h, popupSheet, joker, joker);
    playMusicButton = NULL;
    
    music = theMusic;
    isJoker = true;
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::PopUp()_3 - end\n");
}

int PopUp::handle_events(SDL_Event* event) {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::handle_events - start\n");
    
	//The mouse offsets
	int x = 0, y = 0;
    int action = 0;
	
    //Falls es eine Musikfrage ist und keine Antwort angezeigt wird
    if (playMusicButton != NULL && !showAnswer) {
        if( playMusicButton->handle_events(event) == 2 ) {
            //Play the music
            Mix_PlayMusic( music, 0 );
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
        refresh = true;
        
		//If the left mouse button was pressed
		if( event->button.button == SDL_BUTTON_LEFT ) {
			
			//Get the mouse offsets
			x = event->button.x;
			y = event->button.y;
            
            //falls es keine Musikfrage ist
            if (playMusicButton == NULL && showAnswer) {
                printf("[DEBUG] PopUp schliessen\n");
                //falls Maus im Popup gedrückt
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                    //Set the button sprite
                    clip = &clips[ CLIP_MOUSEDOWN ];
                    action = 2;
                    
                    //lösche den Popup Bildschirm
                    apply_surface( 0, 0, popup, answer, NULL );
                    apply_surface( 0, 0, popup, question, NULL );
                    if (Mix_PlayingMusic() == 1) {
                        musicDone();
                    }
                }
            }
            
            //falls es eine Musikfrage ist
            if (playMusicButton != NULL && showAnswer) {
                printf("[DEBUG] Musik PopUp schliessen\n");
                //falls Maus im Popup gedrückt
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                    //Set the button sprite
                    clip = &clips[ CLIP_MOUSEDOWN ];
                    action = 2;
                    
                    //lösche den Popup Bildschirm
                    apply_surface( 0, 0, popup, answer, NULL );
                    apply_surface( 0, 0, popup, question, NULL );
                    if (Mix_PlayingMusic() == 1) {
                        musicDone();
                    }
                }
            }
            
            //falls es ein Joker ist
            if (isJoker) {
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) ) {
                    printf("[DEBUG] Joker PopUp schliessen\n");
                    //Set the button sprite
                    clip = &clips[ CLIP_MOUSEDOWN ];
                    action = 2;
                    
                    //lösche den Popup Bildschirm
                    apply_surface( 0, 0, popup, answer, NULL );
                    apply_surface( 0, 0, popup, question, NULL );
                    if (Mix_PlayingMusic() == 1) {
                        musicDone();
                    }
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
                showAnswer = true;
                
                if (playMusicButton != NULL && Mix_PlayingMusic()) {
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
    printf("[DEBUG] Checkpoint PopUp::handle_events - end\n");
    
    return action;
}

void PopUp::refresh_popup() {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::refresh_popup - start\n");
    
    //DEBUG
    printf("[DEBUG] Start debugging PopUp::refresh_popup...\n");
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1a\n");
    //Text
    TTF_Font* font = TTF_OpenFont( "lazy.ttf", 28 );
    SDL_Color black = { 0, 0, 0 };
    size_t posA, posQ;
    string substrAnswer, substrQuestion;
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1b\n");
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1b1\n"); posQ = textQuestion.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1b2\n"); substrQuestion = textQuestion.substr(0,posQ); //kopiere den String bis dahin
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1b3\n"); textQuestion = textQuestion.substr( posQ + 1 ); //kürze den alten String bis dahin
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1b4\n"); char* q = const_cast<char*>(substrQuestion.c_str()); //char cast
    //Hier passiert der Memory leak wenn die if-Abfrage fehlt! font wird irgendwo im Programm auf NULL gesetzt
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1b5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 20, 10, TTF_RenderText_Solid(font, q, black), question, clip ); //String auf Screen ausgeben
    
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1c1\n"); posA = textAnswer.find_first_of( '\n' );
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1c2\n"); substrAnswer = textAnswer.substr(0,posA);
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1c3\n"); textAnswer = textAnswer.substr( posA + 1  );
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1c4\n"); char* a = const_cast<char*>(substrAnswer.c_str());
    printf("[DEBUG] Checkpoint PopUp::refresh_popup 1c5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 20, 10, TTF_RenderText_Solid(font, a, black), answer, clip );
    
    
    for (int i = 0; i < 10; i++) {
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1d1\n"); posQ = textQuestion.find_first_of( '\n' ); //Finde den ersten Zeilenumbruch
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1d2\n"); substrQuestion = textQuestion.substr(0,posQ); //kopiere den String bis dahin
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1d3\n"); textQuestion = textQuestion.substr( posQ + 1 ); //kürze den alten String bis dahin
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1d4\n"); q = const_cast<char*>(substrQuestion.c_str()); //char cast
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1d5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 40, 60 + i * 40, TTF_RenderText_Solid(font, q, black), question, clip ); //String auf Screen ausgeben
        
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1e1\n"); posA = textAnswer.find_first_of( '\n' );
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1e2\n"); substrAnswer = textAnswer.substr(0,posA);
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1e3\n"); textAnswer = textAnswer.substr( posA + 1  );
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1e4\n"); a = const_cast<char*>(substrAnswer.c_str());
        printf("[DEBUG] Checkpoint PopUp::refresh_popup 1e5\n"); if(font != NULL && q != NULL && question != NULL) apply_surface( 40, 60 + i * 40, TTF_RenderText_Solid(font, a, black), answer, clip );
    }
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::refresh_popup - end\n");
}

void PopUp::show(SDL_Surface* screen) {
    
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::show - start\n");
    
    //Falls es ein Joker ist und die Musik nicht läuft
    if (isJoker && !jokerMusicFinished && ((Mix_PlayingMusic() == 0) || (Mix_PausedMusic() == 1) )) {
        Mix_PlayMusic( music, 0 );
        //Mix_HookMusicFinished(musicDone);
        apply_surface( 65, 10, joker, answer, NULL );
        apply_surface( 65, 10, joker, question, NULL );
        jokerMusicFinished = true;
    }
    
    //Apply the text to the surfaces
    if (refresh) refresh_popup();
    refresh = false;
    
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
    printf("[DEBUG] Checkpoint PopUp::show - end\n");
}

void PopUp::set_clips() {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::set_clips - start\n");
    
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
    printf("[DEBUG] Checkpoint PopUp::set_clips - end\n");
}

void PopUp::musicDone() {
    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::musicDone - start\n");
    
    Mix_PauseMusic();

    //DEBUG
    printf("[DEBUG] Checkpoint PopUp::musicDone - end\n");
}