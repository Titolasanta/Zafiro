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

private:
    SDL_Rect posiciones[1][6];

};


#endif //TP_FASE1_TEST_SPRITEROJO_H
