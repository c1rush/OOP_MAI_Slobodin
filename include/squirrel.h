#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "npc.h"

struct Squirrel : public NPC {
    Squirrel(const std::string& name, int x, int y);
    ~Squirrel() override = default;

    void accept(Visitor& visitor, std::shared_ptr<NPC> other) override;

    void print() const override;
    void save(std::ostream& os) const override;
};

#endif
