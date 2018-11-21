#ifndef IMGTEXTURE_H
#define IMGTEXTURE_H
#include <SDL2/SDL.h>
#include "Texture.h"
#include <string>

class ImgTexture : public Texture {

protected:
    Uint8 transColor[3];
    bool trans;
    int mWidth;
    int mHeight;

public:
	ImgTexture(SDL_Renderer* renderer, Uint8, Uint8, Uint8);
	explicit ImgTexture(SDL_Renderer* renderer);
	void loadFromFile( std::string path);
	void free() override;
	void render( int x, int y );
	void render( int x, int y ,double ang);
	void render(int x, int y, int xi,int xf,int yi,int yf);
	void render(int x, int y, const SDL_Rect* rect);
    void render( int x, int y,SDL_Rect *rect, double angle);
	void renderBackground( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr , SDL_RendererFlip flip = SDL_FLIP_NONE);
	ImgTexture(ImgTexture&& other) noexcept;
	//si pide un giro mayor o menor a 90,-90 rota la img horizontalmente(sirve pa gusano)
	void render( int x, int y, int xInicial, int xFinal, int yInicial, int yFinal, double angle);
	//Gets image dimensions

};

#endif 