#include "factory.h"
#include "squirrel.h"
#include "werewolf.h"
#include "druid.h"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::SquirrelType:
            return std::make_shared<Squirrel>(name, x, y);
        case NpcType::WerewolfType:
            return std::make_shared<Werewolf>(name, x, y);
        case NpcType::DruidType:
            return std::make_shared<Druid>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}
