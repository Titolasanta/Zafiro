#include "Texture.h"
#include "ImgTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "SDLException.h"
#include "SDLIMGException.h"
#include "Logger.h"

using std::string;

extern Logger *gplogger;
ImgTexture::ImgTexture( SDL_Renderer* renderer): Texture(renderer){

	gplogger->log(3,"Se crea una ImgTexture normal");
	trans = false;
}


ImgTexture::ImgTexture(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) 
: Texture(renderer) {

	gplogger->log(3,"Se crea una ImgTexture con rgb");
	trans = true;
	transColor[0] = r;
	transColor[1] = g;
	transColor[2] = b;

}

ImgTexture::ImgTexture(ImgTexture&& other) : Texture(std::move(other)) {

	gplogger->log(3,"Se crea una ImgTexture por movimiento");
	for(int i = 0; i < 3; i++ )
		this->transColor[i] = other.transColor[i];
	this->trans = other.trans;
	//Image dimensions
	mWidth = other.mWidth;
	mHeight = other.mHeight;
	other.mTexture == NULL;
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

//Render camera section
void ImgTexture::renderBackground( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void ImgTexture::render(int x, int y, const SDL_Rect* rect){
    SDL_Rect renderQuad = { x, y, rect->w, rect->h };
    SDL_RenderCopy( renderer, mTexture, rect,  &renderQuad);
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

void ImgTexture::render( int x, int y,SDL_Rect *rect, double angle) {

	SDL_Rect renderQuad = { x, y, rect->w, rect->h };
	if(angle >= 90)
		SDL_RenderCopyEx( renderer, mTexture, rect, &renderQuad , angle-180, NULL, SDL_FLIP_HORIZONTAL );
	else if(angle <= -90)
		SDL_RenderCopyEx( renderer, mTexture,  rect, &renderQuad,  angle+180, NULL, SDL_FLIP_HORIZONTAL );
	else
		SDL_RenderCopyEx( renderer, mTexture, rect, &renderQuad, angle, NULL, SDL_FLIP_NONE );
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
		loadedSurface = IMG_Load( "../escenario/negro.png" );
		gplogger->log(1,"No se encontro una imagen, se cargó una imagen por defecto");
		//throw SDLIMGError("Carga de imagen %s fallo",path.c_str());
	}
	//Color key image
	if(trans){
	//	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, transColor[0], transColor[1], transColor[2] ) );
	}
	//Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	if( mTexture == NULL ){
		gplogger->log(1,"No se abrió una textura");
		throw SDLError("Fallo crear textura apartir de %s",path.c_str());
	}
	//Get image dimensions
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;	

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	gplogger->log(3,"Se carga file a una ImgTexture");
}

void ImgTexture::free(){
	//Free texture if it exists
	if( mTexture != NULL ){
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
		gplogger->log(3,"Se libero una ImgTexture");
	} else
		gplogger->log(3,"Se libero una ImgTexture ya vacia");
}

