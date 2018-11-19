//
// Created by tito on 05/09/18.
//

#include <iostream>
#include <zconf.h>
#include <random>
#include "SpriteHandler.h"
#include "Sprite.h"
#include "../common/Logger.h"

#define SPRITE_PATH_AZUL "../spirites/spriteazul.png"
#define SPRITE_PATH_ROJO "../spirites/spriterojo.png"
#define SPRITE_PATH_VERDE "../spirites/spriteverde.png"
#define SPRITE_PATH_AMARILLO "../spirites/spriteamarillo.png"
#define SPRITE_PATH_ENEMY "../spirites/enemies.png"
#define BOSS_PATH_LVL1 "../spirites/bossl1.png"
#define BOSS_PATH_LVL2 "../spirites/bossl2.png"
#define BOSS_PATH_LVL3 "../spirites/bossl3.png"
#define DEAD_BOSS_PATH_LVL1 "../spirites/bossl1dead.png"
#define DEAD_BOSS_PATH_LVL3 "../spirites/bossl3dead.png"
#define DEAD_BOSS_FRONT_PATH_LVL1 "../spirites/bossl1deadfront.png"
#define DEAD_BOSS_FRONT_PATH_LVL3 "../spirites/bossl3deadfront.png"

#define characterWidth 20

extern Logger *gplogger;

SpriteHandler::SpriteHandler(Window* window) : spriteTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture1(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTexture3(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               movingEnemySpriteTexture(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               staticEnemySpriteTexture(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               bossTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               bossTexture1(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               bossTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               deadBossTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               deadBossTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               deadBossFrontTexture0(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               deadBossFrontTexture1(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               deadBossFrontTexture2(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               spriteTextureGrace(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF)))),
                                               destroyedEnemySpriteTexture(  (std::move(window->createImgTexture(0xFF, 0xFF, 0xFF))))

{
    spriteTexture[0] = &spriteTexture0;
    spriteTexture[1] = &spriteTexture1;
    spriteTexture[2] = &spriteTexture2;
    spriteTexture[3] = &spriteTexture3;
    spriteTexture0.loadFromFile(SPRITE_PATH_AZUL);
    spriteTextureGrace.loadFromFile(SPRITE_PATH_ROJO);
    spriteTexture1.loadFromFile(SPRITE_PATH_ROJO);
    spriteTexture2.loadFromFile(SPRITE_PATH_VERDE);
    spriteTexture3.loadFromFile(SPRITE_PATH_AMARILLO);
    movingEnemySpriteTexture.loadFromFile(SPRITE_PATH_ENEMY);
    staticEnemySpriteTexture.loadFromFile(SPRITE_PATH_ENEMY);
    bossTexture[0] = &bossTexture0;
    bossTexture[1] = &bossTexture1;
    bossTexture[2] = &bossTexture2;
    destroyedEnemySpriteTexture.loadFromFile(SPRITE_PATH_ENEMY);
    deadBossTexture[0] = &deadBossTexture0;
    deadBossTexture[2] = &deadBossTexture2;
    deadBossFrontTexture[0] = &deadBossFrontTexture0;
    deadBossFrontTexture[2] = &deadBossFrontTexture2;
    bossTexture0.loadFromFile(BOSS_PATH_LVL1);
    bossTexture1.loadFromFile(BOSS_PATH_LVL2);
    bossTexture2.loadFromFile(BOSS_PATH_LVL3);
    deadBossTexture0.loadFromFile(DEAD_BOSS_PATH_LVL1);
    deadBossTexture2.loadFromFile(DEAD_BOSS_PATH_LVL3);
    deadBossFrontTexture0.loadFromFile(DEAD_BOSS_FRONT_PATH_LVL1);
    deadBossFrontTexture2.loadFromFile(DEAD_BOSS_FRONT_PATH_LVL3);
    //enemySpriteTexture.loadFromFile(SPRITE_PATH_ENEMY);
    gplogger->log(3,"Se crea SpriteHandler de la vista");
}

void SpriteHandler::render(Scene &scene, int id, int cameraX, int cameraY) {
    dibujarTitilantes--;
    int offset = 0;
    std::list<Enemy>* le = scene.getEnemies();
    for (auto it = le->begin(); it != le->end(); it++){
        if(it->isDead()){
            if (it->getContador() == 1) offset = 4;
            else if (it->getContador() == 0) offset = 8;
            renderEnemyDestroyedSprites(*it, cameraX + offset, cameraY + offset, 2 - it->getContador());
            it = scene.getEnemies()->erase(it);
        } else {
            if (it->isStatic()) renderStaticEnemySprite(*it, cameraX, cameraY);
            else renderMovingEnemySprite(*it, cameraX, cameraY);
        }
    }

    renderBossSprite(scene,cameraX, cameraY);

    for (int i = 0; i-1 <  scene.getCurrentPlayers(); i++) {
        if (i == id - 1) continue;
        renderCharacterSprite(scene, i, cameraX, cameraY);
    }
    renderCharacterSprite(scene, id - 1, cameraX, cameraY);
    if(!dibujarTitilantes)
        dibujarTitilantes = 6;
    renderDeadBossSprite(scene, cameraX, cameraY);
    renderHp(scene, id, cameraX, cameraY);
}

void SpriteHandler::renderCharacterSprite(Scene &scene, int i, int cameraX, int cameraY) {

    if (scene.isWalking(i + 1) || scene.isAirborne(i + 1)) currentFrame[i + 1]++;
    else currentFrame[i + 1] = 0;

    SDL_Rect *currentClip;
    int angle;

    if (scene.isLookingRight(i + 1)) angle = 0;
    else angle = 180;

    if (scene.getAimDirection(i + 1) == -1) currentClip = spritePositionHandler.move(1, currentFrame[i + 1] % 3);
    else if (scene.getAimDirection(i + 1) == 1) currentClip = spritePositionHandler.move(1, currentFrame[i + 1] % 3 + 3);
    else {
        if (!scene.isWalking(i + 1)) currentClip = spritePositionHandler.move(3, currentFrame[i + 1] % 3);
        else currentClip = spritePositionHandler.move(0, currentFrame[i + 1] % 6);

        if (scene.isShooting(i + 1) && !scene.isCrouching(i + 1)) currentClip = spritePositionHandler.move(3, currentFrame[i+1]%3);
    }
    if (scene.isCrouching(i + 1))currentClip = spritePositionHandler.getFaceDown();
    if (scene.isAirborne(i + 1) && !scene.isDead(i + 1)) currentClip = spritePositionHandler.move(2, currentFrame[i + 1] % 4);
    if (scene.isAirborne(i + 1) && scene.isDead(i + 1)) currentClip = spritePositionHandler.move(4, currentFrame[i + 1] % 4);
    if (!scene.isAirborne(i + 1) && scene.isDead(i + 1)) currentClip = spritePositionHandler.getMuerto();
    if (scene.isJugadorGrisado(i + 1)) currentClip = spritePositionHandler.getGrisado();

    if(scene.isInGracePeriod(i+1)) {
        if ((dibujarTitilantes % 3))
            spriteTexture[i]->render(scene.getPositionX(i + 1) - cameraX - characterWidth / 2,
                                     scene.getPositionY(i + 1) - cameraY,
                                     currentClip, angle);
    } else
        spriteTexture[i]->render(scene.getPositionX(i + 1) - cameraX - characterWidth / 2,
                                               scene.getPositionY(i + 1) - cameraY,
                                               currentClip, angle);
}

void SpriteHandler::renderHp(Scene& scene,int  id,int cameraX,int cameraY){
    SDL_Rect lifeClip = {386,0,16,32};
    if(!scene.isDead(id))
        for(int j = scene.getHitPoints(id) - 1; j >= 0; j--)
            spriteTexture[id-1]->render(j * 20, 1,&lifeClip );
}

void SpriteHandler::renderMovingEnemySprite(Enemy e, int cameraX, int cameraY){

    //if (!e.isAirborne()) e.setCurrentFrame(0);

    SDL_Rect *currentClip;
    int angle;

    if (!e.isLookingRight()) angle = 0;
    else angle = 180;

    //if (scene.getAimDirection(i+1) == -1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3);
    //else if (scene.getAimDirection(i+1) == 1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3 + 3);
    //else {
    //if (!scene.isWalking(i+1)) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    /*else*/
    currentClip = spritePositionHandler.getMovingEnemySprite(e.getCurrentFrame());

    //if (e.isShooting() ) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    //}
    //if (scene.isCrouching(i+1))currentClip = spritePositionHandler.getFaceDown();
    //if (e.isAirborne()) currentClip = spritePositionHandler.move(2, e.getCurrentFrame()% 4);
    //if (scene.isJugadorGrisado(i + 1)) currentClip = spritePositionHandler.getGrisado();

    // printf("%d,%d\n",scene.getPositionX(i+1),scene.getPositionY(i+1));
    movingEnemySpriteTexture.render(e.getPosX() - cameraX - characterWidth / 2, e.getPosY() - cameraY, currentClip, angle);
}

void SpriteHandler::renderStaticEnemySprite(Enemy e, int cameraX, int cameraY){

    //if (e.isAirborne()) e.incrementCurrentFrame();
    //else e.setCurrentFrame(0);

    SDL_Rect *currentClip;
    /*int angle;

    if (e.isLookingRight()) angle = 0;
    else angle = 180;*/

    //if (scene.getAimDirection(i+1) == -1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3);
    //else if (scene.getAimDirection(i+1) == 1) currentClip = spritePositionHandler.move(1, currentFrame[i+1] % 3 + 3);
    //else {
    //if (!scene.isWalking(i+1)) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    /*else*/
    currentClip = spritePositionHandler.getStaticEnemySprite(e.getCurrentFrame());

    //if (e.isShooting() ) currentClip = spritePositionHandler.move(3, currentFrame[i+1] % 3);
    //}
    //if (scene.isCrouching(i+1))currentClip = spritePositionHandler.getFaceDown();
    /*if (e.isAirborne() ){
        e.incrementCurrentFrame();
        currentClip = spritePositionHandler.move(2, e.getCurrentFrame()% 4);
    }*/
    //if (scene.isJugadorGrisado(i + 1)) currentClip = spritePositionHandler.getGrisado();

    // printf("%d,%d\n",scene.getPositionX(i+1),scene.getPositionY(i+1));
    staticEnemySpriteTexture.render(e.getPosX() - cameraX - characterWidth / 2, e.getPosY() - cameraY, currentClip, 0);
}

void SpriteHandler::renderBossSprite(Scene &scene, int cameraX, int cameraY) {
    if (scene.getLevel() == 2) {

        std::random_device rand_dev;
        std::default_random_engine generator(rand_dev());
        std::uniform_int_distribution<int> player(0,scene.getCurrentPlayers() - 1);
        int character = player(generator);
        int pos = scene.getPositionX(character + 1);
        SDL_Rect clip;
        if(!scene.getBossHP()) clip = {22, 1013, 762, 312};
        else if (pos < 370 && pos > 230) clip = {22, 0, 762, 312};
        else if (pos <= 230) clip = {22, 339, 762, 312};
        else clip = {22, 675, 762, 312};

        bossTexture[scene.getLevel() - 1]->render(scene.getBossX() - cameraX, scene.getBossY() - cameraY,
                                                  &clip, 0);
    }
    else {
        if (scene.getBossHP()) bossTexture[scene.getLevel() - 1]->render(scene.getBossX() - cameraX, scene.getBossY() - cameraY);
        else deadBossTexture[scene.getLevel() - 1]->render(scene.getBossX() - cameraX, scene.getBossY() - cameraY);
    }
}

void SpriteHandler::renderEnemyDestroyedSprites(Enemy e, int cameraX, int cameraY, int i){
    SDL_Rect *currentClip;
    currentClip = spritePositionHandler.getDestroyedEnemySprite(i);
    destroyedEnemySpriteTexture.render(e.getPosX() - cameraX - characterWidth / 2, e.getPosY() - cameraY, currentClip, 0);
    usleep(5500);
}

void SpriteHandler::renderDeadBossSprite(Scene &scene, int cameraX, int cameraY) {
    if (scene.getLevel() != 2 && (!scene.getBossHP())) deadBossFrontTexture[scene.getLevel() - 1]->render(scene.getBossX() - cameraX, scene.getBossY() - cameraY);
}