#ifndef TEXTTEXTURE_H
#define TEXTTEXTURE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Texture.h"

class TextTexture : public Texture {

private:
	TTF_Font* mFont = nullptr;
	SDL_Color mFontColor;

public:
	explicit TextTexture(SDL_Renderer* renderer, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);
	void loadFromRenderedText( std::string &text);
	void free() override;
	void render( int x, int y, SDL_Rect* clip = nullptr,
			double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );
	TextTexture(TextTexture&& other) noexcept;

};

#endif 