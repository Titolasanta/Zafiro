//
// Created by tito on 04/09/18.
//

#ifndef TP_FASE1_TEST_SPRITEROJO_H
#define TP_FASE1_TEST_SPRITEROJO_H

#define ROJO_DER_FRAMES 6

#define DER 0


#include <SDL_rect.h>

class Sprite {
public:
    Sprite();
    SDL_Rect* move(int direction, int frame);
    SDL_Rect* quieto();
    SDL_Rect* getFaceDown();
    SDL_Rect* getGrisado();
    SDL_Rect* getMuerto();

private:
    SDL_Rect frameMoviemiento[5][6];
    SDL_Rect parado;
    SDL_Rect faceDown;
    SDL_Rect grisado;
    SDL_Rect muerto;

};


#endif //TP_FASE1_TEST_SPRITEROJO_H
