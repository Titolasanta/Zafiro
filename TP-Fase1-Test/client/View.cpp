//
// Created by tito on 07/09/18.
//

#include <string>
#include <zconf.h>
#include "View.h"
#include "SdlInit.h"
#include "SdlImgInit.h"
#include "SpriteHandler.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../common/Logger.h"
#include "MovingEnemyImg.h"
#include <iostream>
extern Logger* gplogger;
extern pugi::xml_document *gXML_doc[2];
extern pugi::xml_parse_result *gXML_parse_result;

View::View(int SCREEN_WIDTH, int SCREEN_HEIGHT)
: window("juego",SCREEN_WIDTH,SCREEN_HEIGHT),
personajes(&window),piedra(&window),plataformaDura(&window),hielo(&window),
pasto(&window),bullet(&window),background(window,1),txt(std::move(window.createTextTexture())),immortal(std::move(window.createTextTexture())),
pass(std::move(window.createTextTexture())),usr(std::move(window.createTextTexture()))
,insert1(std::move(window.createTextTexture())),insert2(std::move(window.createTextTexture()))
,insert2bis(std::move(window.createTextTexture())), staticEnemyImg(std::move(&window)), //bossSprite(&window),
loginImages{std::move(window.createImgTexture()),
            std::move(window.createImgTexture()),
            std::move(window.createImgTexture()),
            std::move(window.createImgTexture())}
{
    loginImages[0].loadFromFile("../escenario/gif1.png");
    loginImages[1].loadFromFile("../escenario/gif2.png");
    loginImages[2].loadFromFile("../escenario/gif3.png");
    loginImages[3].loadFromFile("../escenario/gif4.png");
   // window.setRenderDrawColor(0x10  ,0x10,0xFF,0x120);
    std::string msg("Clave:");
    pass.loadFromRenderedText(msg);

    msg = "Usuario:";
    usr.loadFromRenderedText(msg);

    msg = "Ingrese sus datos";
    insert1.loadFromRenderedText(msg);

    msg = "Pulse esc para resetear ";
    insert2.loadFromRenderedText(msg);

    msg = "los datos ingresados";
    insert2bis.loadFromRenderedText(msg);

    std::string windowName("Contra");
    gplogger->log(3,"Se crea un View");

    std::string immortaal("i");
    immortal.loadFromRenderedText(immortaal);

}

void View::setId(int recid) {
    this->id = recid;
}

int View::isInLevelSummary(){
    return inLevelSummary;
}

void View::render(Scene& scene) {

    if(inLevelSummary){
        levelSummary();
        inLevelSummary--;
        return;
    }

    if(level != scene.getLevel())
        changeLevel(scene);

    if(level == 2) {
        moveBackground(scene.getVelocityY(id));
        if (scene.getPositionY(id) == 200 && scene.getPositionX(id) == 200) background.setScrollingOffset(-200);
    }else {
        moveBackground(scene.getVelocityX(id));
        if (scene.getPositionY(id) == 200 && scene.getPositionX(id) == 200) background.setScrollingOffset(0);
    }
    camera = scene.getCamera();

    window.redererClear();

    //background.render(scene);

    if(scene.isShootSound())
        Mix_PlayChannel(-1, this->getSound().getShootSFX(), 0);

    background.render(scene,*camera, background.getScrollingOffset(),level);

    if(level == 1) piedra.render(scene,camera);

    hielo.render(scene,camera);

    pasto.render(scene,camera);
    plataformaDura.render(scene,camera);
    bullet.render(scene,camera);
    staticEnemyImg.render(scene,camera);
    personajes.render(scene, id, camera->x, camera->y);
    personajes.renderBossSprite(scene,camera->x, camera->y);
    //bossSprite.render(scene);
    if(scene.getImmortal(id)) {
        immortal.render(100,100);
    }
    window.updateRenderer();
    
    for (int i = 0; i < scene.getCurrentPlayers(); i++){
        if (scene.isDead(i+1)){
            if (!scene.isJustDead(i+1)){
                Mix_PlayChannel(-1, sound.getDeathSFX(), 0);
                scene.setJustDead(1,i+1);
            }
        }
    }

}

void View::changeLevel(Scene& scene) {

    inLevelSummary = 100;
    ++level;

    Mix_HaltMusic();

    if (level == 2) {
        Mix_PlayMusic(sound.getLevelTwoMusic(), -1);
    }

    if (level == 3) {
        Mix_PlayMusic(sound.getLevelThreeMusic(), -1);
    }

    if (level < 4) {
        background.changeLevel(level);
        scene.clearPlatform();
        int lh = get_level_height(*gXML_doc[0], *gXML_doc[1], level, *gXML_parse_result);
        int lw = get_level_width(*gXML_doc[0], *gXML_doc[1], level, *gXML_parse_result);
        if (*gXML_parse_result) cargar_plataformas(*gXML_doc[0], scene, level, lh, lw);
        else cargar_plataformas(*gXML_doc[1], scene, level, lh, lw);
    }else{

        Mix_PlayChannel(-1, sound.getVictorySFX(), 0);
        endOfGameScreen();
    }
}
void View::moveBackground(int dir) {
    int newOffset= background.getScrollingOffset();
    if(dir > 0) --newOffset;
    if(dir < 0) ++newOffset;

    if (newOffset > 0) newOffset = 0;
    //if (newOffset < -3000) newOffset = -100;


    background.setScrollingOffset(newOffset);
}


void View::renderValidationScreen(std::string& Uinserted,std::string& Pinserted) {

    window.createRectangle(0,1000,0,800);
    loginImages[currentImage % 4].render(0, 0);
    usleep(60000);
    currentImage++;
    insert1.render(50, 200);
    insert2.render(50, 250);
    insert2bis.render(50, 280);

    usr.render(50, 370);

    if(!Uinserted.empty()) {
        txt.loadFromRenderedText(Uinserted);
        txt.render(50, 400);
    }
    pass.render(50, 450);
    if (!Pinserted.empty()) {
        txt.loadFromRenderedText(Pinserted);
        txt.render(50, 480);
    }
    window.updateRenderer();

}

void View::fullHouseMesage() {
    window.createRectangle(0,1000,0,800);
    int img;
    for(int i = 0; i < 60; i++) {
        img = i % 4;
        loginImages[img].render(0, 0);
        std::string msg("El servidor no tiene mas cupos.");
        txt.loadFromRenderedText(msg);
        txt.render(50, 250);
        window.updateRenderer();
        usleep(75000);
    }
}

void View::invalidLoginMesage() {
    window.createRectangle(0,1000,0,800);
    int img;
    for(int i = 0; i < 60; i++) {
        img = i % 4;
        loginImages[img].render(0, 0);
        std::string msg1("El usuario ingresado es");
        std::string msg2("invalido o ya esta en uso.");
        txt.loadFromRenderedText(msg1);
        txt.render(50, 250);
        txt.loadFromRenderedText(msg2);
        txt.render(50, 300);
        window.updateRenderer();
        usleep(75000);
    }
}

void View::conexionFail() {
    window.createRectangle(0,1000,0,800);
    int img;
    for(int i = 0; i < 60; i++) {
        img = i % 4;
        loginImages[img].render(0, 0);
        std::string msg("El servidor se cayo.");
        txt.loadFromRenderedText(msg);
        txt.render(50, 250);
        window.updateRenderer();
        usleep(75000);
    }
}
void View::conexionFail2() {
    window.createRectangle(0,1000,0,800);
    int img;
    for(int i = 0; i < 60; i++) {
        img = i % 4;
        loginImages[img].render(0, 0);
        std::string msg("Se perdio conexion al servidor.");
        txt.loadFromRenderedText(msg);
        txt.render(50, 250);
        msg = "Intente conectarse nuevamamente.";
        txt.loadFromRenderedText(msg);
        txt.render(50, 300);
        window.updateRenderer();
        usleep(75000);
    }
}

void View::conexionDown() {
    window.createRectangle(0,1000,0,800);
    int img;
    for(int i = 0; i < 60; i++) {
        img = i % 4;
        loginImages[img].render(0, 0);
        std::string msg("No se encontro el servidor.");
        txt.loadFromRenderedText(msg);
        txt.render(50, 250);
        window.updateRenderer();
        usleep(75000);
    }
}
void View::waiting() {
    window.createRectangle(0,1000,0,800);
    loginImages[currentImage % 4].render(0, 0);
    currentImage++;
    std::string msg1("El servidor esta ocupado, ");
    std::string msg2("por favor aguarde su turno.");
    txt.loadFromRenderedText(msg1);
    txt.render(50, 250);
    txt.loadFromRenderedText(msg2);
    txt.render(50, 300);
    window.updateRenderer();
}

void View::waiting_for_players() {
    window.createRectangle(0,1000,0,800);
    loginImages[currentImage % 4].render(0, 0);
    currentImage++;
    std::string msg("Esperando al resto ");
    txt.loadFromRenderedText(msg);
    txt.render(50, 250);
    msg = "de los jugadores";
    txt.loadFromRenderedText(msg);
    txt.render(50, 300);
    window.updateRenderer();
}

void View::levelSummary() {
    window.createRectangle(0,1000,0,800);
    currentImage++;
    loginImages[currentImage%4].render(0, 0);
    std::string msg("Fin del nivel");
    txt.loadFromRenderedText(msg);
    txt.render(100, 250);
    window.updateRenderer();

}

void View::endOfGameScreen() {
    window.createRectangle(0,1000,0,800);
    int img;
    for(int i = 0; i < 60; i++) {
        img = i % 4;
        loginImages[img].render(0, 0);
        std::string msg("Fin del juego");
        txt.loadFromRenderedText(msg);
        txt.render(100, 250);
        window.updateRenderer();
        usleep(75000);
    }
}

int View::getLevel() { return level; }

Sound& View::getSound() { return sound; }