#include <gtest/gtest.h>
#include <cstring>

extern "C" {
#include "html.h"
}

// просто проверка на то что все подтягивает и в конце ничего не добавляет тк память не выделена
TEST(TEST_HTML_TAG, start_tag) {
    char str[SIZE_VALUE] = R"(<form  action="/questions/511196/answer/submit" class="js-add-answer-component post-form">\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    ASSERT_STREQ(tag[0].name,"form\0");
    ASSERT_STREQ(tag[0].value,"open");
    ASSERT_STREQ(tag[1].name,"action");
    ASSERT_STREQ(tag[1].value, "/questions/511196/answer/submit");
    ASSERT_STREQ(tag[2].name, "class");
    ASSERT_STREQ(tag[2].value, "js-add-answer-component post-form");
    free(tag);
}

// проверка на пробелл перед тегом (такой тег не валиден)
TEST(TEST_HTML_TAG, error_start_tag) {
    char str[SIZE_VALUE] = R"(< form class="js-add-answer-component post-form">\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "0"), 0);
    EXPECT_EQ(tag->name[0], '0');
    free(tag);
}

// проверка на то что он закрывающий (close) и в name не хранит символ "/"
TEST(TEST_HTML_TAG, close_tag) {
    char str[SIZE_VALUE] = R"(</form>\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "form"), 0);
    EXPECT_EQ(strcmp(tag->value, "close"), 0);
    free(tag);
}
// проверка на отступ после "/" в случае закрывающего тега
TEST(TEST_HTML_TAG, error_close_tag) {
    char str[SIZE_VALUE] = R"(</ form>\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "0"), 0);
    EXPECT_EQ(tag->name[0], '0');
    free(tag);
}

// проверка на правильный нейминг атрибутов тега, никаких символов (только в value атрибута)
TEST(TEST_HTML_TAG, error_attribute_tag) {
    char str[SIZE_VALUE] = R"(<form c);l"a;ss="js-add-answer-component post-form">\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "0"), 0);
    EXPECT_EQ(tag->name[0], '0');
    free(tag);
}

// проверка на то как он читает пробеллы (дышащий тег)
TEST(TEST_HTML_TAG, spaces_in_tag) {
    char str[SIZE_VALUE] = R"(<form   action =  " /questions/511196/answer/submit " >\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    ASSERT_STREQ(tag[0].name, "form");
    ASSERT_STREQ(tag[0].value, "open");
    ASSERT_STREQ(tag[1].name, "action");
    ASSERT_STREQ(tag[1].value, " /questions/511196/answer/submit ");
    free(tag);
}

// проверка на то что тег содержит "<"
TEST(TEST_HTML_TAG,  error_start_str_tag) {
    char str[SIZE_VALUE] = R"(  form   action="/questions/">\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "0"), 0);
    EXPECT_EQ(tag->name[0], '0');
}

// проверка на то что тег содержит ">"
TEST(TEST_HTML_TAG,  error_end_str_tag) {
    char str[SIZE_VALUE] = R"( <form   action="/questions/"\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "0"), 0);
    EXPECT_EQ(tag->name[0], '0');
    free(tag);
}

// проверка на то что он пустой
TEST(TEST_HTML_TAG,  null_str_tag) {
    char str[SIZE_VALUE] = R"( )";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    EXPECT_EQ(strcmp(tag->name, "0"), 0);
    EXPECT_EQ(tag->name[0], '0');
    free(tag);
}

// Есть особая форма атрибута без кавычек (action=/search) и не такое бывает
TEST(TEST_HTML_TAG,  spechial_attr_tag) {
    char str[SIZE_VALUE] = R"(<form  action=/search class="post-form">\n)";
    int size = 0;
    html * tag = (html *) html_decoder(str, &size);
    ASSERT_STREQ(tag[0].name, "form");
    ASSERT_STREQ(tag[0].value, "open");
    ASSERT_STREQ(tag[1].name, "action");
    ASSERT_STREQ(tag[1].value, "/search");
    ASSERT_STREQ(tag[2].name, "class");
    ASSERT_STREQ(tag[2].value, "post-form");
    free(tag);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}