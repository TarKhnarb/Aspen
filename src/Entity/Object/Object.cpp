#include "Object.h"

/***************
 * Constructor *
 ***************/
Object::Object(const std::string &name, TextureManager *txtMgr, std::size_t number):
        Entity(txtMgr, Entity::Object),
        name(name),
        number(number){
    
    setSprite();

    loadFromFile();

    if(this->number > stackSize)
        this->number = stackSize;
}

/***************
 * Constructor *
 ***************/
Object::Object(const Object &obj, std::size_t number):
        Entity(getTextureManager(), Entity::Object){

    Object(obj.getName(), getTextureManager(), number);
}

/**************
 * Desstructor *
 **************/
Object::~Object(){
    
    textureMgr->releaseResource(name);
}

/***********
 * GetName *
 ***********/
std::string Object::getName() const{

    return name;
}

/*************
 * GetNumber *
 *************/
std::size_t Object::getNumber() const{

    return number;
}

/*****************
 * GetObjectType *
 *****************/
Object::ObjectType Object::getObjectType() const{

    return type;
}

/****************
 * GetStackSize *
 ****************/
std::size_t Object::getStackSize() const{

    return stackSize;
}

/************
 * GetBonus *
 ************/
Bonus* Object::getBonus() const{

    if(bonus)
        return bonus;
    else
        return nullptr; // Cas où on essayerait de recupérer le bonus d'un Loot
}

std::pair<int, int> Object::getPrices() const{

    return prices;
}

/*********
 * Empty *
 *********/
bool Object::empty() const{

    return number == 0;
}

/*********
 * Empty *
 *********/
bool Object::full() const{

    return number == stackSize;
}
/***************
 * Operator += *
 ***************/
Object& Object::operator+=(std::size_t &toAdd){

    std::size_t avail = stackSize - number;

    if(toAdd <= avail){

        number += toAdd;
        toAdd = 0;
    }
    else{

        number = stackSize;
        toAdd -= avail;
    }

    return *this;
}

/***************
 * Operator += *
 ***************/
Object& Object::operator+=(Object &otherStk){

    if(name != otherStk.name)
        return *this;

    return operator+=(number);
}

/***************
 * Operator -= *
 ***************/
Object& Object::operator-=(std::size_t &toRemove){

    if(toRemove <= number){

        number -= toRemove;
        toRemove = 0;
    }
    else{

        number = 0;
        toRemove -= number;
    }

    return *this;
}

/***************
 * Operator -= *
 ***************/
Object& Object::operator-=(Object &otherStk){

    if(name != otherStk.name)
        return *this;

    return operator-=(otherStk.number);
}

/***************
 * Operator ++ *
 ***************/
Object& Object::operator++(){

    std::size_t toAdd = 1;
    return operator+=(toAdd);
}

/***************
 * Operator -- *
 ***************/
Object& Object::operator--(){

    std::size_t toRemove = 1;
    return operator-=(toRemove);
}

/*************
 * SetSprite *
 *************/
void Object::setSprite(){

    textureMgr->requireResource(name);
    sprite.setTexture(*textureMgr->getResource(name));

    collisionBox = sprite.getGlobalBounds();
}

/*************
 * UsePotion *
 *************/
int Object::usePotion(std::size_t num){

    if(type == Potion) {

        if (num > number)
            num = number;

        number -= num;

        return number * bonus->getValues(StatName::Life).x;
    }
    else
        return 0;
}

/****************
 * LoadFromFile *
 ****************/
void Object::loadFromFile(){

    std::string filename = "Data/Files/Objects/" + name + ".cfg";

    std::ifstream file(filename);
    if(!file.is_open())
        throw std::runtime_error("Failed to load " + filename);

    while(!file.eof()){

        std::string line;
        std::getline(file, line);
        std::istringstream sLine(line);

        std::string statName;
        std::string statVal;

        sLine >> statName >> statVal;

        if(statName == "StackSize")
            stackSize = abs(std::stoi(statVal));
        else if(statName == "Type") {

            if(statVal == "Weapon" || statVal == "Helmet" || statVal == "Amulet" || statVal == "ChestPlate" || statVal == "Leggings" || statVal == "Boots"){

                setType(Entity::Stuff);
                type = Stuff;
            }
            else if(statVal == "Potion"){

                setType(Entity::Potion);
                type = Potion;
            }
            else if(statVal == "Loot"){

                setType(Entity::Object);
                type = Loot;
            }
        }
        else if(statName == "BuyPrice")
            prices.first = std::stoi(statVal);
        else if(statName == "SellPrice")
            prices.second = std::stoi(statVal);
    }
    if(type != Loot)
        bonus = new Bonus(name);
}

/********
 * Draw *
 ********/
void Object::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    
    states.transform *= getTransform();
    target.draw(sprite, states);
}
