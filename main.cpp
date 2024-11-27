#include "npc.h"
#include "factory.h"
#include "visitor.h"
#include "observer.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <set>

using SetNPC = std::set<std::shared_ptr<NPC>>;

// Сохранение NPC в файл
void saveNPCs(const SetNPC& npcs, const std::string& filename) {
    std::ofstream ofs(filename);
    if (ofs.is_open()) {
        ofs << npcs.size() << '\n';
        for (const auto& npc : npcs) {
            npc->save(ofs);
        }
    }
}

// Загрузка NPC из файла
SetNPC loadNPCs(const std::string& filename) {
    SetNPC npcs;
    std::ifstream ifs(filename);
    if (ifs.is_open()) {
        size_t size;
        ifs >> size;
        for (size_t i = 0; i < size; ++i) {
            auto npc = NPC::load(ifs);
            if (npc) {
                npcs.insert(npc);
            }
        }
    }
    return npcs;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    SetNPC npcs;

    // Создаем NPC и добавляем наблюдателей
    auto squirrel = NPCFactory::createNPC(NpcType::SquirrelType, "Squirrel", 10, 10);
    auto werewolf = NPCFactory::createNPC(NpcType::WerewolfType, "Werewolf", 15, 15);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Druid", 20, 20);

    auto consoleObserver = std::make_shared<ConsoleObserver>();
    squirrel->addObserver(consoleObserver);
    werewolf->addObserver(consoleObserver);
    druid->addObserver(consoleObserver);

    npcs.insert(squirrel);
    npcs.insert(werewolf);
    npcs.insert(druid);

    // Сохраняем NPC в файл
    saveNPCs(npcs, "npcs.txt");

    // Загружаем NPC из файла
    auto loadedNPCs = loadNPCs("npcs.txt");

    // Выводим информацию о загруженных NPC
    for (const auto& npc : loadedNPCs) {
        npc->print();
    }

    return 0;
}
