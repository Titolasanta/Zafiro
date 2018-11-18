//
// Created by tito on 05/09/18.
//

#ifndef TP_FASE1_TEST_PERSONAJES_H
#define TP_FASE1_TEST_PERSONAJES_H


#include "Window.h"
#include "Sprite.h"
#include "../common/Scene.h"

class SpriteHandler {

public:
    explicit SpriteHandler(Window* window);
    void render(Scene &scene, int id, int cameraX, int cameraY);
    void renderCharacterSprite(Scene &scene, int i, int cameraX, int cameraY);
    void renderMovingEnemySprite(Enemy e, int cameraX, int cameraY);
    void renderStaticEnemySprite(Enemy e, int cameraX, int cameraY);
    void renderBossSprite(Scene &scene, int cameraX, int cameraY);
    void renderHp(Scene&, int, int, int);
    void renderEnemyDestroyedSprites(Enemy e, int cameraX, int cameraY, int i);

private:
    ImgTexture *spriteTexture[5];
    ImgTexture spriteTexture0;
    ImgTexture spriteTexture1;
    ImgTexture spriteTexture2;
    ImgTexture spriteTexture3;
    ImgTexture spriteTextureGrace;
    ImgTexture movingEnemySpriteTexture;
    ImgTexture staticEnemySpriteTexture;
    ImgTexture *bossTexture[3];
    ImgTexture *deadBossTexture[3];
    ImgTexture bossTexture0;
    ImgTexture bossTexture1;
    ImgTexture bossTexture2;
    ImgTexture destroyedEnemySpriteTexture;
    ImgTexture deadBossTexture0;
    ImgTexture deadBossTexture1;
    ImgTexture deadBossTexture2;
    int dibujarTitilantes = 10;
    Sprite spritePositionHandler;
    int currentFrame[5] = {0, 0, 0, 0, 0};
};


#endif //TP_FASE1_TEST_PERSONAJES_H
