#include "npc.h"
#include "factory.h"
#include "observer.h"
#include "logger.h"
#include "scheduler.h"

#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

std::vector<std::shared_ptr<NPC>> npcs;
std::atomic<bool> game_over(false);

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Наблюдатели
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");

    // НПС
    const int num_npcs = 50;
    for (int i = 0; i < num_npcs; ++i) {
        NpcType type = static_cast<NpcType>(std::rand() % 3 + 1);
        std::string name = "NPC_" + std::to_string(i);
        int x = std::rand() % 101;
        int y = std::rand() % 101;

        auto npc = NPCFactory::createNPC(type, name, x, y);
        npc->addObserver(consoleObserver);
        npc->addObserver(fileObserver);

        npcs.push_back(npc);
    }

    // Корутины
    for (auto& npc : npcs) {
        Scheduler::instance().schedule(npc->run());
    }

    // Планировщик в отдельном потоке
    std::thread scheduler_thread([]() {
        while (!game_over) {
            Scheduler::instance().run();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // Поток для карты
    auto start_time = std::chrono::steady_clock::now();
    while (!game_over) {
        Logger::logBlock([&]() {
            std::cout << "Current NPC positions:" << std::endl;
            for (const auto& npc : npcs) {
                if (npc->alive) {
                    npc->print();
                }
            }
            std::cout << "-------------------------------------" << std::endl;
        });

        std::this_thread::sleep_for(std::chrono::seconds(1));

        // 30 сек
        auto elapsed = std::chrono::steady_clock::now() - start_time;
        if (std::chrono::duration_cast<std::chrono::seconds>(elapsed).count() >= 30) {
            game_over = true;
        }
    }

    scheduler_thread.join();

    Logger::log("Game over! Survivors:");
    for (const auto& npc : npcs) {
        if (npc->alive) {
            npc->print();
        }
    }

    return 0;
}