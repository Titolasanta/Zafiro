#include "commonButton.h"
#include "commonWindow.h"
#include "commonTexture.h"
#include "commonSdlInit.h"
#include "commonSdlImgInit.h"
#include "commonSdlTtfInit.h"
#include "commonImgTexture.h"
#include "commonTextTexture.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

#define WINDOW_WIDTH 790
#define WINDOW_HEIGHT 440

#define BUTTONWIDTH 90
#define BUTTONHEIGHT 40

#define IMGWORM "/home/tito/Desktop/Tallar/github/resources/wairlnk.png"


#define IMGFONDOPATH "/home/tito/Desktop/Tallar/github/resources/wallpaper.jpg"

#define JLISTDELTA 50
#define JLISTWIDTH 150
#define JLISTHEIGHT 30

int main() {
	
	Estado siguienteEstado(1);
	//inicios, creando clases para inicializar estas variables
	//no me tengo q acordar de borrarlos despues
	SdlTtfInit y;
	SdlInit z;
	SdlImgInit x;

	//ventana
	string tit("Worms: Lobby Host");
	Window window(tit,WINDOW_WIDTH,WINDOW_HEIGHT);
	//window.redererClear();
	
	//fondo
	ImgTexture t = window.createImgTexture();
	string s = IMGFONDOPATH;
	t.loadFromFile(s);
	
	//dibujito
	ImgTexture wormsito = window.createImgTexture(128,128,192);
	s = IMGWORM;
	wormsito.loadFromFile(s);	

	//boton comenzar
	TextTexture tt = window.createTextTexture();
	int bx = WINDOW_WIDTH - BUTTONWIDTH * 2;
	int by = WINDOW_HEIGHT - BUTTONHEIGHT * 2;
	string strin("Comenzar");
	tt.loadFromRenderedText(strin);
	Button b = window.createButton(&siguienteEstado, bx, bx + JLISTWIDTH, by, by + JLISTHEIGHT);
	

	int j = 2;
	SDL_Event e;
	bool quit = false;

	while( !quit ){
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ){
			//User requests quit
			if( e.type == SDL_QUIT ){
				quit = true;
				siguienteEstado.set(DIBUJAR_FINAL);
			}
			if(b.handle( &e ))
				quit = true;
		}

		window.redererClear();
		//imagen
		t.render(0,0);

		//dibujos
		for(int i = 0; i < j; i++)
			wormsito.render(0,i*60,0,60,0,60);
		b.render();
		tt.render( bx, by);	

		window.updateRenderer();
	
	}
	
}

