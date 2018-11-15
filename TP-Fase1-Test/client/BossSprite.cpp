//
// Created by tito on 14/11/18.
//

#include "BossSprite.h"
#include "Window.h"
#include "../common/Logger.h"

#define SPRITE_PATH_AZUL "../spirites/spriteazul.png"
#define SPRITE_PATH_ROJO "../spirites/spriterojo.png"
#define SPRITE_PATH_VERDE "../spirites/spriteverde.png"

extern Logger *gplogger;

BossSprite::BossSprite(Window* window) : spriteTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture1(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF))))
{
    spriteTexture0.loadFromFile("../spirites/sprites (copy).png");
    //spriteTexture1.loadFromFile(SPRITE_PATH_ROJO);
    //spriteTexture2.loadFromFile(SPRITE_PATH_VERDE);
    spriteTexture[0] = &spriteTexture0;
    spriteTexture[1] = &spriteTexture1;
    spriteTexture[2] = &spriteTexture2;
    //enemySpriteTexture.loadFromFile(SPRITE_PATH_ENEMY);
    gplogger->log(3,"Se crea SpriteHandler de la vista");
}

void BossSprite::render(Scene &scene) {
    int x = scene.getBossX();
    int y = scene.getBossY();
    spriteTexture[scene.getLevel()]->render(x,y);
}