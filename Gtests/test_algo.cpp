#include <gtest/gtest.h>
#include <string>

extern "C" {
    #include "trivial/trivial.h"
}

// только позитивные
TEST(Trivial_algo, only_positive) {
    int emotional_color;
    char buffer[] = {":):):):)"};
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// только негативные
TEST(Trivial_algo, only_negative) {
    int emotional_color;
    char buffer[] = {":(:(:(:("};
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, NEGATIVE);
}

// вперемешку позитивные
TEST(Trivial_algo, dirty_negative) {
    int emotional_color;
    char buffer[] = {"n:(go:)yw:)dt:)wi:("};
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// вперемешку, нейтральные
TEST(Trivial_algo, dirty_neutral) {
    int emotional_color;
    char buffer[] = {":):)go:)yw:(dt:(wi:("};
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, NEUTRAL);
}

// вперемешку, нейтральные
TEST(Trivial_algo, empty_neutral) {
    int emotional_color;
    char buffer[] = {""};
    trivial_emotional_color(buffer, &emotional_color);
    ASSERT_EQ(emotional_color, NEUTRAL);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}