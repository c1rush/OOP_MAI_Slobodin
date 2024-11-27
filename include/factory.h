#ifndef FACTORY_H
#define FACTORY_H

#include "npc.h"
#include "squirrel.h"
#include "werewolf.h"
#include "druid.h"
#include <memory>

struct NPCFactory {
    static std::shared_ptr<NPC> createNPC(NpcType type, const std::string& name, int x, int y);
};

#endif
