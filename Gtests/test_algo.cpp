#include <gtest/gtest.h>

extern "C" {
    #include "trivial.h"
}

class Trivial_algo : public ::testing::Test {
protected:
//    virtual void SetUp(void) {
//        // настройка перед запуском очередного теста
//    }
//    virtual void TearDown(void) {
//        // очистка после прогона очередного теста
//    }

    const char *buffer{};
};

// только позитивные
TEST_F(Trivial_algo, only_positive) {
    int emotional_color;
    buffer = ":):):):)";
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// только негативные
TEST_F(Trivial_algo, only_negative) {
    int emotional_color;
    buffer = ":(:(:(:(";
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, NEGATIVE);
}

// вперемешку позитивные
TEST_F(Trivial_algo, dirty_negative) {
    int emotional_color;
    buffer = "n:(go:)yw:)dt:)wi:(";
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// вперемешку, нейтральные
TEST_F(Trivial_algo, dirty_neutral) {
    int emotional_color;
    buffer = ":):)go:)yw:(dt:(wi:(";
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, NEUTRAL);
}

// вперемешку, нейтральные
TEST_F(Trivial_algo, empty_neutral) {
    int emotional_color;
    buffer = "";
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, NEUTRAL);
}