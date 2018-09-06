#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <string>

class Texture {
public:
	//Initializes variables
	explicit Texture( SDL_Renderer* renderer);

	//Deallocates memory
	virtual ~Texture();

	//Deallocates texture
	virtual void free() {
		//significa un error
		throw Texture(renderer);
	}

	//Gets image dimensions
	int getWidth();
	int getHeight();
	Texture(Texture&& other) noexcept;


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