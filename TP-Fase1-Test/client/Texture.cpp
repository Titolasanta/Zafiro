#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SDLException.h"
#include "SDLIMGException.h"
#include "../common/Logger.h"

using std::string;
extern Logger *gplogger;

Texture::Texture( SDL_Renderer* renderer): renderer(renderer){
	//Initialize
	gplogger->log(3,"Se crea Textura");
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture(){

	gplogger->log(3,"Se destruye Textura");
	//Deallocate

}

Texture::Texture(Texture&& other) noexcept: renderer(other.renderer)  {

	gplogger->log(3,"Se construye Textura por movimiento");
	 mTexture = other.mTexture;
	 other.mTexture = NULL; 
}



int Texture::getWidth(){
	return mWidth;
}


int Texture::getHeight(){
	return mHeight;
}

