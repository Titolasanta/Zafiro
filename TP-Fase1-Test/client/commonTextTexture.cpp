#include "commonTextTexture.h"
#include "commonSDLTTFException.h"
#include <SDL2/SDL_ttf.h>
#include "Texture.h"
#include "SDLException.h"


TextTexture::TextTexture(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
: Texture(renderer) {
	//Initialize
	mFont = TTF_OpenFont( "../txt/emulogic.ttf", 18 );
   // mFont = TTF_OpenFont( "../txt/OpenSans-Regular.ttf", 28 );
	if( mFont == nullptr ){
		throw SDLTTFError("no se pudo cargar el tipo de texto resources/ttf/OpenSans/OpenSans-Regular.ttf");
	}
	mFontColor = {r,g,b};
}

void TextTexture::free(){
    if( mTexture != nullptr ){
        SDL_DestroyTexture( mTexture );
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;

    }
}


TextTexture::TextTexture(TextTexture&& other) noexcept : Texture(std::move(other)){
    mFont = TTF_OpenFont( "../txt/emulogic.ttf", 18 );
	mFontColor = other.mFontColor;
	other.mFont = nullptr;
	other.free();
}

void TextTexture::loadFromRenderedText( std::string &textureText ) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( mFont, textureText.c_str(), mFontColor );
	if( textSurface == nullptr ){
			throw SDLTTFError("no se pudo cagar el texto que dice %s",textureText.c_str());
		}
	else{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == nullptr ){
			throw SDLError( "Unable to create texture from rendered text %s",textureText.c_str()  );
		}
		else{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
}

void TextTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip ) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	//Set clip rendering dimensions
	if( clip != nullptr ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	//Render to screen
	SDL_RenderCopyEx( renderer, mTexture, nullptr, &renderQuad, angle, center, flip );
}



