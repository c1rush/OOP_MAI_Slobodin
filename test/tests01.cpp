#include <gtest/gtest.h>
#include "trapezoid.h"
#include "rhombus.h"
#include "pentagon.h"
#include "figure_array.h"

// Тест для класса Trapezoid
TEST(TrapezoidTest, AreaCalculation) {
    Trapezoid trapezoid({0, 0}, {1, 1}, {2, 1}, {2, 0});
    EXPECT_NEAR(double(trapezoid), 1.5, 1e-5);
}

TEST(TrapezoidTest, CenterCalculation) {
    Trapezoid trapezoid({0, 0}, {1, 1}, {2, 1}, {2, 0});
    auto center = trapezoid.Center();
    EXPECT_NEAR(center.first, 1.25, 1e-1);
    EXPECT_NEAR(center.second, 0.5, 1e-1);
}

TEST(TrapezoidTest, AssignAndCompare) {
    Figure* t1 = new Trapezoid({0, 0}, {1, 1}, {2, 1}, {2, 0});
    Figure* t2 = new Trapezoid();
    *t2 = *t1;
    EXPECT_TRUE(*t1 == *t2);
}

// Тест для класса Rhombus
TEST(RhombusTest, AreaCalculation) {
    Rhombus rhombus({0, 0}, {1, 1}, {2, 0}, {1, -1});
    EXPECT_NEAR(double(rhombus), 2.0, 1e-1);
}

TEST(RhombusTest, CenterCalculation) {
    Rhombus rhombus({0, 0}, {1, 1}, {2, 0}, {1, -1});
    auto center = rhombus.Center();
    EXPECT_NEAR(center.first, 1.0, 1e-1);
    EXPECT_NEAR(center.second, 0.0, 1e-1);
}

TEST(RhombusTest, AssignAndCompare) {
    Figure* r1 = new Rhombus({0, 0}, {1, 1}, {2, 0}, {1, -1});
    Figure* r2 = new Rhombus();
    *r2 = *r1;
    EXPECT_TRUE(*r1 == *r2);
}

// Тест для класса Pentagon
TEST(PentagonTest, AreaCalculation) {
    Pentagon pentagon({1, 0}, {0.309, 0.951}, {-0.809, 0.588}, 
                      {-0.809, -0.588}, {0.309, -0.951});
    EXPECT_NEAR(double(pentagon), 2.377, 1e-1); // Площадь правильного пятиугольника
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon pentagon({1, 0}, {0.309, 0.951}, {-0.809, 0.588}, 
                      {-0.809, -0.588}, {0.309, -0.951});
    auto center = pentagon.Center();
    EXPECT_NEAR(center.first, 0.0, 1e-1);
    EXPECT_NEAR(center.second, 0.0, 1e-1);
}

TEST(PentagonTest, AssignAndCompare) {
    Figure* p1 = new Pentagon({1, 0}, {0.309, 0.951}, {-0.809, 0.588}, 
                {-0.809, -0.588}, {0.309, -0.951});
    Figure* p2 = new Pentagon();
    *p2 = *p1;
    EXPECT_TRUE(*p1 == *p2);
}

// Тесты для класса FigureArray
TEST(FigureArrayTest, AddFiguresAndCalculateTotalArea) {
    FigureArray array;
    
    // Добавляем фигуры
    Figure* trapezoid = new Trapezoid({0, 0}, {1, 1}, {2, 1}, {2, 0});
    Figure* rhombus = new Rhombus({0, 0}, {1, 1}, {2, 0}, {1, -1});
    Figure* pentagon = new Pentagon({1, 0}, {0.309, 0.951}, {-0.809, 0.588}, 
                                    {-0.809, -0.588}, {0.309, -0.951});
    
    array.AddFigure(std::move(trapezoid));
    array.AddFigure(std::move(rhombus));
    array.AddFigure(std::move(pentagon));
    
    // Проверяем общую площадь
    EXPECT_NEAR(array.TotalArea(), 5.877, 1e-1); // Сумма площадей всех фигур
}

TEST(FigureArrayTest, RemoveFigureAndCheckRemainingArea) {
    FigureArray array;
    
    // Добавляем фигуры
    Figure* trapezoid = new Trapezoid({0, 0}, {1, 1}, {2, 1}, {2, 0});
    Figure* rhombus = new Rhombus({0, 0}, {1, 1}, {2, 0}, {1, -1});
    Figure* pentagon = new Pentagon({1, 0}, {0.309, 0.951}, {-0.809, 0.588}, 
                                    {-0.809, -0.588}, {0.309, -0.951});
    
    array.AddFigure(std::move(trapezoid));
    array.AddFigure(std::move(rhombus));
    array.AddFigure(std::move(pentagon));
    
    // Удаляем одну фигуру (ромб)
    array.RemoveFigure(1);
    
    // Проверяем оставшуюся площадь
    EXPECT_NEAR(array.TotalArea(), 3.877, 1e-1); // Оставшиеся фигуры после удаления ромба
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}