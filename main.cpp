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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <sstream>
#include "SDL_Init.h"
#include "Button.h"
#include "SmallButton.h"
#include "PopUp.h"
#include "PopupScreens.h"
#include "Splash.h"
#include <iostream>
 
using namespace std;

//Attributes of the screen
const int SCREEN_WIDTH = 1680; //1680
const int SCREEN_HEIGHT = 1050; //1050
const int SCREEN_BPP = 32;
const int POPUP_WIDTH = 640;
const int POPUP_HEIGHT = 480;

//The surfaces
SDL_Surface *background = NULL;
SDL_Surface *buttonsheet = NULL;
SDL_Surface *buttonsheetTeamRot = NULL;
SDL_Surface *buttonsheetTeamGruen = NULL;
SDL_Surface *buttonsheetTeamGelb = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *popUpText = NULL;
SDL_Surface *balkenRot = NULL;
SDL_Surface *balkenGruen = NULL;
SDL_Surface *balkenGelb = NULL;
SDL_Surface *loeschen = NULL;
SDL_Surface *splashSheet = NULL;


//The event structure
SDL_Event event;

//Text
TTF_Font *font = NULL;
TTF_Font *jeopFont = NULL;
TTF_Font *catFont = NULL;
SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };

//Music
Mix_Music *joker = NULL;
Mix_Music *jeopMelodie = NULL;
Mix_Music *music1 = NULL;
Mix_Music *music2 = NULL;
Mix_Music *music3 = NULL;
Mix_Music *music4 = NULL;
Mix_Music *music5 = NULL;
Mix_Music *music6 = NULL;
Mix_Music *music7 = NULL;
Mix_Music *music8 = NULL;

//Anzahl der Kategorien und der Schwierigkeiten
const int categories = 7; //x-Achse
const int difficulities = 5; //y-Achse

//Popups mit Fragen und Antworten
PopUp* myPopUp[categories][difficulities];

string convertInt(int number)
{
    ostringstream convert;//create a stringstream
    convert << number;//add number to the stream
    return convert.str();//return a string with the contents of the stream
}

void clean_up() {
    printf("[DEBUG] Cleaning up...\n");
    
    printf("[DEBUG] Cleaning Surfaces...\n");
    //Free the image
    if (background != NULL) SDL_FreeSurface( background );
    if (buttonsheet != NULL) SDL_FreeSurface( buttonsheet );
    if (buttonsheetTeamRot != NULL) SDL_FreeSurface( buttonsheetTeamRot );
    if (buttonsheetTeamGruen != NULL) SDL_FreeSurface( buttonsheetTeamGruen );
    if (buttonsheetTeamGelb != NULL) SDL_FreeSurface( buttonsheetTeamGelb );
    if (screen != NULL) SDL_FreeSurface( screen );
    if (popUpText != NULL) SDL_FreeSurface( popUpText );
    if (balkenRot != NULL) SDL_FreeSurface( balkenRot );
    if (balkenGruen != NULL) SDL_FreeSurface( balkenGruen );
    if (balkenGelb != NULL) SDL_FreeSurface( balkenGelb );
    if (loeschen != NULL) SDL_FreeSurface( loeschen );
    if (splashSheet != NULL) SDL_FreeSurface( splashSheet );
    
    printf("[DEBUG] Cleaning Fonts...\n");
	if (font != NULL) TTF_CloseFont( font );
    if (jeopFont != NULL) TTF_CloseFont( jeopFont );
    if (catFont != NULL) TTF_CloseFont( catFont );
    
    printf("[DEBUG] Cleaning Music...\n");
    printf("[DEBUG] Cleaning Music 1\n"); if (joker != NULL) Mix_FreeMusic( joker );
    printf("[DEBUG] Cleaning Music 2\n"); if (jeopMelodie != NULL) Mix_FreeMusic( jeopMelodie );
    printf("[DEBUG] Cleaning Music 3\n"); if (music1 != NULL) Mix_FreeMusic( music1 );
    printf("[DEBUG] Cleaning Music 4\n"); if (music2 != NULL) Mix_FreeMusic( music2 );
    printf("[DEBUG] Cleaning Music 5\n"); if (music3 != NULL) Mix_FreeMusic( music3 );
    printf("[DEBUG] Cleaning Music 6\n"); if (music4 != NULL) Mix_FreeMusic( music4 );
    printf("[DEBUG] Cleaning Music 7\n"); if (music5 != NULL) Mix_FreeMusic( music5 );
    printf("[DEBUG] Cleaning Music 8\n"); if (music6 != NULL) Mix_FreeMusic( music6 );
    printf("[DEBUG] Cleaning Music 9\n"); if (music7 != NULL) Mix_FreeMusic( music7 );
    printf("[DEBUG] Cleaning Music 10\n"); if (music8 != NULL) Mix_FreeMusic( music8 );
    
    Mix_CloseAudio();
    
    //Quit SDL
	SDL_Quit();
    
    printf("[DEBUG] Done.\n");
}

void generatePopUps() {
    PopupScreens popupSheet;
    //Das geht auch eleganter... irgendwie
    //erste Kategorie
    myPopUp[0][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    myPopUp[0][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nAls Saenger welcher Rockgruppe wurde\nMick Jagger beruehmt?\n", "Antwort:\nThe Rolling Stones\n");
    myPopUp[0][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nVon wann bis wann lebte\nJohann Sebastian Bach?\n\na) 1596-1661\n\nb) 1650-1723\n\nc) 1685- 1750\n\nd) 1702-1769\n", "Antwort:\n1685- 1750\n");
    myPopUp[0][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWann wurde das Ensemble\nGENESIS BRASS gegruendet?\n", "Antwort:\n2003\n");
    myPopUp[0][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWann kam Christian Sprenger\nzur  Welt?\n\na) 1974\n\nb) 1975\n\nc) 1976\n\nd) 1977\n", "Antwort:\n1976\n");
    //zweite Kategorie
    myPopUp[1][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWie heisst folgendes Stueck?\n", "Antwort:\nDu bist die Kraft, die mir oft fehlt\n", music1);
    myPopUp[1][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    myPopUp[1][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWie heisst folgendes Stueck?\n", "Antwort:\nYellow Mountains\n", music2);
    myPopUp[1][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWie heisst folgendes Stueck?\n", "Antwort:\nFunky Walkin'\n", music3);
    myPopUp[1][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWelcher Komponist hat folgendes\n Stueck komponiert?\n", "Antwort:\nAntonio Vivaldi\n", music4);
    //dritte Kategorie
    myPopUp[2][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWelche zwei Tongeschlechter gibt es?\n", "Antwort:\nDur und Moll\n");
    myPopUp[2][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWas bedeutet fp?\n", "Antwort:\nfortepiano = Tonanfang laut und\nsofort danach wieder leise\n");
    myPopUp[2][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWelche Vorzeichen hat die Fis-Dur?\n", "Antwort:\n6 Kreuze: fis, cis, gis, dis, ais, eis\n");
    myPopUp[2][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    myPopUp[2][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWie heisst die Paralleltonart von D-Dur?\n", "Antwort:\nh-Moll\n");
    //vierte Kategorie
    myPopUp[3][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWelches Lied wurde beim\nWeihnachtsliederblasen nicht gespielt?\n\na) Ihr Kinderlein kommet\n\nb) Tochter Zion\n\nc) Last Christmas\n\nd) Oh du froehliche\n", "Antwort:\nLast Christmas\n");
    myPopUp[3][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWas war der erste Ton in der\nPosaunenchorprobe am 20.Dezember?\n", "Antwort:\nb\n");
    myPopUp[3][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    myPopUp[3][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWelches Stueck spielten wir am\n1. Dezember im Gottesdienst als Vorspiel?\n", "Antwort:\nHosanna\n");
    myPopUp[3][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWie viele Personen waren am\n6. Dezember in der Posaunenchorprobe?\n\na) 25\n\nb) 29\n\nc) 31\n\nd) 36\n", "Antwort:\n29\n");
    //fünfte Kategorie
    myPopUp[4][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Pantomime:\nEin Freiwilliger aus der Gruppe beschreibt\nseinen Gruppenmitgliedern einen\nGegenstand.\n", "Antwort:\nNotenstaender\n");
    myPopUp[4][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Pantomime:\nEin Freiwilliger aus der Gruppe beschreibt\nseinen Gruppenmitgliedern einen\nGegenstand.\n", "Antwort:\nInstrumentenkoffer\n");
    myPopUp[4][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Pantomime:\nEin Freiwilliger aus der Gruppe beschreibt\nseinen Gruppenmitgliedern einen\nGegenstand.\n", "Antwort:\nWasserklappe\n");
    myPopUp[4][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Pantomime:\nEin Freiwilliger aus der Gruppe beschreibt\nseinen Gruppenmitgliedern einen\nBegriff.\n", "Antwort:\nViolinschluessel\n");
    myPopUp[4][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    //sechste Kategorie
    myPopUp[5][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWelcher Vogel ist das Friedenssymbol?\n", "Antwort:\nTaube\n");
    myPopUp[5][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    myPopUp[5][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nMit welcher Waehrung wird in Ungarn\nbezahlt?\n\na) Dinar\n\nb) Euro\n\nc) Kuna\n\nd) Forint\n", "Antwort:\nForint\n");
    myPopUp[5][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWie heisst der laengste Fluss Europas?\n", "Antwort:\nWolga\n");
    myPopUp[5][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Frage:\nWas bedeutet das M in der roemischen\nZaehlweise?\n", "Antwort:\n1000\n");
    //siebte Kategorie
    myPopUp[6][0] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Joker\n", joker);
    myPopUp[6][1] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Musikzusammenschnitt:\nPasst bei folgendem Musikstueck\ngenau auf!\n", "Frage:\nWie viele verschiedene\nTiergeraeusche waren zu hoeren?\n", music5);
    myPopUp[6][2] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Aufgabe:\nKnaeckebrot-Musikstueck:\nErratet das geknusperte Lied.\n", "Loesung:\nO Tannenbaum\n", music7);
    myPopUp[6][3] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Problem loesen:\nDie Trompete funktioniert nicht mehr.\nMacht sie wieder spielbar.\n", "\n");
    myPopUp[6][4] = new PopUp(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, popupSheet,
                              "Musikzusammenschnitt:\nPasst bei folgendem Musikstueck\ngenau auf!\n", "Frage:\nWie heisst das Stueck, das zweimal\nvorkam?\n", music6);
}

int main(int argc, char *argv[]) {
	
	//Make sure the program waits for a quit
	bool quit = false;
	
	//Initialize
	screen = init(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
	//Load the files
    //Surfaces
	background = load_image("Jeopardyback.png");
    buttonsheet = load_image("button.png");
    buttonsheetTeamRot = load_image("teamRot.png");
    buttonsheetTeamGelb = load_image("teamGelb.png");
    buttonsheetTeamGruen = load_image("teamGruen.png");
    balkenRot = load_image("balkenRot.png");
    balkenGruen = load_image("balkenGruen.png");
    balkenGelb = load_image("balkenGelb.png");
    loeschen = load_image("loeschen.png");
    splashSheet = load_image("splash.png");
    //Text
    font = TTF_OpenFont("lazy.ttf", 28);
    catFont = TTF_OpenFont("lazy.ttf", 20);
    jeopFont = TTF_OpenFont("gyparody.ttf", 60);
    //Music
    music1 = Mix_LoadMUS("musik20.mp3");
    music2 = Mix_LoadMUS("musik60.mp3");
    music3 = Mix_LoadMUS("musik80.mp3");
    music4 = Mix_LoadMUS("musik100.mp3");
    music5 = Mix_LoadMUS("zusammen40.mp3");
    music6 = Mix_LoadMUS("zusammen100.mp3");
    music7 = Mix_LoadMUS("tannenb.mp3");
    joker = Mix_LoadMUS("troll.mp3");
    jeopMelodie = Mix_LoadMUS("Jeopardy.mp3");
    
                            
	//Apply the background to the screen
    apply_surface( 500, 15, TTF_RenderText_Solid(jeopFont, "Der (ganz) grosse Preis", white), background, NULL);
    //Kategorien
    //uint16_t text[] = { L'ä', L'ö', L'ü', '\0' };
    //string text = "ä";
    //char* q = const_cast<char*>(text.c_str());
    //uint16_t q[] = atoi(text.c_str());
    //uint16_t q = const_cast<uint16_t>(text.c_str());
    //apply_surface( 60, 120, TTF_RenderUNICODE_Solid(font, &q, white), background, NULL);
	apply_surface(25, 130, TTF_RenderText_Solid(catFont, "Musikgeschichte", white), background, NULL);
    apply_surface(240, 130, TTF_RenderText_Solid(catFont, "Musikstuecke", white), background, NULL);
    apply_surface(440, 130, TTF_RenderText_Solid(catFont, "Musiktheorie", white), background, NULL);
    apply_surface(630, 130, TTF_RenderText_Solid(catFont, "Poschor Moess", white), background, NULL);
    apply_surface(850, 130, TTF_RenderText_Solid(catFont, "Pantomime", white), background, NULL);
    apply_surface(1050, 130, TTF_RenderText_Solid(catFont, "Allgemein", white), background, NULL);
    apply_surface(1240, 130, TTF_RenderText_Solid(catFont, "Aufgepasst!", white), background, NULL);
    apply_surface(0, 0, background, screen, NULL);
    
    //Koordinaten des gerade gedrückten Buttons
    int coordX;
    int coordY;
    //Programmlogik
    int buttonState[categories][difficulities];
    bool handlePopUp = false;
    int counterRot = 0;
    int counterGruen = 0;
    int counterGelb = 0;
    bool startup = true;
                            
    //Make the Splash
    Splash mySplash(SCREEN_WIDTH/2-POPUP_WIDTH/2, SCREEN_HEIGHT/2-POPUP_HEIGHT/2, POPUP_WIDTH, POPUP_HEIGHT, splashSheet,  "Der grosse Preis\n\nVon Sarah und Matthias Kesenheimer\n3. Januar 2014\n", jeopMelodie);
    
	//Make the buttons
    Button* myButtons[categories][difficulities];
    for (int i = 0; i < categories; i++) {
        for (int j = 0; j < difficulities; j++) {
            if(j == 0) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "20", white));
            if(j == 1) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "40", white));
            if(j == 2) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "60", white));
            if(j == 3) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "80", white));
            if(j == 4) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "100", white));
            //Zusätzliche Schwierigkeiten
            if(j == 5) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "120", white));
            if(j == 6) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "140", white));
            if(j == 7) myButtons[i][j] = new Button(10 + i * 200, 170 + j * 150, 200, 150, buttonsheet, TTF_RenderText_Solid(font, "160", white));
            buttonState[i][j] = 0;
        }
    }
    
    SmallButton smallButtonTeamRot(1450, 843, 50, 37, buttonsheetTeamRot, TTF_RenderText_Solid(catFont, "+20", white));
    SmallButton smallButtonTeamGruen(1500, 843, 50, 37, buttonsheetTeamGruen, TTF_RenderText_Solid(catFont, "+20", white));
    SmallButton smallButtonTeamGelb(1550, 843, 50, 37, buttonsheetTeamGelb, TTF_RenderText_Solid(catFont, "+20", white));
    SmallButton smallButtonTeamRotMinus(1450, 880, 50, 37, buttonsheetTeamRot, TTF_RenderText_Solid(catFont, "-20", white));
    SmallButton smallButtonTeamGruenMinus(1500, 880, 50, 37, buttonsheetTeamGruen, TTF_RenderText_Solid(catFont, "-20", white));
    SmallButton smallButtonTeamGelbMinus(1550, 880, 50, 37, buttonsheetTeamGelb, TTF_RenderText_Solid(catFont, "-20", white));
    
    //Make the popups
    generatePopUps();
  
    
	//While the user hasn't quit
	while( quit == false ) {
		SDL_Delay(100);
        
		//While there's an event to handle
		while( SDL_PollEvent( &event ) ) {
            
            //If a key was pressed
            if( event.type == SDL_KEYDOWN )
            {
                //If Esacape was pressed
                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE ); //Vollbildmodus beenden
                }
                if( event.key.keysym.sym == SDLK_f )
                {
                    SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN|SDL_SWSURFACE ); //Vollbildmodus starten
                }
            }
            
            bool trigger = false; //wird auf true gesetzt wenn ein Button, Splash oder PopUp geklickt wurde. Dadurch wird verhindert, dass bei einem Durchlauf der while-Schleife die Buttons und das PopUp zusammen behandelt werden. Die Buttons und die PopUps müssen nacheinander behandelt werden, da ansonsten das gleiche Event für beide gelten würde.
            
            if (!handlePopUp && !trigger && startup) {
                int splashAction = mySplash.handle_events(&event);
                if (splashAction == 2) startup = false;
                trigger = true;
            }
            
			//Handle buttons events
            if (!handlePopUp && !trigger && !startup) {
                for (int i = 0; i < categories; i++) {
                    for (int j = 0; j < difficulities; j++) {
                        int tmp = 0;
                        tmp =  myButtons[i][j]->handle_events(&event);
                        if (tmp == 2 && buttonState[i][j] == 0) {
                            handlePopUp = true; //beim nächsten Event die Popups behandeln
                            trigger = true;
                            coordX = i; //Koordinaten des gedrückten Buttons speichern
                            coordY = j;
                            buttonState[i][j] = 2; //der eben gedrückte Button kann kein zweites mal gedrückt werden
                        }
                        
                    }
                }
                if (smallButtonTeamRot.handle_events(&event) == 2) counterRot += 20;
                if (smallButtonTeamGelb.handle_events(&event) == 2) counterGelb += 20;
                if (smallButtonTeamGruen.handle_events(&event) == 2) counterGruen += 20;
                if (smallButtonTeamRotMinus.handle_events(&event) == 2 && counterRot >= 20) counterRot -= 20;
                if (smallButtonTeamGelbMinus.handle_events(&event) == 2 && counterGelb >= 20) counterGelb -= 20;
                if (smallButtonTeamGruenMinus.handle_events(&event) == 2 && counterGruen >= 20) counterGruen -= 20;
			}
            
            //Handle popup events
            if (handlePopUp && !trigger && !startup) {
                int tmp = 0;
                tmp = myPopUp[coordX][coordY]->handle_events(&event);
                if (tmp == 2) { //Falls das PopUp geklickt wurde
                    handlePopUp = false; //beim nächsten Event wieder die Buttons behandeln
                    trigger = true;
                }
            }
            
			//If the user has Xed out the window
			if( event.type == SDL_QUIT ) {
				
				//Quit the program
				quit = true;
			}
		}
        
		
		//Show the button
        if (!handlePopUp && !startup) {
            apply_surface( 0, 0, background, screen, NULL );
            for (int i = 0; i < categories; i++) {
                for (int j = 0; j < difficulities; j++) {
                    myButtons[i][j]->show(screen);
                }
            }
            smallButtonTeamRot.show(screen);
            smallButtonTeamGelb.show(screen);
            smallButtonTeamGruen.show(screen);
            smallButtonTeamRotMinus.show(screen);
            smallButtonTeamGelbMinus.show(screen);
            smallButtonTeamGruenMinus.show(screen);
        }
		
        //Show the Splash
        if(!handlePopUp && startup) {
            SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x30, 0x2e, 0xc0 ) );
            mySplash.show(screen);
        }
        
        //Show the PopUp if Question was clicked
        if (handlePopUp && !startup) {
            myPopUp[coordX][coordY]->show(screen);
        }
        
        //Show the Pointbars
        if (!handlePopUp && !startup) {
            string points = convertInt(counterRot);
            char* q = const_cast<char*>(points.c_str());
            apply_surface(1450, 803 - counterRot/2, TTF_RenderText_Solid(catFont, q, white), screen, NULL);
            points = convertInt(counterGruen);
            q = const_cast<char*>(points.c_str());
            apply_surface(1500, 803 - counterGruen/2, TTF_RenderText_Solid(catFont, q, white), screen, NULL);
            points = convertInt(counterGelb);
            q = const_cast<char*>(points.c_str());
            apply_surface(1550, 803 - counterGelb/2, TTF_RenderText_Solid(catFont, q, white), screen, NULL);
            
            apply_surface(1450, 823 - counterRot/2, balkenRot, background, NULL);
            apply_surface(1500, 823 - counterGruen/2, balkenGruen, background, NULL);
            apply_surface(1550, 823 - counterGelb/2, balkenGelb, background, NULL);
            apply_surface(1450, 803 - counterRot/2, loeschen, background, NULL);
            apply_surface(1500, 803 - counterGruen/2, loeschen, background, NULL);
            apply_surface(1550, 803 - counterGelb/2, loeschen, background, NULL);
        }
        
		//Update the screen
		if( SDL_Flip( screen ) == -1 ) { return 1; }
		
	}
	
	//Free the surface and quit SDL
	clean_up();
    printf("[DEBUG] All done. Good bye.\n");
	return(0);
}