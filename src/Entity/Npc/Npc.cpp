#include "Npc.h"

Npc::Npc(std::string name, TextureManager* txtMgr):
        Entity(txtMgr, Type::Npc),
        name(name){

    loadFromFile();
    setSprite();
}