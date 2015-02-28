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
