#ifndef GAME_SPRITESHEET_H
#define GAME_SPRITESHEET_H

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>


#include "TextureManager.h"
#include "Orientation.h"
#include "Anim_Base.h"
#include "Anim_Directional.h"

using Animations = std::unordered_map<std::string, Anim_Base*>;

class SpriteSheet : public sf::Drawable{

public:

    SpriteSheet(TextureManager *textMgr);

    ~SpriteSheet();

public:

    void releaseSheet();

    void setSpriteSize(const sf::Vector2f &size);

    sf::Vector2f getSpriteSize() const;

    void setSpritePosition(const sf::Vector2f &pos);

    void setOrientation(const Orientation &orient);

    Orientation getOrientation() const;

    void cropSprite(const sf::IntRect &rect);

    bool loadSheet(const std::string &file);

    Anim_Base* getCurrentAnim() const;

    bool setAnimation(const std::string &name, const bool &play = false, const bool &loop = false);

    void update(const float &deltaT);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:

    std::string texture;
    sf::Sprite sprite;

    sf::Vector2f spriteSize;
    sf::Vector2f spriteScale;

    Orientation orientation;
    std::string animType;
    Animations animations;
    Anim_Base *animationCurrent;

    TextureManager *textureManager;
};

#endif
