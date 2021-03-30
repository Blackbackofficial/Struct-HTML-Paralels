#include <gtest/gtest.h>

extern "C" {
    #include "trivial.h"
    #include "parallel.h"
}

// только позитивные
TEST(TRIVIAL_ALGO, only_positive) {
    int emotional_color;
    const char buffer[9] = ":):):):)";
    trivial_emotional_color(buffer, &emotional_color, 9);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// только негативные
TEST(TRIVIAL_ALGO, only_negative) {
    int emotional_color;
    const char buffer[9] = ":(:(:(:(";
    trivial_emotional_color(buffer, &emotional_color, 9);
    ASSERT_EQ(emotional_color, NEGATIVE);
}

// вперемешку позитивные
TEST(TRIVIAL_ALGO, dirty_negative) {
    int emotional_color;
    const char buffer[20] = "n:(go:)yw:)dt:)wi:(";
    trivial_emotional_color(buffer, &emotional_color, 21);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// вперемешку, нейтральные
TEST(TRIVIAL_ALGO, dirty_neutral) {
    int emotional_color;
    const char buffer[21] = ":):)go:)yw:(dt:(wi:(";
    trivial_emotional_color(buffer, &emotional_color, 21);
    ASSERT_EQ(emotional_color, NEUTRAL);
}

// вперемешку, нейтральные
TEST(TRIVIAL_ALGO, empty_neutral) {
    int emotional_color;
    const char buffer[1] = "";
    trivial_emotional_color(buffer, &emotional_color, 1);
    ASSERT_EQ(emotional_color, NEUTRAL);
}

// проверка на подсчет положительной суммы
TEST(PARALLEL_ALGO, p_like) {
    const char buffer[9] = ":):):):)";
    size_t start = 0;
    size_t end = 8;
    int sum = 0;
    count_smile(buffer, start, end, &sum);
    ASSERT_EQ(sum, 4);
}

// проверка на подсчет отрицательной суммы
TEST(PARALLEL_ALGO, p_dislike) {
    const char buffer[9] = ":(:(:(:(";
    size_t start = 0;
    size_t end = 8;
    int sum = 0;
    count_smile(buffer, start, end, &sum);
    ASSERT_EQ(sum, -4);
}

// проверка на подсчет суммы из диапазона
TEST(PARALLEL_ALGO, p_like_rage) {
    const char buffer[9] = ":):):):)";
    size_t start = 3;
    size_t end = 8;
    int sum = 0;
    count_smile(buffer, start, end, &sum);
    ASSERT_EQ(sum, 2);
}

// подсчет отрицательной эмоциональной окраски
TEST(PARALLEL_ALGO, p_dislike_color) {
    int emotional_color;
    const char buffer[17] = ":(:(:(:(:(:(:(:(";
    parallel_emotional_color(buffer, &emotional_color, 17);
    ASSERT_EQ(emotional_color, NEGATIVE);
}

// подсчет положительной эмоциональной окраски
TEST(PARALLEL_ALGO, p_like_color) {
    int emotional_color;
    const char buffer[17] = ":):):):):):):):)";
    parallel_emotional_color(buffer, &emotional_color, 17);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// подсчет нейтральной эмоциональной окраски
TEST(PARALLEL_ALGO, p_neutral_color) {
    int emotional_color;
    const char buffer[15] = "):):):):(:(:(:";
    parallel_emotional_color(buffer, &emotional_color, 15);
    ASSERT_EQ(emotional_color, NEUTRAL);
}