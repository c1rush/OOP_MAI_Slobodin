#include "squirrel.h"
#include "visitor.h"

Squirrel::Squirrel(const std::string& name, int x, int y)
    : NPC(NpcType::SquirrelType, name, x, y) {}

void Squirrel::accept(Visitor& visitor, std::shared_ptr<NPC> other) {
    visitor.visit(*this, other);
}

void Squirrel::print() const {
    std::cout << "Squirrel - Name: " << name
              << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
}

void Squirrel::save(std::ostream& os) const {
    NPC::save(os);
}
