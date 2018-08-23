#ifndef BUTTON_H
#define BUTTON_H
#include <SDL2/SDL.h>
#include <string>
#include "clienteEstado.h"
#include "commonTextTexture.h"

class Button {
public:
	Button(SDL_Renderer* renderer, Estado* e, int xi, int xf, int yi, int yf);
	~Button();
	bool handle(SDL_Event*);
	void render();
	bool pressed();
	void setPressColor(Uint8& r, Uint8& g, Uint8& b);
	void setHoverColor(Uint8& r, Uint8& g, Uint8& b);
	void setStandColor(Uint8& r, Uint8& g, Uint8& b);
	void setColors(int state, Uint8& r, Uint8& g, Uint8& b);
private:
	SDL_Rect cord;
	SDL_Renderer* renderer;
	int state;
	Estado* SiguienteDibujador;

	Uint8 red[3];
	Uint8 green[3];
	Uint8 blue[3];
};

#endif