#include "Texture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "SDLException.h"
#include "SDLIMGException.h"
using std::string;

Texture::Texture( SDL_Renderer* renderer): renderer(renderer){
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture(){
	//Deallocate
}

Texture::Texture(Texture&& other) noexcept: renderer(other.renderer)  {
	 mTexture = other.mTexture;
	 other.mTexture = NULL; 
}



int Texture::getWidth(){
	return mWidth;
}


int Texture::getHeight(){
	return mHeight;
}

