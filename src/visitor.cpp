#include "visitor.h"
#include "npc.h"
#include "squirrel.h"
#include "werewolf.h"
#include "druid.h"

Visitor::Visitor(NPC& attacker)
    : attacker(attacker), attackerDies(false), defenderDies(false) {}

void Visitor::visit(Squirrel& squirrel, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::WerewolfType || attacker.type == NpcType::DruidType) {
        defenderDies = true; // Белка убивает всех
    }
}

void Visitor::visit(Werewolf& werewolf, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::DruidType) {
        defenderDies = true; // Оборотень убивает Друида
    } else if (attacker.type == NpcType::SquirrelType) {
        attackerDies = true; // Белка убивает Оборотня
    }
}

void Visitor::visit(Druid& druid, std::shared_ptr<NPC> other) {
    if (attacker.type == NpcType::SquirrelType || attacker.type == NpcType::WerewolfType) {
        defenderDies = true; // Друид умирает от всех
    }
}
