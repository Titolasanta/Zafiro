//
// Created by tito on 07/09/18.
//

#ifndef TP_FASE1_TEST_MODEL_H
#define TP_FASE1_TEST_MODEL_H


#include <SDL2/SDL_events.h>
#include <mutex>
#include "Character.h"
#include "../common/Projectile.h"
#include "../common/Level.h"
#include "../common/Scene.h"
#include "Boss.h"

class Model {
    
private:
    int shootBoss=0;
    Level level;
    Character *players[4];
    Boss *boss[3];
    std::list<Projectile> lBullets;
    Boss boss1;
    Boss boss2;
    Boss boss3;
    Character player1;
    Character player2;
    Character player3;
    Character player4;
    int currentPlayers = 0;
    int maxPlayers;
    std::mutex mutex;
    bool jugadorGrisado[4] = {true,true,true,true};
    bool jugadorReconectado[4] = {false, false, false, false};
    bool maxPlayersReached = false;
    bool fixBugPls[4] = {true,true,true,true};
    bool shootSound = false;

public:

    explicit Model(int initialLevel);
    ~Model() = default;
    void collisionEyP(Scene&);
    void collisionWyP(Scene&);
    void createCharacter(int);
    int getMaxPlayers();
    int getCurrentPlayers();
    void update(Scene&);
    void moveRight(int);
    void moveLeft(int);
    void aimDown(int);
    void aimStraight(int);
    void aimUp(int);
    void stop(int);
    void jump(int);
    void time();
    bool endOfLevel(Scene&);
    std::list<std::tuple<int,int,int>> lPlataformsSoft;
    std::list<std::tuple<int,int,int>> lPlataformsHard;
    void addPlataformSoft(int x, int y, int w);
    void addPlataformHard(int x, int y, int w);
    void changeLevel(Level,Scene&);
    void crouch(int);
    void stand(int);
    int getLevelWidth();
    int getLevelHeight();
    void shoot(int);
    void stopShooting(int);
    void bajaJugador(int currentPlayers);
    bool getMaxPlayersReached();
    void rejoinCharacter(int id);
    void placeCamera(Scene&);
    int XMasChico(Scene&);
    int YMasGrande(Scene&);
    void setEnemies(Scene&);
    void setWeapons(Scene&);
    void moveEnemies(Scene&);
    void immortalize(int id);
    void enemyCollision(Enemy&,Scene&);
    //const Level &getLevel() const;
    void respawn(int,SDL_Rect*);
    const bool *getJugadorGrisado() const;
    void handleBullet(Scene& scene);
    bool isBetween(int bulletX, int bulletY, int posX, int posY, int width, int height);
    void bossBullets(Scene& scene);
    void equipTrigonometricgun(int id);
    void equipMachinegun(int id);
};


#endif //TP_FASE1_TEST_MODEL_H
