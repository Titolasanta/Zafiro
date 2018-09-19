#include "SdlImgInit.h"
#include "SDLIMGException.h"
#include "Logger.h"
#include <SDL2/SDL_image.h>

extern Logger* gplogger;

SdlImgInit::~SdlImgInit(){
	IMG_Quit();

	gplogger->log(1,"se destruye sdlimginit\n");
}


SdlImgInit::SdlImgInit(){
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ){
		throw SDLIMGError("No se pudo iniciar SDL_IMG");
	}

	gplogger->log(1,"se crea sdlimginit\n");
}