//
// Created by tito on 04/09/18.
//

#include <iostream>
#include "Sprite.h"

SDL_Rect* Sprite::move(int dirreccion, int frame) {
    return &frameMoviemiento[dirreccion][frame];
}

SDL_Rect* Sprite::quieto() {
    return &parado;
}

SDL_Rect* Sprite::getFaceDown() {
    return &faceDown;
}

Sprite::Sprite()
: frameMoviemiento { {{1*2,43*2,16*2,35*2}, //Corriendo hacia adelante
                      {18*2,43*2,19*2,35*2}, //(segunda linea sprite sheet)
                      {38*2,47*2,20*2,31*2},
                      {59*2,44*2,16*2,34*2},
                      {76*2,44*2,18*2,34*2},
                      {95*2,47*2,20*2,31*2} },
                     {{1*2,149*2,16*2,35*2}, //apuntando hacia arriba
                      {18*2,149*2,19*2,35*2}, // (quinta linea sprite sheet)
                      {38*2,151*2,20*2,33*2},
                      {1*2,221*2,20*2,35*2}, //apuntando hacia abajo
                      {22*2,221*2,21*2,35*2}, // (septima linea sprite sheet)
                      {44*2,223*2,21*2,33*2} },

                     {{117*2,52*2,16*2,20*2},//secuencia de salto
                      {135*2,44*2,20*2,26*2},
                      {157*2,52*2,16*2,20*2},
                      {157*2,54*2,17*2,16*2},
                      {0,0,0,0},
                      {0,0,0,0}}
                      },
parado{0*2,8*2,23*2,34*2},
faceDown{79*2,25*2,32*2,16*2}
                 {}
