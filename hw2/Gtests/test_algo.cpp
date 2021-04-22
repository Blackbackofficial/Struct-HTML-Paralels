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
    parallel_emotional_color((void (*)()) parallel_emotional_color, buffer, &emotional_color, 17);
    ASSERT_EQ(emotional_color, NEGATIVE);
}

// считываение библиотеки проверка на пустоту
TEST(PARALLEL_ALGO, p_null_void) {
    int emotional_color = 0;
    const char buffer[17] = ":(:(:(:(:(:(:(:(";
    void (*pre)() = nullptr;
    parallel_emotional_color(pre, buffer, &emotional_color, 17);
    ASSERT_EQ(emotional_color, 0);
}

// подсчет положительной эмоциональной окраски
TEST(PARALLEL_ALGO, p_like_color) {
    int emotional_color;
    const char buffer[17] = ":):):):):):):):)";
    parallel_emotional_color((void (*)()) parallel_emotional_color, buffer, &emotional_color, 17);
    ASSERT_EQ(emotional_color, POSITIVE);
}

// подсчет нейтральной эмоциональной окраски
TEST(PARALLEL_ALGO, p_neutral_color) {
    int emotional_color = 0;
    const char buffer[86] = "e:)wewdewdwewewe:(fhwjhe2";
    parallel_emotional_color((void (*)()) parallel_emotional_color, buffer, &emotional_color, 86);
    ASSERT_EQ(emotional_color, NEUTRAL);
}

// проверка на создание и очистки
TEST(PARALLEL_ALGO, p_new_del_pipes) {
    size_t process = sysconf(_SC_NPROCESSORS_ONLN);
    FD_P * pipes = new_pipes(process);
    ASSERT_EQ((long) del_new_description(pipes, process), NULL);
}

// если процессов свободных нет
TEST(PARALLEL_ALGO, p_null_color) {
    int process = 0;
    FD_P * pipes = new_pipes(process);
    ASSERT_EQ((long) pipes, NULL);
    del_new_description(pipes, process);
}