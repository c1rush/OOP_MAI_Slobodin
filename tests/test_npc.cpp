#include <gtest/gtest.h>
#include <memory>
#include <npc.h>
#include <squirrel.h>
#include <werewolf.h>
#include <druid.h>
#include <visitor.h>
#include <observer.h>
#include <factory.h>

// Тест на создание NPC
TEST(NPCTest, CreationTest) {
    auto squirrel = NPCFactory::createNPC(NpcType::SquirrelType, "Nutty", 100, 200);
    auto werewolf = NPCFactory::createNPC(NpcType::WerewolfType, "Fenrir", 300, 400);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Merlin", 150, 250);

    ASSERT_NE(squirrel, nullptr);
    ASSERT_NE(werewolf, nullptr);
    ASSERT_NE(druid, nullptr);

    EXPECT_EQ(squirrel->name, "Nutty");
    EXPECT_EQ(werewolf->name, "Fenrir");
    EXPECT_EQ(druid->name, "Merlin");

    EXPECT_EQ(squirrel->x, 100);
    EXPECT_EQ(squirrel->y, 200);
    EXPECT_EQ(werewolf->x, 300);
    EXPECT_EQ(werewolf->y, 400);
    EXPECT_EQ(druid->x, 150);
    EXPECT_EQ(druid->y, 250);
}

// Тест на вычисление расстояния
TEST(NPCTest, DistanceTest) {
    auto npc1 = NPCFactory::createNPC(NpcType::SquirrelType, "Squirrel1", 0, 0);
    auto npc2 = NPCFactory::createNPC(NpcType::WerewolfType, "Werewolf1", 3, 4); // Расстояние 5 от npc1

    EXPECT_TRUE(npc1->isClose(npc2, 5));  // Ожидаем, что расстояние будет <= 5
    EXPECT_FALSE(npc1->isClose(npc2, 4)); // Ожидаем, что расстояние не будет <= 4
}


// Тест на бой между NPC
TEST(NPCTest, FightTest) {
    auto squirrel = std::dynamic_pointer_cast<Squirrel>(NPCFactory::createNPC(NpcType::SquirrelType, "Nutty", 0, 0));
    auto werewolf = std::dynamic_pointer_cast<Werewolf>(NPCFactory::createNPC(NpcType::WerewolfType, "Fenrir", 0, 0));
    auto druid = std::dynamic_pointer_cast<Druid>(NPCFactory::createNPC(NpcType::DruidType, "Merlin", 0, 0));

    // Наблюдатели
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    squirrel->addObserver(consoleObserver);
    werewolf->addObserver(consoleObserver);
    druid->addObserver(consoleObserver);

    // Белка атакует друида
    Visitor fight1(*squirrel);
    druid->accept(fight1, squirrel);

    EXPECT_FALSE(fight1.attackerDies);  // Белка не должна погибнуть
    EXPECT_TRUE(fight1.defenderDies);   // Друид должен погибнуть

    // Оборотень атакует белку
    Visitor fight2(*werewolf);
    squirrel->accept(fight2, werewolf);

    EXPECT_FALSE(fight2.attackerDies);  // Оборотень не должен погибнуть
    EXPECT_TRUE(fight2.defenderDies);   // Белка должна погибнуть

    // Друид атакует волка
    Visitor fight3(*druid);
    werewolf->accept(fight3, druid);

    EXPECT_FALSE(fight3.attackerDies);  // Друид не должен погибнуть
    EXPECT_TRUE(fight3.defenderDies);   // Оборотень должен погибнуть
}

// Тест на работу с наблюдателями
TEST(NPCTest, ObserverTest) {
    auto squirrel = NPCFactory::createNPC(NpcType::SquirrelType, "Nutty", 0, 0);
    auto druid = NPCFactory::createNPC(NpcType::DruidType, "Merlin", 0, 0);

    // Создаем mock-объект для наблюдателя
    class MockObserver : public Observer {
    public:
        std::string lastEvent;
        void onEvent(const std::string& event) override {
            lastEvent = event;
        }
    };

    auto mockObserver = std::make_shared<MockObserver>();
    squirrel->addObserver(mockObserver);

    // Белка атакует друида
    Visitor fight(*squirrel);
    druid->accept(fight, squirrel);

    if (fight.defenderDies) {
        squirrel->notify(squirrel->name + " killed " + druid->name); // Белка убивает друида
    }

    EXPECT_EQ(mockObserver->lastEvent, "Nutty killed Merlin");
}

// Тест на сохранение и загрузку NPC
TEST(NPCTest, SaveLoadTest) {
    auto squirrel = NPCFactory::createNPC(NpcType::SquirrelType, "Nutty", 100, 200);

    // Сохраняем NPC в строковый поток
    std::ostringstream oss;
    squirrel->save(oss);

    // Загружаем NPC из строкового потока
    std::istringstream iss(oss.str());
    auto loadedSquirrel = NPC::load(iss);

    ASSERT_NE(loadedSquirrel, nullptr);
    EXPECT_EQ(loadedSquirrel->type, NpcType::SquirrelType);
    EXPECT_EQ(loadedSquirrel->name, "Nutty");
    EXPECT_EQ(loadedSquirrel->x, 100);
    EXPECT_EQ(loadedSquirrel->y, 200);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
