#include "SdlImgInit.h"
#include "SDLIMGException.h"
#include <SDL2/SDL_image.h>

SdlImgInit::~SdlImgInit(){
	IMG_Quit();
}


SdlImgInit::SdlImgInit(){
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		throw SDLIMGError("No se pudo iniciar SDL_IMG");
	}
}