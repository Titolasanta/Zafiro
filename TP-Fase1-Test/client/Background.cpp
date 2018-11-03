//
// Created by tito on 17/09/18.
//

#include <iostream>
#include "Background.h"
#include "../common/pugixml.hpp"
#include "../common/xml.h"
#include "../common/Logger.h"


extern pugi::xml_document* gXML_doc[2];
extern Logger *gplogger;
extern pugi::xml_parse_result *gXML_parse_result;

Background::Background(Window& window, int level) : img1(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) ),
                                                    img2(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) ),
                                                    img3(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) )
{
    //img1.loadFromFile("../escenario/level1-background1.png");
    //img1.loadFromFile("../escenario/NES - Contra - Level 1.png");
    //img2.loadFromFile("../escenario/1-2-transparent-test.png");
  //  std::cout << get_level_background_path(*gXML_doc[0],*gXML_doc[1], level, 1,*gXML_parse_result);
   img1.loadFromFile(get_level_background_path(*gXML_doc[0],*gXML_doc[1], level, 1,*gXML_parse_result));
   img2.loadFromFile(get_level_background_path(*gXML_doc[0],*gXML_doc[1],level, 2,*gXML_parse_result));
   img3.loadFromFile(get_level_background_path(*gXML_doc[0],*gXML_doc[1],level, 3,*gXML_parse_result));

    gplogger->log(3,"Se crea Background");
}

void Background::render(Scene& scene,SDL_Rect& camera, int scrollingOffset,int level){
    if(level == 1) {
        img1.renderBackground(scrollingOffset, 0);
        img2.renderBackground(scrollingOffset * 5, 0);
        img3.renderBackground(scrollingOffset * 10, 0);

    } if(level == 2){
        if(scrollingCatarata >= -100)
            scrollingCatarata = -2900;
        scrollingCatarata += 10;
        img1.renderBackground(0, scrollingCatarata);
        img2.renderBackground(0, scrollingOffset*5 );
        //img3.renderBackground(0, scrollingOffset *10);

    } if(level == 3) {
        img1.renderBackground(scrollingOffset, 0);
        img2.renderBackground(scrollingOffset * 5, 0);
        img3.renderBackground(scrollingOffset * 10, 0   );
    }
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

void Background::changeLevel(int level) {
    scrollVertical = !scrollVertical;
    img1.loadFromFile(get_level_background_path(*gXML_doc[0],*gXML_doc[1], level, 1,*gXML_parse_result));
    img2.loadFromFile(get_level_background_path(*gXML_doc[0],*gXML_doc[1],level, 2,*gXML_parse_result));
    img3.loadFromFile(get_level_background_path(*gXML_doc[0],*gXML_doc[1],level, 3,*gXML_parse_result));

}


