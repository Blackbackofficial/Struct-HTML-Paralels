#include <gtest/gtest.h>
#include <cstring>

extern "C" {
    #include "main.h"
}

// просто проверка на то что все подтягивает и в конце ничего не добавляет тк память не выделена
TEST(TEST_HTML_TAG, start_tag) {
    char str[SIZE_VALUE] = R"(<form  action="/questions/511196/answer/submit" class="js-add-answer-component post-form">)";
    html * tag = html_decoder(str);
    if (strcmp(tag[0].name, "form") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[0].value, "open") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[1].name, "action") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[1].value, "/questions/511196/answer/submit") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[2].name, "class") != 0)
        GTEST_FAIL() << " Wrong answer";
    if (strcmp(tag[2].value, "js-add-answer-component post-form") != 0)
        GTEST_FAIL() << "Wrong answer";
//    free(tag);
}

// проверка на пробелл перед тегом (такой тег не валиден)
TEST(TEST_HTML_TAG, error_start_tag) {
    char str[SIZE_VALUE] = R"(< form class="js-add-answer-component post-form">)";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "0") != 0)
        GTEST_FAIL() << "Incorrect name tag";
    EXPECT_EQ(tag->name[0], '0');
}

// проверка на то что он закрывающий (close) и в name не хранит символ "/"
TEST(TEST_HTML_TAG, close_tag) {
    char str[SIZE_VALUE] = R"(</form>)";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "form") != 0)
        GTEST_FAIL() << " Wrong answer";
    if (strcmp(tag->value, "close") != 0)
        GTEST_FAIL() << "Wrong answer";
}
// проверка на отступ после "/" в случае закрывающего тега
TEST(TEST_HTML_TAG, error_close_tag) {
    char str[SIZE_VALUE] = R"(</ form>)";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "0") != 0)
        GTEST_FAIL() << "Incorrect name tag";
    EXPECT_EQ(tag->name[0], '0');
}

// проверка на правильный нейминг атрибутов тега, никаких символов (только в value атрибута)
TEST(TEST_HTML_TAG, error_attribute_tag) {
    char str[SIZE_VALUE] = R"(<form c);l"a;ss="js-add-answer-component post-form">)";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "0") != 0)
        GTEST_FAIL() << "Incorrect name tag";
    EXPECT_EQ(tag->name[0], '0');
}

// проверка на то как он читает пробеллы (дышащий тег)
TEST(TEST_HTML_TAG, spaces_in_tag) {
    char str[SIZE_VALUE] = R"(<form   action =  " /questions/511196/answer/submit " >)";
    html * tag = html_decoder(str);
    if (strcmp(tag[0].name, "form") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[0].value, "open") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[1].name, "action") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[1].value, " /questions/511196/answer/submit ") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[2].value, "") != 0)
        GTEST_FAIL() << "Bad alloc";
}

// проверка на то что тег содержит "<"
TEST(TEST_HTML_TAG,  error_start_str_tag) {
    char str[SIZE_VALUE] = R"(  form   action="/questions/">)";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "0") != 0)
        GTEST_FAIL() << "Incorrect name tag";
    EXPECT_EQ(tag->name[0], '0');
}

// проверка на то что тег содержит ">"
TEST(TEST_HTML_TAG,  error_end_str_tag) {
    char str[SIZE_VALUE] = R"( <form   action="/questions/")";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "0") != 0)
        GTEST_FAIL() << "Incorrect name tag";
    EXPECT_EQ(tag->name[0], '0');
}

// проверка на то что он пустой
TEST(TEST_HTML_TAG,  null_str_tag) {
    char str[SIZE_VALUE] = R"( )";
    html * tag = html_decoder(str);
    if (strcmp(tag->name, "0") != 0)
        GTEST_FAIL() << "IS NULL";
    EXPECT_EQ(tag->name[0], '0');
}

// Есть особая форма атрибута без кавычек (action=/search) и не такое бывает
TEST(TEST_HTML_TAG,  spechial_attr_tag) {
    char str[SIZE_VALUE] = R"(<form  action=/search class="post-form">)";
    html * tag = html_decoder(str);
    if (strcmp(tag[0].name, "form") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[0].value, "open") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[1].name, "action") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[1].value, "/search") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[2].name, "class") != 0)
        GTEST_FAIL() << "Wrong answer";
    if (strcmp(tag[2].value, "post-form") != 0)
        GTEST_FAIL() << "Wrong answer";
}

// случай если слишком большая строчка
//TEST(TEST_HTML_TAG,  max_str_tag) {
//    char str[SIZE_VALUE+512] = R"(<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet" rel="stylesheet" href="https://fonts.googleapis.com/css?family=Roboto:300,400,500,700" rel="stylesheet">)";
//    html * tag = html_decoder(str);
//    if (strcmp(tag->name, "0") != 0)
//        GTEST_FAIL() << "IS NULL";
//    EXPECT_EQ(tag->name[0], '0');
//}

int main(int argc, char** argv) {
    // The following line must be executed to initialize Google Mock
    // (and Google Test) before running the tests.
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
