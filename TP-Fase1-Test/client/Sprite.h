//
// Created by tito on 04/09/18.
//

#ifndef TP_FASE1_TEST_SPRITEROJO_H
#define TP_FASE1_TEST_SPRITEROJO_H

#define ROJO_DER_FRAMES 6

#define DER 0


#include <SDL2/SDL_rect.h>

class Sprite {

public:
    Sprite();
    SDL_Rect* move(int, int);
    SDL_Rect* quieto();
    SDL_Rect* getFaceDown();
    SDL_Rect* getGrisado();
    SDL_Rect* getMuerto();
    SDL_Rect* getMovingEnemySprite(int);
    SDL_Rect* getStaticEnemySprite(int);
    SDL_Rect* getDestroyedEnemySprite(int);
    SDL_Rect* getMovingEnemyShootingSprite();


private:
    SDL_Rect frameMoviemiento[5][6];
    SDL_Rect parado;
    SDL_Rect faceDown;
    SDL_Rect grisado;
    SDL_Rect muerto;
    SDL_Rect movingEnemies[7];
    SDL_Rect movingEnemyShooting;
    SDL_Rect staticEnemies[12];
    SDL_Rect destroyedEnemies[3];

};


#endif //TP_FASE1_TEST_SPRITEROJO_H
