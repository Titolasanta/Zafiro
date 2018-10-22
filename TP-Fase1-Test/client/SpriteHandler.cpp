//
// Created by tito on 05/09/18.
//

#include <iostream>
#include "SpriteHandler.h"
#include "Sprite.h"
#include "../common/Logger.h"

#define SPRITE_PATH "../spirites/sprites.png"

#define characterWidth 20

extern Logger *gplogger;

SpriteHandler::SpriteHandler(Window* window) : spriteTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture1(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture3(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF))))
                                               {
    spriteTexture[0] = &spriteTexture0;
    spriteTexture[1] = &spriteTexture1;
    spriteTexture[2] = &spriteTexture2;
    spriteTexture[3] = &spriteTexture3;
    spriteTexture0.loadFromFile(SPRITE_PATH);
    spriteTexture1.loadFromFile(SPRITE_PATH);
    spriteTexture2.loadFromFile(SPRITE_PATH);
    spriteTexture3.loadFromFile(SPRITE_PATH);
    gplogger->log(3,"Se crea SpriteHandler de la vista");
}

void SpriteHandler::render(Scene &scene, int cameraX, int cameraY) {

    for (int i = 0; i-1 <  scene.getCurrentPlayers(); i++) {
        if (scene.isWalking(i+1) || scene.isAirborne(i+1))
            currentFrame[i+1]++;
        else
            currentFrame[i+1] = 0;

        SDL_Rect *currentClip;
        int angle;

        if (scene.isLookingRight(i+1))
            angle = 0;
        else
            angle = 180;

        if (scene.getAimDirection(i+1) == -1)
            currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3);
        else if (scene.getAimDirection(i+1) == 1)
            currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3 + 3);
        else {
            if (!scene.isWalking(i+1))
                currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
            else
                currentClip = spritePositionHandler.move(0, currentFrame[i+1] % 6);
            if (scene.isShooting(i+1) && !scene.isCrouching(i+1))
                currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
        }
        if (scene.isCrouching(i+1))
            currentClip = spritePositionHandler.getFaceDown();

        if (scene.isAirborne(i+1)) {
            currentClip = spritePositionHandler.move(2, currentFrame[i+1] % 4);
        }
       // printf("%d,%d\n",scene.getPositionX(i+1),scene.getPositionY(i+1));
        spriteTexture[i+1]->render(scene.getPositionX(i+1) - cameraX - characterWidth / 2, scene.getPositionY(i+1) - cameraY,
                             currentClip, angle);
    }
}
