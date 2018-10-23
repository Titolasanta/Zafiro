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

private:
    SDL_Rect frameMoviemiento[4][6];
    SDL_Rect parado;
    SDL_Rect faceDown;
    SDL_Rect grisado;

};


#endif //TP_FASE1_TEST_SPRITEROJO_H
