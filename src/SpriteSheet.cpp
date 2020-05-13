#include "SpriteSheet.h"

/***************
 * Constructor *
 ***************/
SpriteSheet::SpriteSheet(TextureManager *textMgr):
        textureManager(textMgr),
        animationCurrent(nullptr),
        spriteScale(1.f, 1.f),
        orientation(Orientation::South){}

/**************
 * Destructor *
 **************/
SpriteSheet::~SpriteSheet(){

    releaseSheet();
}

/****************
 * ReleaseSheet *
 ****************/
void SpriteSheet::releaseSheet(){

    textureManager->releaseResource(texture);
    animationCurrent = nullptr;
    while(animations.begin() != animations.end()){

        delete animations.begin()->second;
        animations.erase(animations.begin());
    }
}

/*****************
 * SetSpriteSize *
 *****************/
void SpriteSheet::setSpriteSize(const sf::Vector2f &size){

    spriteSize = size;
    sprite.setOrigin(spriteSize.x / 2.f, spriteSize.y);
}

/*****************
 * GetSpriteSize *
 *****************/
sf::Vector2f SpriteSheet::getSpriteSize() const{

    return spriteSize;
}

/*********************
 * SetSpritePosition *
 *********************/
void SpriteSheet::setSpritePosition(const sf::Vector2f &pos){

    sprite.setPosition(pos);
}

/******************
 * SetOrientation *
 ******************/
void SpriteSheet::setOrientation(const Orientation &orient){

    if (orient == orientation)
        return;

    orientation = orient;
    animationCurrent->cropSprite();
}

Orientation SpriteSheet::getOrientation() const{

    return orientation;
}

/**************
 * CropSprite *
 **************/
void SpriteSheet::cropSprite(const sf::IntRect &rect){

    sprite.setTextureRect(rect);
}

/*************
 * LoadSheet *
 *************/
bool SpriteSheet::loadSheet(const std::string &file){

    std::ifstream sheet;
    sheet.open(file);
    if(sheet.is_open()){

        releaseSheet(); // Release current sheet resources.
        std::string line;
        while(std::getline(sheet,line)){

            if (line[0] == '|')
                continue;

            std::stringstream keystream(line);
            std::string type;
            keystream >> type;

            if(type == "Texture"){
                if (texture != ""){

                    std::cerr << "! Duplicate texture entries in: " << file << std::endl;
                    continue;
                }
                std::string nameText;
                keystream >> nameText;
                if (!textureManager->requireResource(nameText)){

                    std::cerr << "! Could not set up the texture: " << nameText << std::endl;
                    continue;
                }
                texture = nameText;
                sprite.setTexture(*textureManager->getResource(texture));
            }

            else if(type == "Size"){

                keystream >> spriteSize.x >> spriteSize.y;
                setSpriteSize(spriteSize);
            }
            else if(type == "Scale"){

                keystream >> spriteScale.x >> spriteScale.y;
                sprite.setScale(spriteScale);
            }
            else if(type == "AnimationType"){

                keystream >> animType;
            }
            else if(type == "Animation"){

                std::string name;
                keystream >> name;
                if (animations.find(name) != animations.end()){

                    std::cerr << "! Duplicate animation(" << name << ") in: " << file << std::endl;
                    continue;
                }
                Anim_Base* anim = nullptr;
                if(animType == "Directional"){

                    anim = new Anim_Directional();
                }
                else {

                    std::cerr << "! Unknown animation type: " << animType << std::endl;
                    continue;
                }
                keystream >> *anim;
                anim->setSpriteSheet(this);
                anim->setName(name);
                anim->reset();
                animations.emplace(name,anim);
                if(animationCurrent)
                    continue;

                animationCurrent = anim;
                animationCurrent->play();
            }
        }
        sheet.close();
        return true;
    }
    std::cerr << "! Failed loading spritesheet: " << file << std::endl;
    return false;
}

/****************
 * GetAnimation *
 ****************/
Anim_Base* SpriteSheet::getCurrentAnim() const{

    return animationCurrent;
}

/****************
 * SetAnimation *
 ****************/
bool SpriteSheet::setAnimation(const std::string &name, const bool &play, const bool &loop){

    auto itr = animations.find(name);
    if (itr == animations.end())
        return false;

    if (itr->second == animationCurrent)
        return false;

    if (animationCurrent)
        animationCurrent->stop();

    animationCurrent = itr->second;
    animationCurrent->setLooping(loop);
    if(play)
        animationCurrent->play();

    animationCurrent->cropSprite();
    return true;
}

/**********
 * Update *
 **********/
void SpriteSheet::update(const float &deltaT){

    animationCurrent->update(deltaT);
}

/********
 * Draw *
 ********/
void SpriteSheet::draw(sf::RenderWindow *wnd){

    wnd->draw(sprite);
}