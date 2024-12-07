#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <atomic>
#include <sstream>
#include <npc.h>
#include <squirrel.h>
#include <werewolf.h>
#include <druid.h>
#include <visitor.h>
#include <observer.h>
#include <factory.h>
#include <scheduler.h>

std::vector<std::shared_ptr<NPC>> npcs;
std::atomic<bool> game_over(false);

class NPCTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Инициализация NPC
        auto elf = NPCFactory::createNPC(NpcType::SquirrelType, "TestSquirrel", 10, 10);
        auto dragon = NPCFactory::createNPC(NpcType::WerewolfType, "TestWerewolf", 20, 20);
        auto druid = NPCFactory::createNPC(NpcType::DruidType, "TestDruid", 30, 30);
        
        npcs.push_back(elf);
        npcs.push_back(dragon);
        npcs.push_back(druid);
    }
    
    void TearDown() override {
        npcs.clear();
        game_over.store(false);
    }
};



TEST_F(NPCTest, CreationTest) {
    ASSERT_EQ(npcs.size(), 3);

    EXPECT_EQ(npcs[0]->name, "TestSquirrel");
    EXPECT_EQ(npcs[1]->name, "TestWerewolf");
    EXPECT_EQ(npcs[2]->name, "TestDruid");

    EXPECT_EQ(npcs[0]->x, 10);
    EXPECT_EQ(npcs[0]->y, 10);
    EXPECT_EQ(npcs[1]->x, 20);
    EXPECT_EQ(npcs[1]->y, 20);
    EXPECT_EQ(npcs[2]->x, 30);
    EXPECT_EQ(npcs[2]->y, 30);
}

TEST_F(NPCTest, Movement) {
    auto initial_x = npcs[0]->x;
    auto initial_y = npcs[0]->y;

    // Запускаем корутину перемещения NPC
    auto task = npcs[0]->run();
    Scheduler::instance().schedule(std::move(task));
    Scheduler::instance().run();

    // Проверяем, что NPC переместился
    EXPECT_NE(npcs[0]->x, initial_x);
    EXPECT_NE(npcs[0]->y, initial_y);
}

TEST_F(NPCTest, Interaction) {
    // Устанавливаем NPC близко друг к другу для сражения
    npcs[0]->x = 50;
    npcs[0]->y = 50;

    npcs[1]->x = 50;
    npcs[1]->y = 50;

    // Запускаем корутину
    auto task0 = npcs[0]->run();
    auto task1 = npcs[1]->run();
    Scheduler::instance().schedule(std::move(task0));
    Scheduler::instance().schedule(std::move(task1));

    // Запускаем планировщик несколько раз, чтобы произошёл бой
    for (int i = 0; i < 10; ++i) {
        Scheduler::instance().run();
    }

    bool werewolf_alive = npcs[1]->alive;
    bool squirrel_alive = npcs[0]->alive;

    EXPECT_TRUE(!squirrel_alive || werewolf_alive);
}

TEST_F(NPCTest, GameOver) {
    game_over.store(true);

    auto task = npcs[0]->run();
    Scheduler::instance().schedule(std::move(task));
    Scheduler::instance().run();

    // Проверяем, что NPC завершил свою корутину
    EXPECT_TRUE(task.done());
}


// Тест на вычисление расстояния
TEST_F(NPCTest, DistanceTest) {
    auto npc1 = npcs[0]; // TestElf at (10,10)
    auto npc2 = NPCFactory::createNPC(NpcType::WerewolfType, "Werewolf1", 13, 14);

    EXPECT_TRUE(npc1->isClose(npc2, 5));
    EXPECT_FALSE(npc1->isClose(npc2, 4));
}


// Тест на бой между NPC
TEST_F(NPCTest, FightTest) {
    auto squirrel = npcs[0];
    auto werewolf = npcs[1];
    auto druid = npcs[2];

    Visitor fight1(*squirrel);
    druid->accept(fight1, squirrel);

    EXPECT_FALSE(fight1.attackerDies);
    EXPECT_TRUE(fight1.defenderDies);

    Visitor fight2(*werewolf);
    druid->accept(fight2, werewolf);

    EXPECT_FALSE(fight2.attackerDies);
    EXPECT_TRUE(fight2.defenderDies);

    Visitor fight3(*squirrel);
    werewolf->accept(fight3, squirrel);

    EXPECT_TRUE(fight3.attackerDies);
    EXPECT_FALSE(fight3.defenderDies);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
