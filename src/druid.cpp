#include "druid.h"
#include "visitor.h"

Druid::Druid(const std::string& name, int x, int y)
    : NPC(NpcType::DruidType, name, x, y) {}

void Druid::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Druid::print() const {
    if (alive) {
        std::cout << "Druid - Name: " << name
                << ", Coordinates: (" << x << ", " << y << ")" << std::endl;   
    }
}

void Druid::save(std::ostream& os) const {
    NPC::save(os);
}
