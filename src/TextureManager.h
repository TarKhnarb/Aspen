#ifndef GAME_TEXTUREMANAGER_H
#define GAME_TEXTUREMANAGER_H

#include <SFML/Graphics.hpp>

#include <iostream>

#include "ResourceManager.h"

class TextureManager: public ResourceManager<TextureManager, sf::Texture>{

public:

    TextureManager(): ResourceManager("Data/Files/Texture/Textures.cfg"){}

    sf::Texture* load(const std::string &path){

        sf::Texture *texture = new sf::Texture();
        if(!texture->loadFromFile(path)){

            delete texture;
            texture = nullptr;
            std::cerr << "! Failed to load texture: " << path << std::endl;
        }
        return texture;
    }
};

#endif