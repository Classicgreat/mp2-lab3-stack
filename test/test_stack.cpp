#include "../include/stack.h"
#include <gtest/gtest.h>

TEST(StackTest, CanCreateEmptyStack) {
  EXPECT_NO_THROW(Stack<int> st);
  Stack<int> st;
  EXPECT_TRUE(st.IsEmpty());
}

TEST(StackTest, CanCreateWithSize) { EXPECT_NO_THROW(Stack<int> st(30)); }

TEST(StackTest, CantCreateWithNegSize) { EXPECT_ANY_THROW(Stack<int> st(-1)); }

TEST(StackTest, PushingObj) {
  Stack<int> st(5);

  st.push(1);

  EXPECT_FALSE(st.IsEmpty());
}

TEST(StackTest, PopingObj) {
  Stack<int> st;

  st.push(1);
  EXPECT_FALSE(st.IsEmpty());

  st.pop();
  EXPECT_TRUE(st.IsEmpty());
}

TEST(StackTest, CleaningStack) {
  Stack<int> st;

  EXPECT_TRUE(st.IsEmpty());

  st.push(1);

  EXPECT_FALSE(st.IsEmpty());

  st.clear();

  EXPECT_TRUE(st.IsEmpty());
}

TEST(StackTest, CantPopEmptyStack) {
  Stack<int> st;

  ASSERT_ANY_THROW(st.pop());
}

TEST(StackTest, CantPushThroughLimit) {
  Stack<int> st(3);

  st.push(1);
  st.push(2);
  st.push(3);

  EXPECT_TRUE(st.IsFull());
  ASSERT_ANY_THROW(st.push(4));
}

TEST(StackTest, CopyConstructor) {
  Stack<int> st1(5);
  st1.push(1);
  st1.push(2);
  st1.push(3);

  Stack<int> st2(st1);
  EXPECT_FALSE(st2.IsEmpty());

  EXPECT_EQ(st1, st2);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(st1.pop(), st2.pop());
  }
  EXPECT_TRUE(st2.IsEmpty());
}

TEST(StackTest, EqOperator) {
  Stack<int> st1(5), st2;
  st1.push(1);
  st1.push(2);
  st1.push(3);

  st2 = st1;
  EXPECT_FALSE(st2.IsEmpty());

  EXPECT_EQ(st1, st2);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(st1.pop(), st2.pop());
  }
  EXPECT_TRUE(st2.IsEmpty());
}
