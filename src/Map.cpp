#include "Map.h"

Map::Map(TextureManager *txtMng):
        txtMng(txtMng){

    background.setSize(2560.f, 1440.f);
    background.setFillColor(sf::Color(148, 223, 231));;

    txtMng->requireResource("Map");
    map.setTexture(*textureMgr->getResource("Map"));
    map.setSize(1280.f, 720.f);
    map.setPosition(640.f, 360.f);
}

