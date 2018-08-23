#include "commonTexture.h"
#include "commonImgTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "commonSDLException.h"
#include "commonSDLIMGException.h"
using std::string;

ImgTexture::ImgTexture( SDL_Renderer* renderer): Texture(renderer){
	trans = false;
}


ImgTexture::ImgTexture(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) 
: Texture(renderer) {
	trans = true;
	transColor[0] = r;
	transColor[1] = g;
	transColor[2] = b;

}

ImgTexture::ImgTexture(ImgTexture&& other) : Texture(std::move(other)) {
	for(int i = 0; i < 3; i++ )
		this->transColor[i] = other.transColor[i];
	this->trans = other.trans;
	//Image dimensions
	mWidth = other.mWidth;
	mHeight = other.mHeight;
	other.free();
}

void ImgTexture::render( int x, int y ){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
}


void ImgTexture::render(int x, int y, int xInicial, int xFinal, int yInicial, int yFinal){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, xFinal - xInicial, yFinal - yInicial };
	SDL_Rect segment = {xInicial,  yInicial, xFinal - xInicial, yFinal - yInicial };	//Render to screen
	SDL_RenderCopy( renderer, mTexture, &segment, &renderQuad );
}


void ImgTexture::render( int x, int y, int xInicial, int xFinal, int yInicial, int yFinal, double angle) {

	SDL_Rect renderQuad = { x, y, xFinal - xInicial, yFinal - yInicial };
	SDL_Rect segment = {xInicial,  yInicial, xFinal - xInicial, yFinal - yInicial };
	if(angle >= 90)
		SDL_RenderCopyEx( renderer, mTexture, &segment, &renderQuad, angle-180, NULL, SDL_FLIP_HORIZONTAL );
	else if(angle <= -90)
		SDL_RenderCopyEx( renderer, mTexture, &segment, &renderQuad, angle+180, NULL, SDL_FLIP_HORIZONTAL );
	else
		SDL_RenderCopyEx( renderer, mTexture, &segment, &renderQuad, angle, NULL, SDL_FLIP_NONE );
}



void ImgTexture::render( int x, int y, double angle) {

	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if(angle >= 90)
		SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, angle-180, NULL, SDL_FLIP_HORIZONTAL );
	else if(angle <= -90)
		SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, angle+180, NULL, SDL_FLIP_HORIZONTAL );
	else
		SDL_RenderCopyEx( renderer, mTexture, NULL, &renderQuad, angle, NULL, SDL_FLIP_NONE );
}


void ImgTexture::loadFromFile( std::string path ){
	//Get rid of preexisting texture
	free();
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ){
		throw SDLIMGError("Carga de imagen %s fallo",path.c_str());
	}
	//Color key image
	if(trans){
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, transColor[0], transColor[1], transColor[2] ) );
	}
	//Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	if( mTexture == NULL ){
		throw SDLError("Fallo crear textura apartir de %s",path.c_str());
	}
	//Get image dimensions
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;	

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

}

void ImgTexture::free(){
	//Free texture if it exists
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

