#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <string>

class Texture {
public:
	//Initializes variables
	Texture( SDL_Renderer* renderer);

	//Deallocates memory
	virtual ~Texture();

	//Deallocates texture
	virtual void free() {
		throw Texture(renderer);
	}

	//Gets image dimensions
	int getWidth();
	int getHeight();
	Texture(Texture&& other);


protected:
	//textura a dibujar
	SDL_Texture* mTexture;
	//donde dibujar 
	SDL_Renderer* renderer;

	//Image dimensions
	int mWidth;
	int mHeight;
};

#endif 