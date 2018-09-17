//
// Created by tito on 17/09/18.
//

#include "Background.h"
#include "pugixml.hpp"
#include "xml.h"


extern pugi::xml_document* gXML_doc;

Background::Background(Window& window, int level) : img1(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) ),
                                                    img2(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) ),
                                                    img3(std::move(window.createImgTexture(0xFF, 0xFF, 0xFF) ) )
{   img1.loadFromFile("../escenario/NES - Contra - Level 1.png");
   // img1.loadFromFile(get_level_background_path(gXML_doc, level, 1));
   //img2.loadFromFile(get_level_background_path(gXML_doc, level, 2));
   //img3.loadFromFile(get_level_background_path(gXML_doc, level, 3));
}

void Background::render(Scene& scene){

    img1.render(0,0,0,800,0,600);
}