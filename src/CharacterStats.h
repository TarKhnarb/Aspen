#ifndef GAME_CHARACTERSTATS_H
#define GAME_CHARACTERSTATS_H

#include <iomanip> // Permet d'utiliser ( std::setprecision(i), 0 <= i <= 200) pour set la precision decimale d'un float sur un output
#include <string>

enum class CharacterType{

    Player,
    Monster
    //Npc // A voir si on les mets ici sachant qu'ils n'ont pas besoin de stats
};

class CharacterStats: public sf::Drawable, public sf::Transformable {

public:

    enum Stats{

        Life,
        Attack,
        AttackSpeed,
        Defence,
        Speed,
        fly
    };

public:

    CharacterStats(std::sting name, charType);
    ~CharacterStats();

public:

private:

    takeCharacterStats()
private:

    std::map<Type, float> Stats;

    std::string characterName;
};

#endif