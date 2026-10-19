#include <gtest/gtest.h>

#include "str_ops.h"
#include "var_10.h"

TEST(StrOps, AllocCopiesTextIntoNewMemory) {
    char source[] = "hello";
    char* copy = str_alloc(source);

    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy, "hello");
    source[0] = 'H';
    EXPECT_STREQ(copy, "hello");

    str_delete(copy);
    EXPECT_EQ(copy, nullptr);
}

TEST(StrOps, AllocHandlesEmptyAndNullStrings) {
    char* empty = str_alloc("");
    ASSERT_NE(empty, nullptr);
    EXPECT_STREQ(empty, "");
    str_delete(empty);

    EXPECT_EQ(str_alloc(nullptr), nullptr);
}

TEST(StrOps, LengthStopsAtTerminator) {
    const char text[] = {'a', 'b', '\0', 'c', '\0'};
    EXPECT_EQ(str_len(text), 2u);
    EXPECT_EQ(str_len(""), 0u);
    EXPECT_EQ(str_len(nullptr), 0u);
}

TEST(StrOps, CopyIncludesTerminator) {
    char destination[8] = {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'};
    str_copy(destination, "cat");

    EXPECT_STREQ(destination, "cat");
    EXPECT_EQ(destination[3], '\0');
}

TEST(StrOps, DeleteAcceptsNullPointer) {
    char* text = nullptr;
    str_delete(text);
    EXPECT_EQ(text, nullptr);
}

TEST(CountWords, CountsWordsFromAssignmentExample) {
    EXPECT_EQ(str_count_words("hello world test"), 3u);
}

TEST(CountWords, EmptyAndNullInputsHaveNoWords) {
    EXPECT_EQ(str_count_words(""), 0u);
    EXPECT_EQ(str_count_words(nullptr), 0u);
}

TEST(CountWords, WhitespaceOnlyHasNoWords) {
    EXPECT_EQ(str_count_words("  \t\n  "), 0u);
}

TEST(CountWords, RepeatedSeparatorsDoNotCreateWords) {
    EXPECT_EQ(str_count_words("  one   two  "), 2u);
}

TEST(CountWords, RecognizesTabsAndNewlinesAsSeparators) {
    EXPECT_EQ(str_count_words("one\ttwo\nthree"), 3u);
}

TEST(FindSubstring, FindsAssignmentExampleAndWritesPosition) {
    int position = -1;
    EXPECT_TRUE(str_find_substr("hello world test", "world", position));
    EXPECT_EQ(position, 6);
}

TEST(FindSubstring, ReturnsFirstMatchWhenThereAreSeveral) {
    int position = -1;
    EXPECT_TRUE(str_find_substr("banana", "ana", position));
    EXPECT_EQ(position, 1);
}

TEST(FindSubstring, FindsMatchAtBeginningAndAtEnd) {
    int position = -1;
    EXPECT_TRUE(str_find_substr("hello", "he", position));
    EXPECT_EQ(position, 0);
    EXPECT_TRUE(str_find_substr("hello", "lo", position));
    EXPECT_EQ(position, 3);
}

TEST(FindSubstring, MissingMatchResetsOutputPosition) {
    int position = 42;
    EXPECT_FALSE(str_find_substr("hello world", "xyz", position));
    EXPECT_EQ(position, -1);
}

TEST(FindSubstring, NeedleLongerThanTextIsNotFound) {
    int position = 42;
    EXPECT_FALSE(str_find_substr("cat", "catch", position));
    EXPECT_EQ(position, -1);
}

TEST(FindSubstring, EmptyAndNullInputsAreNotFound) {
    int position = 42;
    EXPECT_FALSE(str_find_substr("hello", "", position));
    EXPECT_EQ(position, -1);
    EXPECT_FALSE(str_find_substr(nullptr, "he", position));
    EXPECT_EQ(position, -1);
    EXPECT_FALSE(str_find_substr("hello", nullptr, position));
    EXPECT_EQ(position, -1);
}
