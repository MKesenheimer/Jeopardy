# Jeopardy
C++ Version des bekannten Spiels "Jeopardy" bzw. zu deutsch "Der große Preis". Dieses Spiel wurde für einen Gesellschaftsabend erstellt - die Fragen sind deshalb entsprechend speziell.

## Systemvoraussetzungen
In der gegenwärtigen Version kann das Programm nur unter Mac OSX kompiliert werden. Um das Programm unter Windows oder Linux zu kompilieren, müssen unter Umständen einige Änderungen vorgenommen werden (bisher noch nicht getestet).
Die SDL-Libraries (https://www.libsdl.org, http://de.wikipedia.org/wiki/Simple_DirectMedia_Layer) müssen installiert sein.

## Kompilation
Um das Programm zu kompilieren, muss ggf. das Makefile für das jeweilige Betriebssystem angepasst werden.
Wichtige Startpunkte sind hier:
- der Kompiler (COMPILER): z.B: g++
- die SDL Libraries (FRM): SDL, SDL_image, SDL_ttf, SDL_mixer
- die Library "Cocoa" wird für die graphische Benutzeroberfläche von Mac OSX gebraucht

Im Terminal

$ make

eintippen kompiliert das Programm.

Mit

$ make clean

werden die erzeugten Objekte und das Programm gelöscht.

Tippt man

$ make do

ein, wird das Programm kompiliert und anschließend ausgeführt.

## Steuerung
Die Felder werden mit der Maus ausgewählt und mit der linken Maustaste aufgedeckt. Ein Rechtsklick auf das Fragenfeld deckt die Antwort auf und ein erneuter Linksklick schließt das Antwortfeld wieder. Punkte können den mitspielenden Gruppen in der Ecke links unten vergeben werden. Mit den Tasten +10 und -10 kann der Punktestand um jeweils zehn Punkte erhöht bzw. erniedrigt werden.
Der Vollbildmodus wird mit ESC beendet.