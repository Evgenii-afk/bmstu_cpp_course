#include "bmstu_optional.h"
#include <gtest/gtest.h>
#include <string>

// Тестовый класс для проверки деструкторов
class TestObject {
public:
    static int constructor_count;
    static int destructor_count;
    static int copy_count;
    static int move_count;
    
    int value;
    
    TestObject(int v = 0) : value(v) { constructor_count++; }
    TestObject(const TestObject& other) : value(other.value) { copy_count++; }
    TestObject(TestObject&& other) : value(other.value) { move_count++; other.value = -1; }
    
    ~TestObject() { destructor_count++; }
    
    TestObject& operator=(const TestObject& other) { value = other.value; return *this; }
    TestObject& operator=(TestObject&& other) { value = other.value; other.value = -1; return *this; }
    
    static void reset_counters() {
        constructor_count = destructor_count = copy_count = move_count = 0;
    }
};

int TestObject::constructor_count = 0;
int TestObject::destructor_count = 0;
int TestObject::copy_count = 0;
int TestObject::move_count = 0;

TEST(OptionalTest, DefaultConstructor) {
    bmstu::optional<int> opt;
    EXPECT_FALSE(opt.has_value());
}

TEST(OptionalTest, ValueConstructor) {
    bmstu::optional<int> opt(42);
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), 42);
}

TEST(OptionalTest, StringValue) {
    bmstu::optional<std::string> opt("hello");
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), "hello");
}

TEST(OptionalTest, CopyConstructor) {
    bmstu::optional<int> opt1(100);
    bmstu::optional<int> opt2(opt1);
    
    EXPECT_TRUE(opt1.has_value());
    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt1.value(), 100);
    EXPECT_EQ(opt2.value(), 100);
}

TEST(OptionalTest, MoveConstructor) {
    bmstu::optional<std::string> opt1("test");
    bmstu::optional<std::string> opt2(std::move(opt1));
    
    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), "test");
}

TEST(OptionalTest, ValueAccess) {
    bmstu::optional<double> opt(3.14);
    EXPECT_DOUBLE_EQ(opt.value(), 3.14);
    EXPECT_DOUBLE_EQ(*opt, 3.14);
}

TEST(OptionalTest, BadAccessThrow) {
    bmstu::optional<int> opt;
    EXPECT_THROW(opt.value(), bmstu::bad_optional_access);
    EXPECT_THROW(*opt, bmstu::bad_optional_access);
}

TEST(OptionalTest, Reset) {
    bmstu::optional<int> opt(55);
    EXPECT_TRUE(opt.has_value());
    
    opt.reset();
    EXPECT_FALSE(opt.has_value());
}

TEST(OptionalTest, Emplace) {
    bmstu::optional<std::string> opt;
    EXPECT_FALSE(opt.has_value());
    
    opt.emplace("emplace_test");
    EXPECT_TRUE(opt.has_value());
    EXPECT_EQ(opt.value(), "emplace_test");
    
    opt.emplace("new_value");
    EXPECT_EQ(opt.value(), "new_value");
}

TEST(OptionalTest, AssignmentOperator) {
    bmstu::optional<int> opt1(100);
    bmstu::optional<int> opt2;
    
    opt2 = opt1;
    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), 100);
}

TEST(OptionalTest, MoveAssignment) {
    bmstu::optional<std::string> opt1("test");
    bmstu::optional<std::string> opt2;
    
    opt2 = std::move(opt1);
    EXPECT_TRUE(opt2.has_value());
    EXPECT_EQ(opt2.value(), "test");
}

TEST(OptionalTest, BoolOperator) {
    bmstu::optional<int> opt1(42);
    bmstu::optional<int> opt2;
    
    EXPECT_TRUE(static_cast<bool>(opt1));
    EXPECT_FALSE(static_cast<bool>(opt2));
}

TEST(OptionalTest, ValueOr) {
    bmstu::optional<int> opt1(100);
    bmstu::optional<int> opt2;
    
    EXPECT_EQ(opt1.value_or(999), 100);
    EXPECT_EQ(opt2.value_or(999), 999);
}

TEST(OptionalTest, ArrowOperator) {
    struct Point {
        int x, y;
        int sum() const { return x + y; }
    };
    
    bmstu::optional<Point> opt(Point{3, 4});
    EXPECT_EQ(opt->x, 3);
    EXPECT_EQ(opt->y, 4);
    EXPECT_EQ(opt->sum(), 7);
}

TEST(OptionalTest, ConstAccess) {
    const bmstu::optional<int> opt(777);
    EXPECT_EQ(opt.value(), 777);
    EXPECT_EQ(*opt, 777);
    EXPECT_TRUE(opt.has_value());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}