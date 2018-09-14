//
// Created by tito on 04/09/18.
//

#include <iostream>
#include "SpriteRojo.h"

SDL_Rect* SpriteRojo::mover(int dirreccion, int frame){

    return &frameMoviemiento[dirreccion][frame];

    }
    SDL_Rect* SpriteRojo::quieto(){

        return &parado;
}

    
SpriteRojo::SpriteRojo()
: frameMoviemiento { { {1,43,26,35},
                 {18,43,19,35},
                 {38,47,20,31},
                 {59,44,19,35},
                 {76,44,18,34},
                 {95,47,20,31} } },
parado{0,5,23,37}
                 {}
