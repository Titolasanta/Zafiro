#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <string>
#include "commonImgTexture.h"
#include "commonTextTexture.h"

#include "commonButton.h"
enum Color { BLANCO,CELESTE };

class Window { 
private:
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;


public:
	Window(std::string& title, int xPos,int yPos,int width, int height);
	Window(std::string& title,int width, int height);
	Window(std::string& title);
	~Window();

	//dev por mov
	ImgTexture createImgTexture();
	ImgTexture createImgTexture(Uint8, Uint8, Uint8);
	TextTexture createTextTexture();


	void createRectangle(int xi, int xf, int yi, int yf);
	Button createButton(Estado* e, int xi, int xf, int yi, int yf);

	void redererClear();
	void surfaceFill(int Color);
	void updateRenderer();
	void updateSurface();
	//necesario liberar imagen luego.Por ahora leakea
	void loadImageToSurface(std::string& path);
	//no implementado
	void setRenderDrawColor( Uint8,Uint8,Uint8,Uint8);

};

#endif