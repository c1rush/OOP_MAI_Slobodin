#ifndef VISITOR_H
#define VISITOR_H

#include <memory>

struct Squirrel;
struct Werewolf;
struct Druid;
struct NPC;

struct Visitor {
    NPC& attacker;       // Атакующий NPC
    bool attackerDies;   // Флаг гибели атакующего
    bool defenderDies;   // Флаг гибели защищающегося

    Visitor(NPC& attacker);

    void visit(Squirrel& squirrel, std::shared_ptr<NPC> other);
    void visit(Werewolf& werewolf, std::shared_ptr<NPC> other);
    void visit(Druid& druid, std::shared_ptr<NPC> other);
};

#endif
