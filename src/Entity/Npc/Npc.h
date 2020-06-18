#ifndef GAME_NPC_H
#define GAME_NPC_H

class Npc: public Entity{

public:

    enum NpcType{

        BlackSmith,
        Witch,
        Trader,
        Crafter
    };

public:

    Npc() = delete;
    Npc(std::string name, TextureManager*);

    //virtual ~Npc();

public:

    std::string getName() const;
    NpcType getType() const;


private:

    virtual void loadFromFile();
    virtual void setSprite();

protected:

    std::string name;
    NpcType type;

private:

    sf::Sprite
};

#endif