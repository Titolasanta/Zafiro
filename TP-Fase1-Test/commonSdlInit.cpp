#include <SDL2/SDL.h>
#include <stdio.h>
#include "commonSDLException.h"
#include "commonSdlInit.h"


SdlInit::~SdlInit(){
	SDL_Quit();
}

void SdlInit::delay(size_t milisec){
	SDL_Delay(milisec);
}

SdlInit::SdlInit(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		throw SDLError( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		throw SDLError("SDL_SetHint fallo");
	}
}
