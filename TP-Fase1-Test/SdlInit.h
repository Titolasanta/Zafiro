#ifndef SDLINIT_H
#define SDLINIT_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDLException.h"
#include "Window.h"



class SdlInit {
public:
	SdlInit();
	void delay(size_t milisec);
	~SdlInit();
};


#endif