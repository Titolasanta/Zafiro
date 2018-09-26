#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDLException.h"
#include "Exception.h"
#include "SDLIMGException.h"
#include "Window.h"
#include <SDL2/SDL_image.h>
//#include "commonTextTexture.h"
//#include "commonButton.h"
#include "ImgTexture.h"
#include "Logger.h"
#include <string>
using std::string;


#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 400

extern Logger *gplogger;

void static setRender(SDL_Renderer*& renderer, SDL_Window* window, string title) {
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( renderer == NULL ){
		gplogger->log(1,"no se crea render de ventana");
		throw SDLError("No se pudo crear el renderer de la ventana %s",title.c_str());
	}

	//Transparencia y color de las figuras dibujadas
	//por default: blanco y opaco 100%
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );


}
void Window::setRenderDrawColor(Uint8 a, Uint8 b, Uint8 c, Uint8 d) {

	gplogger->log(3,"Se setea render draw color de window");
	SDL_SetRenderDrawColor(renderer, a, b, c, d);
}


Window::~Window(){

	gplogger->log(3,"Se intenta destruir Window");
	if(window != NULL) {
		SDL_DestroyWindow(window);
	} else

		gplogger->log(3,"No habia Window que destruir");
}


Window::Window(string& title, int xPos,int yPos,int width, int height){
	window = SDL_CreateWindow( title.c_str(), xPos, yPos, width, height, SDL_WINDOW_SHOWN );
	if( window == NULL ){
		gplogger->log(1,"no se crea ventana");
		throw SDLError( "Window could not be created! SDL_Error: " );
	}	
	//guardo copia de la superficie, probablemnte prefiero el renderer
	screenSurface = SDL_GetWindowSurface( window );

	//creo un renderer de la vetana
	setRender(renderer, window, title);

	gplogger->log(3,"Se creo window con 5 parametros");
}

Window::Window(string title ,int width, int height){
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN );
	if( window == NULL ){
		gplogger->log(1,"no se crea ventana");
		throw SDLError( "Window could not be created! SDL_Error: " );
	}			
	//guardo copia de la superficie, probablemnte prefiero el renderer
	screenSurface = SDL_GetWindowSurface( window );

	//creo un renderer de la vetana
	setRender(renderer, window, title);
	gplogger->log(3,"Se creo window con 3 parametros");
}

Window::Window(string& title){
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED,
	 SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL ){
		gplogger->log(1,"no se crea ventana");
		throw SDLError( "Window could not be created! " );
	}		
	//guardo copia de la superficie, probablemnte prefiero el renderer
	screenSurface = SDL_GetWindowSurface( window );

	//creo un renderer de la vetana
	setRender(renderer, window, title);
	gplogger->log(3,"Se creo window con 1 parametro");

}





ImgTexture Window::createImgTexture(){
	gplogger->log(3,"Window devuelve una imgTexture");
	return std::move(ImgTexture(renderer));
}

ImgTexture Window::createImgTexture(Uint8 r, Uint8 g, Uint8 b){
	gplogger->log(3,"Window devuelve una imgTexture");
	return std::move(ImgTexture(renderer, r, g, b));
}
/*
TextTexture Window::createTextTexture(){
	return std::move(TextTexture(renderer));
}
*/
void Window::surfaceFill(int Color){
	if( window == NULL || screenSurface == NULL ){
		throw SDLError( "initialize window" );
	}		

	switch(Color) {
		case BLANCO	:
	    	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
	      	break;
	    case CELESTE :
	    	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x0, 0xFF, 0xFF ) );
	      	break;
	    default	:
			gplogger->log(1,"se pide un colo indefinido para rellenar la ventana");
			throw OSError("El color: %d no fue definido",Color);
	   	}
}
void Window::redererClear(){
		SDL_RenderClear( renderer );
}

void Window::updateSurface(){
	SDL_UpdateWindowSurface( window );
}

void Window::updateRenderer(){
	SDL_RenderPresent( renderer );
}




void Window::createRectangle( int xi,int xf,int yi,int yf) {
	xf = (xf - xi);
	yf = (yf - yi);
	SDL_Rect segment = {xi, yi, xf, yf};
	if(SDL_RenderFillRect(renderer, &segment) ){
		gplogger->log(1,"no se dibuja un rectangulo de ventana");
		throw SDLError("no se pudo dibujar un rectangulo en window");
	}
}
/*
Button Window::createButton(Estado* e, int xi, int xf, int yi, int yf){
	return std::move(Button(renderer, e, xi,xf,yi,yf));
}
 */