#include "SDL_Init.h"

SDL_Surface *load_image( string filename ) {
	
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;
	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;
	//Load the image
	loadedImage = IMG_Load( filename.c_str() );
	
	//If the image loaded
	if( loadedImage != NULL ) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat( loadedImage );
		//Free the old image
		SDL_FreeSurface( loadedImage );
		
		//If the image was optimized just fine
		if( optimizedImage != NULL ) {
			//Map the color key
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
		}
	}
	
	//Return the optimized image
	return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ) { //Clip ist ein Rechteck mit bestimmten Maßen und einer bestimmten Position
	
	//Holds offsets
	SDL_Rect offset; //der offset gibt relativ zum Screen die Position des Rechteckes an. Also wird an x,y ein Rechteck definiert, in das ein Bild geladen werden kann
	
	//Get offsets
	offset.x = x;
	offset.y = y;
	
	//Blit
	SDL_BlitSurface( source, clip, destination, &offset ); //If "clip" is NULL, then it will blit the entire source surface. Wird ein bestimmtes clip, also ein bestimmtes Rechteck definiert, so wird aus der Sorucedatei nur die Pixel geladen, die über clip definiert wurden
}

SDL_Surface* init(int SCREEN_WIDTH, int SCREEN_HEIGHT, int SCREEN_BPP) {
    
    //Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) { return NULL; }

    //Initialize SDL_ttf
	if( TTF_Init() == -1 ) { return NULL; }
	
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) { return NULL; }
    
	//Set the window caption
	SDL_WM_SetCaption( "Jeopardy", NULL );
	//If everything initialized fine
	return SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_FULLSCREEN|SDL_SWSURFACE ); //SDL_FULLSCREEN|
}