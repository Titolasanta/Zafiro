#ifndef IMGTEXTURE_H
#define IMGTEXTURE_H
#include <SDL2/SDL.h>
#include "commonTexture.h"
#include <string>

class ImgTexture : public Texture {
public:
	//Initializes variables
	ImgTexture(SDL_Renderer* renderer, Uint8, Uint8, Uint8);
	ImgTexture(SDL_Renderer* renderer);
	//Loads image at specified path
	void loadFromFile( std::string path);
	void free();
	//Renders texture at given point
	void render( int x, int y );
	void render( int x, int y ,double ang);

	void render(int x, int y, int xi,int xf,int yi,int yf);
	ImgTexture(ImgTexture&& other);
	//si pide un giro mayor o menor a 90,-90 rota la img horizontalmente(sirve pa gusano)
	void render( int x, int y, int xInicial, int xFinal, int yInicial, int yFinal, double angle);
	//Gets image dimensions

protected:
	Uint8 transColor[3];
	bool trans;
	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif 