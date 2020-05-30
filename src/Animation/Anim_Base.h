#ifndef GAME_ANIM_BASE_H
#define GAME_ANIM_BASE_H

#include <string>

class SpriteSheet;

using Frame = unsigned int;

class Anim_Base{

    friend class SpriteSheet;

public:

    Anim_Base();
    virtual ~Anim_Base();

public:

    void setSpriteSheet(SpriteSheet *sheet);

    void setFrame(const unsigned int &frame);

    void setName(const std::string tName);

    void setLooping(const bool isLooping);

    bool isInAction();

    void play();

    void pause();

    void stop();

    void reset();

    virtual void update(const float &deltaT);

    friend std::stringstream &operator >>(std::stringstream &stream, Anim_Base &anim){

        anim.readIn(stream);
        return stream;
    }

protected:

    virtual void frameStep() = 0;
    virtual void cropSprite() = 0;
    virtual void readIn(std::stringstream &stream) = 0;

    Frame frameCurrent;
    Frame frameStart;
    Frame frameEnd;
    Frame frameRow;
    int frameActionStart; // Frame when a specific "action" begins
    int frameActionEnd; // Frame when a specific "action" ends
    float frameTime;

    float elapsedTime;
    bool loop;
    bool playing;
    std::string name;
    SpriteSheet *spriteSheet;
};

#endif