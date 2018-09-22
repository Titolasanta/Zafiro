//
// Created by tito on 04/09/18.
//

#ifndef TP_FASE1_TEST_SPRITEROJO_H
#define TP_FASE1_TEST_SPRITEROJO_H

#define ROJO_DER_FRAMES 6

#define DER 0


#include <SDL_rect.h>

class SpriteRojo {
public:
    SpriteRojo();
    SDL_Rect* mover(int dirreccion, int frame);
    SDL_Rect* quieto();
private:
    SDL_Rect frameMoviemiento[3][6];
    SDL_Rect parado;
    SDL_Rect faceDown;

};


#endif //TP_FASE1_TEST_SPRITEROJO_H
