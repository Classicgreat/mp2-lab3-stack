#include "../include/calculator.h"
#include "../src/calculator.cpp"
#include <gtest/gtest.h>

#include <cmath>
#include <string>

class CalculatorTest : public ::testing::Test {
protected:
  Calculator calc;

  double eval(const std::string &expr) {
    calc.SetInfix(expr);
    return calc.CalcPostfix();
  }
};

// ---------------------------------------------------------------------------
// Арифметика
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, Addition) {
  EXPECT_DOUBLE_EQ(eval("2+3"), 5);
  EXPECT_DOUBLE_EQ(eval("0+0"), 0);
  EXPECT_DOUBLE_EQ(eval("123+456"), 579);
  EXPECT_DOUBLE_EQ(eval("1.5+2.25"), 3.75);
}

TEST_F(CalculatorTest, Subtraction) {
  EXPECT_DOUBLE_EQ(eval("10-4"), 6);
  EXPECT_DOUBLE_EQ(eval("4-10"), -6);
  EXPECT_DOUBLE_EQ(eval("10-2-3"), 5);
  EXPECT_DOUBLE_EQ(eval("10-2+3"), 11);
}

TEST_F(CalculatorTest, Multiplication) {
  EXPECT_DOUBLE_EQ(eval("6*7"), 42);
  EXPECT_DOUBLE_EQ(eval("2*3*4"), 24);
  EXPECT_DOUBLE_EQ(eval("1.5*2"), 3);
}

TEST_F(CalculatorTest, Division) {
  EXPECT_DOUBLE_EQ(eval("7/2"), 3.5);
  EXPECT_DOUBLE_EQ(eval("20/2/5"), 2);
  EXPECT_DOUBLE_EQ(eval("1/4"), 0.25);
}

TEST_F(CalculatorTest, Precedence) {
  EXPECT_DOUBLE_EQ(eval("2+3*4"), 14);
  EXPECT_DOUBLE_EQ(eval("2*3+4"), 10);
  EXPECT_DOUBLE_EQ(eval("2+3*4-5/5"), 13);
  EXPECT_DOUBLE_EQ(eval("2*3^2"), 18);
}

TEST_F(CalculatorTest, Power) {
  EXPECT_DOUBLE_EQ(eval("2^10"), 1024);
  EXPECT_DOUBLE_EQ(eval("9^0.5"), 3);
  EXPECT_DOUBLE_EQ(eval("2^0.5"), std::sqrt(2.0));
  EXPECT_DOUBLE_EQ(eval("2^3^2"), 64);
}

// ---------------------------------------------------------------------------
// Скобки
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, Parentheses) {
  EXPECT_DOUBLE_EQ(eval("(2+3)*4"), 20);
  EXPECT_DOUBLE_EQ(eval("2*(3+4)"), 14);
  EXPECT_DOUBLE_EQ(eval("((2))"), 2);
  EXPECT_DOUBLE_EQ(eval("((2+3)*(4-1))"), 15);
  EXPECT_DOUBLE_EQ(eval("(1+2)*(3+4)*(5-2)"), 63);
  EXPECT_DOUBLE_EQ(eval("(((1)))"), 1);
}

// ---------------------------------------------------------------------------
// Унарные операторы
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, UnaryMinus) {
  EXPECT_DOUBLE_EQ(eval("-5"), -5);
  EXPECT_DOUBLE_EQ(eval("-5+3"), -2);
  EXPECT_DOUBLE_EQ(eval("-5*3"), -15);
  EXPECT_DOUBLE_EQ(eval("-(2+3)"), -5);
  EXPECT_DOUBLE_EQ(eval("-(2+3)*2"), -10);
  EXPECT_DOUBLE_EQ(eval("2*(-3)"), -6);
  EXPECT_DOUBLE_EQ(eval("2*(-(-3))"), 6);
}

TEST_F(CalculatorTest, UnaryPlus) {
  EXPECT_DOUBLE_EQ(eval("+5"), 5);
  EXPECT_DOUBLE_EQ(eval("+5-3"), 2);
  EXPECT_DOUBLE_EQ(eval("+(2+3)"), 5);
}

// ---------------------------------------------------------------------------
// Форматы чисел и пробелы
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, Whitespace) {
  EXPECT_DOUBLE_EQ(eval("  2 + 3  "), 5);
  EXPECT_DOUBLE_EQ(eval(" ( 1 + 2 ) * 3 "), 9);
  EXPECT_DOUBLE_EQ(eval("2  +  3"), 5);
}

TEST_F(CalculatorTest, Decimals) {
  EXPECT_DOUBLE_EQ(eval("3.14*2"), 6.28);
  EXPECT_DOUBLE_EQ(eval(".5+.5"), 1);
  EXPECT_DOUBLE_EQ(eval("1."), 1);
  EXPECT_DOUBLE_EQ(eval("1.5*2.0"), 3);
}

// ---------------------------------------------------------------------------
// Сложные выражения
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, ComplexExpressions) {
  EXPECT_DOUBLE_EQ(eval("(1+2*3-4)/(1+1)+2^3"), (1 + 2 * 3 - 4) / 2.0 + 8);
  EXPECT_DOUBLE_EQ(eval("1+2*(3+4*(5-6))"), -1);
  EXPECT_DOUBLE_EQ(eval("1000000*1000000"), 1e12);
  EXPECT_NEAR(eval("0.001+0.002"), 0.003, 1e-12);
}

// ---------------------------------------------------------------------------
// Деление на ноль
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, DivisionByZeroThrows) {
  EXPECT_ANY_THROW(eval("1/0"));
  EXPECT_ANY_THROW(eval("5/(3-3)"));
  EXPECT_ANY_THROW(eval("0/0"));
}

// ---------------------------------------------------------------------------
// Ошибки разбора / структуры
// ---------------------------------------------------------------------------
TEST_F(CalculatorTest, InvalidCharacters) {
  EXPECT_ANY_THROW(eval("abc"));
  EXPECT_ANY_THROW(eval("2&3"));
  EXPECT_ANY_THROW(eval("2#3"));
}

TEST_F(CalculatorTest, InvalidNumbers) {
  EXPECT_ANY_THROW(eval("."));
  EXPECT_ANY_THROW(eval("+."));
}

TEST_F(CalculatorTest, StructuralErrors) {
  EXPECT_ANY_THROW(eval("2+"));
  EXPECT_ANY_THROW(eval("*.5"));
  EXPECT_ANY_THROW(eval("2 3"));
  EXPECT_ANY_THROW(eval("1..2"));
  EXPECT_ANY_THROW(eval("(2+3"));
  EXPECT_ANY_THROW(eval("2+3)"));
  EXPECT_ANY_THROW(eval(""));
}

TEST(CalculatorWithoutSetInfix, CalcPostfixThrows) {
  Calculator c;
  EXPECT_ANY_THROW(c.CalcPostfix());
}

TEST(CalculatorRecovery, WorksAfterException) {
  Calculator c;
  EXPECT_ANY_THROW(c.SetInfix("2&3"));
  c.SetInfix("1+1");
  EXPECT_DOUBLE_EQ(c.CalcPostfix(), 2);
}

// ---------------------------------------------------------------------------
// Повторное использование
// ---------------------------------------------------------------------------
TEST(CalculatorReuse, MultipleExpressions) {
  Calculator c;

  c.SetInfix("2+2");
  EXPECT_DOUBLE_EQ(c.CalcPostfix(), 4);
  EXPECT_DOUBLE_EQ(c.CalcPostfix(), 4);

  c.SetInfix("3*3");
  EXPECT_DOUBLE_EQ(c.CalcPostfix(), 9);

  c.SetInfix("10-1");
  EXPECT_DOUBLE_EQ(c.CalcPostfix(), 9);
}

// ---------------------------------------------------------------------------
// Token::Prior
// ---------------------------------------------------------------------------
namespace {
Token MakeToken(TokenType type, const std::string &data) {
  Token t{};
  t.type = type;
  t.data = data;
  return t;
}
} // namespace

TEST(TokenPriority, Operations) {
  using TT = TokenType;
  EXPECT_EQ(MakeToken(TT::OPERATION, "+").Prior(), 1);
  EXPECT_EQ(MakeToken(TT::OPERATION, "-").Prior(), 1);
  EXPECT_EQ(MakeToken(TT::OPERATION, "*").Prior(), 2);
  EXPECT_EQ(MakeToken(TT::OPERATION, "/").Prior(), 2);
  EXPECT_EQ(MakeToken(TT::OPERATION, "^").Prior(), 3);
  EXPECT_EQ(MakeToken(TT::OPERATION, "u-").Prior(), 3);
}

TEST(TokenPriority, Brackets) {
  using TT = TokenType;
  EXPECT_EQ(MakeToken(TT::OPEN_BRACKET, "(").Prior(), 0);
  EXPECT_EQ(MakeToken(TT::CLOSE_BRACKET, ")").Prior(), 0);
}
