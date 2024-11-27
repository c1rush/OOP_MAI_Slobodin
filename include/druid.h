#ifndef DRUID_H
#define DRUID_H

#include "npc.h"

struct Druid : public NPC {
    Druid(const std::string& name, int x, int y);
    ~Druid() override = default;

    void accept(Visitor& visitor, std::shared_ptr<NPC> other) override;

    void print() const override;
    void save(std::ostream& os) const override;
};

#endif
