#ifndef SDLWINDOW_H
#define SDLWINDOW_H
#include <string>
#include "ImgTexture.h"
#include "commonTextTexture.h"

class Window {

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;


public:
	Window(std::string& title, int xPos,int yPos,int width, int height);
	Window(std::string title,int width, int height);
	explicit Window(std::string& title);
	ImgTexture createImgTexture();
	ImgTexture createImgTexture(Uint8, Uint8, Uint8);
	TextTexture createTextTexture();
	void createRectangle(int xi, int xf, int yi, int yf);
	void redererClear();
	void updateRenderer();
	~Window();

};

#endif