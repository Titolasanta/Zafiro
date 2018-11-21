#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDLException.h"
#include "SdlInit.h"
#include "../common/Logger.h"

extern Logger *gplogger;

SdlInit::~SdlInit(){

	gplogger->log(3,"Se destruye SdlInit");
	SDL_Quit();
}

SdlInit::SdlInit(){
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		gplogger->log(1,"no se inicializa sdl");
		throw SDLError( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
		gplogger->log(1,"no se logra sdlhint");
		throw SDLError("SDL_SetHint fallo");
	}

	gplogger->log(3,"Se crea SdlInit");
}
