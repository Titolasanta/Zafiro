//
// Created by tito on 14/11/18.
//

#ifndef TP_FASE1_TEST_ENEMIGOFINAL_H
#define TP_FASE1_TEST_ENEMIGOFINAL_H


class Boss {
private:
    int posX;
    int posY;
    int HP = 3;
public:

    Boss(int level);

    int getPosX() const {
        return posX;
    }

    void takeDamage(){
        if(HP != 0)
            HP -= 1;
    }

    void setPosX(int posX) {
        Boss::posX = posX;
    }

    int getPosY() const {
        return posY;
    }

    void setPosY(int posY) {
        Boss::posY = posY;
    }

    int getHP() const {
        return HP;
    }

    void setHP(int HP) {
        Boss::HP = HP;
    }



};


#endif //TP_FASE1_TEST_ENEMIGOFINAL_H