#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL2/SDL.h>
#include <string>

class Texture {

protected:
	//textura a dibujar
	SDL_Texture* mTexture;
	//donde dibujar
	SDL_Renderer* renderer;

	//Image dimensions
	int mWidth;
	int mHeight;

public:
	//Initializes variables
	explicit Texture( SDL_Renderer* renderer);

	//Deallocates memory
	virtual ~Texture();

	//Deallocates texture
	virtual void free() = 0;

	//Gets image dimensions
	Texture(Texture&& other) noexcept;

};

#endif 