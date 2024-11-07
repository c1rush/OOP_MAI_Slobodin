#include <gtest/gtest.h>
#include "../src/pentagon.h"
#include "../src/rhombus.h"
#include "../src/trapezoid.h"
#include "../src/array.h"
#include <cmath>

using namespace Shape;

TEST(PentagonTests, AreaCenter) {
    auto pentagon = Pentagon<double>({
        Point<double>{0, 0},
        Point<double>{1, 1},
        Point<double>{2, 1},
        Point<double>{2, -1},
        Point<double>{1, -1}
    });

    auto center = pentagon.Center();
    EXPECT_NEAR(center->x, 1.222222, 1e-6);
    EXPECT_NEAR(center->y, 0.0, 1e-6);
    EXPECT_NEAR(static_cast<double>(pentagon), 3.0, 1e-6);
}

TEST(RhombusTests, AreaCenter) {
    auto center = Point<double>{0, 0};
    auto rhombus = Rhombus<double>(center, 2.0, 4.0);

    auto rhombus_center = rhombus.Center();
    EXPECT_NEAR(rhombus_center->x, center.x, 1e-6);
    EXPECT_NEAR(rhombus_center->y, center.y, 1e-6);
    EXPECT_NEAR(static_cast<double>(rhombus), 4.0, 1e-6);
}

TEST(TrapezoidTests, AreaCenter) {
    auto p1 = Point<double>{0, 0};
    auto p2 = Point<double>{2, 0};
    auto trapezoid = Trapezoid<double>(p1, p2, 2.0);

    auto center = trapezoid.Center();
    EXPECT_NEAR(center->x, 1.0, 1e-6);
    EXPECT_NEAR(center->y, 1.0, 1e-6);
    EXPECT_NEAR(static_cast<double>(trapezoid), 4.0, 1e-6);
}

TEST(ArrayTests, TotalArea) {
    auto pentagon = Pentagon<double>({
        Point<double>{0, 0},
        Point<double>{1, 1},
        Point<double>{2, 1},
        Point<double>{2, -1},
        Point<double>{1, -1}
    });
    auto rhombus = Rhombus<double>(Point<double>{0, 0}, 2.0, 4.0);
    auto trapezoid = Trapezoid<double>(Point<double>{0, 0}, Point<double>{2, 0}, 2.0);

    Array<IFigure*> figures = {&pentagon, &rhombus, &trapezoid};

    EXPECT_NEAR(figures.TotalArea(), 11.0, 1e-6);
}

TEST(ArrayTests, SubscriptOperator) {
    auto pentagon = Pentagon<double>({
        Point<double>{0, 0},
        Point<double>{1, 1},
        Point<double>{2, 1},
        Point<double>{2, -1},
        Point<double>{1, -1}
    });
    auto rhombus = Rhombus<double>(Point<double>{0, 0}, 2.0, 4.0);
    auto trapezoid = Trapezoid<double>(Point<double>{0, 0}, Point<double>{2, 0}, 2.0);

    Array<IFigure*> figures;
    figures.push_back(&pentagon);
    figures.push_back(&rhombus);
    figures.push_back(&trapezoid);

    EXPECT_EQ(figures.size(), 3);
    EXPECT_EQ(double(*figures[0]), 3.0);
    EXPECT_EQ(double(*figures[1]), 4.0);
    EXPECT_EQ(double(*figures[2]), 4.0);
}

TEST(ArrayTests, RemoveAt) {
    auto pentagon = Pentagon<double>({
        Point<double>{0, 0},
        Point<double>{1, 1},
        Point<double>{2, 1},
        Point<double>{2, -1},
        Point<double>{1, -1}
    });
    auto trapezoid = Trapezoid<double>(Point<double>{0, 0}, Point<double>{2, 0}, 2.0);

    Array<IFigure*> figures;
    figures.push_back(&pentagon);
    figures.push_back(&trapezoid);

    EXPECT_EQ(figures.size(), 2);
    figures.remove_at(0);
    EXPECT_EQ(figures.size(), 1);
    EXPECT_EQ(double(*figures[0]), 4.0);
}

TEST(ArrayTests, InvalidIndex) {
    Array<IFigure*> figures;
    EXPECT_THROW(figures[0], std::out_of_range);
    EXPECT_THROW(figures.remove_at(0), std::out_of_range);
}

TEST(ArrayTests, ArrayOfFigures) {
    auto figure1 = Rhombus<double>({
        Point<double>{0, 0},
        Point<double>{0, 2},
        Point<double>{2, 2},
        Point<double>{2, 0}
    });
    auto figure2 = Trapezoid<double>({
        Point<double>{0, 0},
        Point<double>{0, 3},
        Point<double>{3, 3},
        Point<double>{3, 0}
    });

    Array<Figure<double, 4>> figures;
    figures.push_back(figure1);
    figures.push_back(figure2);

    EXPECT_EQ(figures.size(), 2);
    EXPECT_NEAR(static_cast<double>(figures[0]), 4.0, 1e-6);
    EXPECT_NEAR(static_cast<double>(figures[1]), 9.0, 1e-6);
}

TEST(ArrayTests, UsingRemoveAt) {
    auto figure1 = Figure<double, 4>({
        Point<double>{0, 0},
        Point<double>{0, 2},
        Point<double>{2, 2},
        Point<double>{2, 0}
    });
    auto figure2 = Figure<double, 4>({
        Point<double>{0, 0},
        Point<double>{0, 3},
        Point<double>{3, 3},
        Point<double>{3, 0}
    });

    Array<Figure<double, 4>> figures;
    figures.push_back(figure1);
    figures.push_back(figure2);

    EXPECT_EQ(figures.size(), 2);
    figures.remove_at(0);
    EXPECT_EQ(figures.size(), 1);
    EXPECT_NEAR(static_cast<double>(figures[0]), 9.0, 1e-6);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
