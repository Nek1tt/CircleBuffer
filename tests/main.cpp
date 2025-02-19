#include <gtest/gtest.h>
#include "CircleBuffer.h" 


TEST(CircularBufferTest, ConstructorAndBasicMethods) {
    CircularBuffer buf1(5);
    EXPECT_EQ(buf1.capacity(), 5);
    EXPECT_EQ(buf1.size(), 0);

    CircularBuffer buf2(3, 'a');
    EXPECT_EQ(buf2.capacity(), 3);
    EXPECT_EQ(buf2.size(), 3);
    EXPECT_EQ(buf2.front(), 'a');
    EXPECT_EQ(buf2.back(), 'a');
}


TEST(CircularBufferTest, PushAndPopOperations) {
    CircularBuffer buf(5);
    buf.push_back('x');
    buf.push_back('y');
    buf.push_front('z');

    EXPECT_EQ(buf.front(), 'z');
    EXPECT_EQ(buf.back(), 'y');
    EXPECT_EQ(buf.size(), 3);

    buf.pop_back();
    EXPECT_EQ(buf.back(), 'x');
    EXPECT_EQ(buf.size(), 2);

    buf.pop_front();
    EXPECT_EQ(buf.front(), 'x');
    EXPECT_EQ(buf.size(), 1);
}


TEST(CircularBufferTest, ResizeAndSetCapacity) {
    CircularBuffer buf(5);
    buf.resize(10, 'b');

    EXPECT_EQ(buf.size(), 10);
    EXPECT_EQ(buf.capacity(), 10);

    buf.set_capacity(15);
    EXPECT_EQ(buf.capacity(), 15);
}


TEST(CircularBufferTest, InsertAndErase) {
    CircularBuffer buf(3, 'a');
    buf.insert(1, 'c');

    EXPECT_EQ(buf[1], 'c');

    buf.erase(1, 2);
    EXPECT_EQ(buf.size(), 2);
}


TEST(CircularBufferTest, AccessAndRotate) {
    CircularBuffer buf(10, 'b');
    buf.push_back('m');
    buf.push_back('n');

    EXPECT_EQ(buf[9], 'n');
    EXPECT_EQ(buf.at(8), 'm');

    buf.linearize();
    buf.rotate(2);

    EXPECT_EQ(buf.front(), 'b');
    EXPECT_EQ(buf.size(), 10);
}


TEST(CircularBufferTest, FullAndEmptyMethods) {
    CircularBuffer buf1(12);
    CircularBuffer buf2(2, 'a');

    EXPECT_FALSE(buf1.full());
    EXPECT_FALSE(buf2.empty());
}


TEST(CircularBufferTest, CopyAndAssignment) {
    CircularBuffer buf1(5);
    buf1.push_back('b');

    CircularBuffer buf3 = buf1;
    EXPECT_EQ(buf3[0], 'b');

    CircularBuffer buf2(2, 'a');
    CircularBuffer buf4(buf2);
    EXPECT_EQ(buf4[0], 'a');
}


TEST(CircularBufferTest, ClearMethod) {
    CircularBuffer buf1(5);
    CircularBuffer buf2(3, 'a');
    CircularBuffer buf3(buf1);
    CircularBuffer buf4(buf2);

    buf1.clear();
    buf2.clear();
    buf3.clear();
    buf4.clear();

    EXPECT_EQ(buf1.size(), 0);
    EXPECT_EQ(buf2.size(), 0);
    EXPECT_EQ(buf3.size(), 0);
    EXPECT_EQ(buf4.size(), 0);
}


int main(int argc, char** argv) {

    CircularBuffer circbuff1(5);
    CircularBuffer circbuff2 = circbuff2.func2(func1(std::move(circbuff1)));

    printf("\n");

    CircularBuffer circubuff3(3);
    CircularBuffer circbuff4 = circbuff4.func2(func1(circubuff3));

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
