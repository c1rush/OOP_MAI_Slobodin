#include "npc.h"
#include "factory.h"

NPC::NPC(NpcType type, const std::string& name, int x, int y)
    : type(type), name(name), x(x), y(y) {}

void NPC::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void NPC::notify(const std::string& event) {
    for (auto& weakObs : observers) {
        if (auto obs = weakObs.lock()) {
            obs->onEvent(event);
        }
    }
}

bool NPC::isClose(const std::shared_ptr<NPC>& other, size_t distance) const {
    int dx = x - other->x;
    int dy = y - other->y;
    return (dx * dx + dy * dy) <= (distance * distance);
}

void NPC::print() const {
    std::cout << "Type: " << static_cast<int>(type)
              << ", Name: " << name
              << ", Coordinates: (" << x << ", " << y << ")" << std::endl;
}

void NPC::save(std::ostream& os) const {
    os << static_cast<int>(type) << ' ' << name << ' ' << x << ' ' << y << '\n';
}

std::shared_ptr<NPC> NPC::load(std::istream& is) {
    int typeInt;
    std::string name;
    int x, y;
    if (is >> typeInt >> name >> x >> y) {
        NpcType type = static_cast<NpcType>(typeInt);
        return NPCFactory::createNPC(type, name, x, y);
    } else {
        throw std::runtime_error("Failed to load NPC from stream.");
    }
}