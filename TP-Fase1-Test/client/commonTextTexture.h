#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Texture.h"

class TextTexture : public Texture {
public:
	//Initializes variables
	TextTexture(SDL_Renderer* renderer, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

	//Deallocates memory

	//Loads image at specified path
	void loadFromRenderedText( std::string &text);

	//Deallocates texture
	void free();
	//Renders texture at given point
	void render( int x, int y, SDL_Rect* clip = NULL,
			double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	TextTexture(TextTexture&& other);
private:
	TTF_Font* mFont = NULL;
	SDL_Color mFontColor;
};

#endif 