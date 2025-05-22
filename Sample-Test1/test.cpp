#include "pch.h"
#include "../AIS/Antibody.h"
#include "../AIS/Simulator.h"
#include <vector>
#include <algorithm>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

// “ест конструктора
TEST(AntibodyTest, Constructor) {
    // ѕроверка создани€ антитела с размерностью 3
    Antibody antibody(3);
    EXPECT_EQ(antibody.position.size(), 3);
    EXPECT_GE(antibody.position[0], -20.0);
    EXPECT_LE(antibody.position[0], 20.0);
    EXPECT_GE(antibody.position[1], -20.0);
    EXPECT_LE(antibody.position[1], 20.0);
    EXPECT_GE(antibody.position[2], -20.0);
    EXPECT_LE(antibody.position[2], 20.0);

    // ѕроверка создани€ антитела с пользовательскими границами
    Antibody antibodyCustom(3, { -10.0, 10.0 });
    EXPECT_EQ(antibodyCustom.position.size(), 3);
    EXPECT_GE(antibodyCustom.position[0], -10.0);
    EXPECT_LE(antibodyCustom.position[0], 10.0);
    EXPECT_GE(antibodyCustom.position[1], -10.0);
    EXPECT_LE(antibodyCustom.position[1], 10.0);
    EXPECT_GE(antibodyCustom.position[2], -10.0);
    EXPECT_LE(antibodyCustom.position[2], 10.0);
}