//
// Created by fede on 21/09/18.
//

#ifndef TP_FASE1_TEST_NIVEL_H
#define TP_FASE1_TEST_NIVEL_H


class Level {
private:
    int level;
    int height;
    int width;
public:
    Level(int n);
    int getHeight();
    int getWidth();

    int getLevel();

    Level next();
};


#endif //TP_FASE1_TEST_NIVEL_H
