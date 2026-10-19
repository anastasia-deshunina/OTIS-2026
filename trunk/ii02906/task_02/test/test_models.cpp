#include <gtest/gtest.h>
#include "LinearModel.h"
#include "NonLinearModel.h"
#include "DiffEqModel.h"

// Тест 1: Проверка правильности значений линейной модели (ручной расчет)
TEST(LinearModelTest, StepCalculation) {
    LinearModel model(0.5, 0.0, 0.0, 1.0);
    // y_{t+1} = 0.5*0 + 0 + 0 + 1*1 = 1.0
    EXPECT_DOUBLE_EQ(model.step(1.0), 1.0);
}

// Тест 2: Проверка устойчивости (устойчивый случай)
TEST(StabilityTest, StableCase) {
    LinearModel model(0.5, 0.2, 0.1, 1.0);
    EXPECT_TRUE(model.isStable());
}

// Тест 3: Проверка устойчивости (неустойчивый случай)
TEST(StabilityTest, UnstableCase) {
    LinearModel model(2.0, 0.0, 0.0, 1.0);
    EXPECT_FALSE(model.isStable());
}

// Тест 4: Проверка нелинейной модели (граничное значение)
TEST(NonlinearModelTest, ZeroState) {
    NonLinearModel model(1.0, 1.0);
    EXPECT_DOUBLE_EQ(model.step(0.0), 0.0);
}

// Тест 5: Проверка дифференциального уравнения (инвариант)
TEST(DiffEqModelTest, ZeroState) {
    DiffEqModel model(1.0, 0.01);
    EXPECT_DOUBLE_EQ(model.step(0.0), 0.0);
}