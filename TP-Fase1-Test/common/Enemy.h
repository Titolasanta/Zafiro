//
// Created by tito on 07/11/18.
//

#ifndef TP_FASE1_TEST_ENEMY_H
#define TP_FASE1_TEST_ENEMY_H


class Enemy {
public:
    Enemy(int x,int y);
private:
    int posX;
    int posY;
public:
    int getPosX() const;

    void setPosX(int posX);

    int getPosY() const;

    void setPosY(int posY);

private:
    bool alive = true;
};


#endif //TP_FASE1_TEST_ENEMY_H
