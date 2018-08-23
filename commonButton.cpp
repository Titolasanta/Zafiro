#include <SDL2/SDL.h>
#include "commonButton.h"
#include "commonSDLException.h"
#include "commonTextTexture.h"
#include <stdio.h>
#include <string>
using std::string;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

void Button::setColors(int state, Uint8& r, Uint8& g, Uint8& b){
	switch(state) {

		case BUTTON_SPRITE_MOUSE_OUT:
		r = red[0];
		g = blue[0];
		b = green[0];
		break;

		case BUTTON_SPRITE_MOUSE_OVER_MOTION:
		r = red[1];
		g = blue[1];
		b = green[1];
		break;

		case BUTTON_SPRITE_MOUSE_DOWN:
		r = red[2];
		g = blue[2];
		b = green[2];
		break;

	}
}

	void Button::setPressColor(Uint8& r, Uint8& g, Uint8& b){
		red[2] = r;
		blue[2] = b;
		green[2] = g;		
	}
	void Button::setHoverColor(Uint8& r, Uint8& g, Uint8& b){
		red[1] = r;
		blue[1] = b;
		green[1] = g;
	}
	void Button::setStandColor(Uint8& r, Uint8& g, Uint8& b){
		red[0] = r;
		blue[0] = b;
		green[0] = g;
	}


bool static isInside(int x, int y, SDL_Rect mPosition){
	//Mouse is left of the button
	if( x < mPosition.x ){
		return false;
	}
	//Mouse is right of the button
	else if( x > (mPosition.x + mPosition.w) ){
		return false;
	}
	//Mouse above the button
	else if( y < mPosition.y )
	{
		return false;
	}
	//Mouse below the button
	else if( y > (mPosition.y + mPosition.h) ){
		return false;
	}
	return true;
}


Button::Button(SDL_Renderer* render,Estado* e, int xi, int xf, int yi, int yf) 
: renderer(render),state(BUTTON_SPRITE_MOUSE_OUT),SiguienteDibujador(e) {
	cord.x = xi;
	cord.y = yi;
	cord.w = (xf - xi);
	cord.h = (yf - yi);
	green[0] = 0;
	green[1] = 0;
	green[2] = 0;
	blue[0] = 0;
	blue[1] = 0xFF;
	blue[2] = 0xFF;
	red[0] = 0xFF;
	red[1] = 0xFF;
	red[2] = 0;
}

Button::~Button(){}


bool Button::handle(SDL_Event* e) {
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = isInside(x,y,cord);
		
		//Mouse is outside button
		if( !inside ){
			state = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				if(state != BUTTON_SPRITE_MOUSE_DOWN)
					state = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;
			
				case SDL_MOUSEBUTTONDOWN:
				state = BUTTON_SPRITE_MOUSE_DOWN;
				break;
				
				case SDL_MOUSEBUTTONUP:
					SiguienteDibujador->set(DIBUJAR_MAPA_NOIN_TURNO);
					return true;
			}
		}
	}
	return false;

}

void Button::render(){
	//Show current button sprite
	Uint8 r,g,b;
	setColors(state,r,g,b);	 
	SDL_SetRenderDrawColor( renderer, r, g, b, 0x88 );
	if( SDL_RenderFillRect(renderer, &cord) ) 
		throw SDLError("no se pudo dibujar boton en window");
}

bool Button::pressed(){
	if(state == BUTTON_SPRITE_MOUSE_UP)
		return true;
	return false;
}

