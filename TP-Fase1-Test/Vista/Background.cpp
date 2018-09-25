//
// Created by tito on 17/09/18.
//

#include "Background.h"
#include "pugixml.hpp"
#include "xml.h"
#include "Logger.h"


extern pugi::xml_document* gXML_doc;
extern Logger *gplogger;

Background::Background(Window& window, int level) : img1(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) ),
                                                    img2(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) ),
                                                    img3(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) )
{
    img1.loadFromFile("../escenario/level1-background1.png");
    //img1.loadFromFile("../escenario/NES - Contra - Level 1.png");
    img2.loadFromFile("../escenario/1-2-transparent-test.png");
   //img1.loadFromFile(get_level_background_path(gXML_doc, level, 1));
   //img2.loadFromFile(get_level_background_path(gXML_doc, level, 2));
   //img3.loadFromFile(get_level_background_path(gXML_doc, level, 3));

    gplogger->log(1,"Se crea Background\n");
}

void Background::render(Scene& scene,SDL_Rect& camera, int scrollingOffset){
    img1.renderBackground( scrollingOffset, 0 );
    img2.renderBackground( --scrollingOffset  , 0);
}

int Background::getScrollingOffset() {
    return scrollingOffset;
}

void Background::setScrollingOffset(int scrollingOffset) {
    Background::scrollingOffset = scrollingOffset;
}

ImgTexture &Background::getImg1() {
    return img1;
}


