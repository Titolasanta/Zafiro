//
// Created by tito on 05/09/18.
//

#include <iostream>
#include <zconf.h>
#include "SpriteHandler.h"
#include "Sprite.h"
#include "../common/Logger.h"

#define SPRITE_PATH_AZUL "../spirites/spriteazul.png"
#define SPRITE_PATH_ROJO "../spirites/spriterojo.png"
#define SPRITE_PATH_VERDE "../spirites/spriteverde.png"
#define SPRITE_PATH_AMARILLO "../spirites/spriteamarillo.png"
//#define SPRITE_PATH_ENEMY "../spirites/spriteenemy.png"

#define characterWidth 20

extern Logger *gplogger;

SpriteHandler::SpriteHandler(Window* window) : spriteTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture1(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture3(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               enemySpriteTexture(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF))))
{
    spriteTexture[0] = &spriteTexture0;
    spriteTexture[1] = &spriteTexture1;
    spriteTexture[2] = &spriteTexture2;
    spriteTexture[3] = &spriteTexture3;
    spriteTexture0.loadFromFile(SPRITE_PATH_AZUL);
    spriteTexture1.loadFromFile(SPRITE_PATH_ROJO);
    spriteTexture2.loadFromFile(SPRITE_PATH_VERDE);
    spriteTexture3.loadFromFile(SPRITE_PATH_AMARILLO);
    //enemySpriteTexture.loadFromFile(SPRITE_PATH_ENEMY);
    gplogger->log(3,"Se crea SpriteHandler de la vista");
}

void SpriteHandler::render(Scene &scene, int id, int cameraX, int cameraY) {
    for (int i = 0; i-1 <  scene.getCurrentPlayers(); i++) {
        if (i == id - 1) continue;
        renderCharacterSprite(scene, i, cameraX, cameraY);
    }
    renderCharacterSprite(scene, id - 1, cameraX, cameraY);

    std::list<Enemy> le = scene.getEnemies();
    for (auto it = le.begin(); it != le.end(); it++)
        renderEnemySprite(*it, cameraX, cameraY);
}

void SpriteHandler::renderCharacterSprite(Scene &scene, int i, int cameraX, int cameraY){

    if (scene.isWalking(i+1) || scene.isAirborne(i+1)) currentFrame[i+1]++;
    else currentFrame[i+1] = 0;

    SDL_Rect *currentClip;
    int angle;

    if (scene.isLookingRight(i+1)) angle = 0;
    else angle = 180;

    if (scene.getAimDirection(i+1) == -1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3);
    else if (scene.getAimDirection(i+1) == 1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3 + 3);
    else {
        if (!scene.isWalking(i+1)) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
        else currentClip = spritePositionHandler.move(0, currentFrame[i+1] % 6);

        if (scene.isShooting(i+1) && !scene.isCrouching(i+1)) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    }
    if (scene.isCrouching(i+1))currentClip = spritePositionHandler.getFaceDown();
    if (scene.isAirborne(i+1)) currentClip = spritePositionHandler.move(2, currentFrame[i+1] % 4);
    if (scene.isJugadorGrisado(i + 1)) currentClip = spritePositionHandler.getGrisado();

    // printf("%d,%d\n",scene.getPositionX(i+1),scene.getPositionY(i+1));
    spriteTexture[i]->render(scene.getPositionX(i+1) - cameraX - characterWidth / 2, scene.getPositionY(i+1) - cameraY,
                             currentClip, angle);
}

void SpriteHandler::renderEnemySprite(Enemy e, int cameraX, int cameraY){

    if (e.isAirborne()) e.incrementCurrentFrame();
    else e.setCurrentFrame(0);

    SDL_Rect *currentClip;
    int angle;

    if (e.isLookingRight()) angle = 0;
    else angle = 180;

    //if (scene.getAimDirection(i+1) == -1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3);
    //else if (scene.getAimDirection(i+1) == 1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3 + 3);
    //else {
    //if (!scene.isWalking(i+1)) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    /*else*/ currentClip = spritePositionHandler.move(0, e.getCurrentFrame() % 6);

    //if (e.isShooting() ) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    //}
    //if (scene.isCrouching(i+1))currentClip = spritePositionHandler.getFaceDown();
    if (e.isAirborne() ){
        e.incrementCurrentFrame();
        currentClip = spritePositionHandler.move(2, e.getCurrentFrame()% 4);
    }
    //if (scene.isJugadorGrisado(i + 1)) currentClip = spritePositionHandler.getGrisado();

    // printf("%d,%d\n",scene.getPositionX(i+1),scene.getPositionY(i+1));
    enemySpriteTexture.render(e.getPosX() - cameraX - characterWidth / 2, e.getPosY() - cameraY,
                              currentClip, angle);
}