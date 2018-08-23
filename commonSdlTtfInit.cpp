#include "commonSdlTtfInit.h"
#include "commonSDLTTFException.h"
#include <SDL2/SDL_ttf.h>

SdlTtfInit::~SdlTtfInit(){
	TTF_Quit();
}


SdlTtfInit::SdlTtfInit(){
	if( TTF_Init() == -1 )
		throw SDLTTFError("No se pudo iniciar SDL_TTF");
}