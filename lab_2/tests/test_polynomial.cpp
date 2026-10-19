#include "polynomial.h"

#include <gtest/gtest.h>

#include <iostream>
#include <stdexcept>
#include <utility>

TEST(PolynomialConstruction, DefaultIsZero) {
    Polynomial p;
    EXPECT_DOUBLE_EQ(p.evaluate(7.0), 0.0);
    EXPECT_DOUBLE_EQ(p.coefficient_sum(), 0.0);
}

TEST(PolynomialConstruction, CopiesInputCoefficients) {
    double coefficients[] = {1.0, 2.0, 3.0};
    Polynomial p(coefficients, 2);
    coefficients[0] = 100.0;
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 17.0);
}

TEST(PolynomialConstruction, TrimsTrailingZeros) {
    double coefficients[] = {1.0, 2.0, 0.0, 0.0};
    Polynomial p(coefficients, 3);
    testing::internal::CaptureStdout();
    p.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "2x + 1");
}

TEST(PolynomialConstruction, AllZeroCoefficientsMakeZero) {
    double coefficients[] = {0.0, 0.0};
    Polynomial p(coefficients, 1);
    EXPECT_DOUBLE_EQ(p.evaluate(5.0), 0.0);
    testing::internal::CaptureStdout();
    p.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0");
}

TEST(PolynomialConstruction, RejectsDegreeBelowMinusOne) {
    EXPECT_THROW(Polynomial(nullptr, -2), std::invalid_argument);
}

TEST(PolynomialConstruction, RejectsNullCoefficientsForNonzeroDegree) {
    EXPECT_THROW(Polynomial(nullptr, 0), std::invalid_argument);
}

TEST(PolynomialConstruction, AllowsNullCoefficientsForZeroPolynomial) {
    Polynomial p(nullptr, -1);
    EXPECT_DOUBLE_EQ(p.evaluate(3.0), 0.0);
}

TEST(PolynomialConstruction, OneCoefficientMakesConstantPolynomial) {
    double coefficients[] = {-3.0};
    Polynomial p(coefficients, 0);
    EXPECT_DOUBLE_EQ(p.evaluate(-10.0), -3.0);
    EXPECT_DOUBLE_EQ(p.coefficient_sum(), -3.0);
}

TEST(PolynomialConstruction, TreatsTinyConstantAsZero) {
    double coefficients[] = {1e-13};
    Polynomial p(coefficients, 0);
    EXPECT_DOUBLE_EQ(p.evaluate(4.0), 0.0);
}

TEST(PolynomialConstruction, PreservesCoefficientAboveTolerance) {
    double coefficients[] = {1e-10};
    Polynomial p(coefficients, 0);
    EXPECT_DOUBLE_EQ(p.evaluate(4.0), 1e-10);
}

TEST(PolynomialCopyMove, CopyConstructorIsIndependent) {
    double coefficients[] = {1.0, 2.0};
    Polynomial source(coefficients, 1);
    Polynomial copy(source);
    source.add(source);
    EXPECT_DOUBLE_EQ(copy.evaluate(2.0), 5.0);
    EXPECT_DOUBLE_EQ(source.evaluate(2.0), 10.0);
}

TEST(PolynomialCopyMove, CopiesZeroPolynomial) {
    Polynomial source;
    Polynomial copy(source);
    EXPECT_DOUBLE_EQ(copy.evaluate(2.0), 0.0);
}

TEST(PolynomialCopyMove, MoveConstructorEmptiesSource) {
    double coefficients[] = {1.0, 2.0};
    Polynomial source(coefficients, 1);
    Polynomial destination(std::move(source));
    EXPECT_DOUBLE_EQ(destination.evaluate(2.0), 5.0);
    EXPECT_DOUBLE_EQ(source.evaluate(2.0), 0.0);
}

TEST(PolynomialCopyMove, CopyAssignmentIsIndependent) {
    double left_coefficients[] = {9.0};
    double right_coefficients[] = {1.0, 2.0};
    Polynomial left(left_coefficients, 0);
    Polynomial right(right_coefficients, 1);
    left = right;
    right.add(right);
    EXPECT_DOUBLE_EQ(left.evaluate(2.0), 5.0);
    EXPECT_DOUBLE_EQ(right.evaluate(2.0), 10.0);
}

TEST(PolynomialCopyMove, MoveAssignmentEmptiesSource) {
    double left_coefficients[] = {9.0};
    double right_coefficients[] = {1.0, 2.0};
    Polynomial left(left_coefficients, 0);
    Polynomial right(right_coefficients, 1);
    left = std::move(right);
    EXPECT_DOUBLE_EQ(left.evaluate(2.0), 5.0);
    EXPECT_DOUBLE_EQ(right.evaluate(2.0), 0.0);
}

TEST(PolynomialCopyMove, SelfAssignmentKeepsValue) {
    double coefficients[] = {1.0, 2.0};
    Polynomial p(coefficients, 1);
    p = p;
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 5.0);
}

TEST(PolynomialAddition, AddsDifferentDegrees) {
    double left_coefficients[] = {1.0, 2.0};
    double right_coefficients[] = {0.0, 1.0, 1.0};
    Polynomial left(left_coefficients, 1);
    Polynomial right(right_coefficients, 2);
    left.add(right);
    EXPECT_DOUBLE_EQ(left.evaluate(2.0), 11.0);
    EXPECT_DOUBLE_EQ(right.evaluate(2.0), 6.0);
}

TEST(PolynomialAddition, AddingZeroKeepsValue) {
    double coefficients[] = {1.0, 2.0};
    Polynomial p(coefficients, 1);
    Polynomial zero;
    p.add(zero);
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 5.0);
    zero.add(p);
    EXPECT_DOUBLE_EQ(zero.evaluate(2.0), 5.0);
}

TEST(PolynomialAddition, OppositesProduceZero) {
    double left_coefficients[] = {1.0, 2.0};
    double right_coefficients[] = {-1.0, -2.0};
    Polynomial left(left_coefficients, 1);
    Polynomial right(right_coefficients, 1);
    left.add(right);
    EXPECT_DOUBLE_EQ(left.coefficient_sum(), 0.0);
    testing::internal::CaptureStdout();
    left.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "0");
}

TEST(PolynomialAddition, TrimsFloatingPointResidual) {
    double first_coefficients[] = {0.1};
    double second_coefficients[] = {0.2};
    double third_coefficients[] = {-0.3};
    Polynomial first(first_coefficients, 0);
    Polynomial second(second_coefficients, 0);
    Polynomial third(third_coefficients, 0);
    first.add(second);
    first.add(third);
    EXPECT_DOUBLE_EQ(first.evaluate(5.0), 0.0);
}

TEST(PolynomialMultiplication, MultipliesDifferentDegrees) {
    double left_coefficients[] = {1.0, 2.0};
    double right_coefficients[] = {0.0, 1.0, 1.0};
    Polynomial left(left_coefficients, 1);
    Polynomial right(right_coefficients, 2);
    left.mul(right);
    testing::internal::CaptureStdout();
    left.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "2x^3 + 3x^2 + x");
    EXPECT_DOUBLE_EQ(left.evaluate(2.0), 30.0);
    EXPECT_DOUBLE_EQ(right.evaluate(2.0), 6.0);
}

TEST(PolynomialMultiplication, MultiplicationByZeroProducesZero) {
    double coefficients[] = {1.0, 2.0};
    Polynomial p(coefficients, 1);
    Polynomial zero;
    p.mul(zero);
    EXPECT_DOUBLE_EQ(p.evaluate(2.0), 0.0);
    EXPECT_DOUBLE_EQ(p.coefficient_sum(), 0.0);
}

TEST(PolynomialMultiplication, CanMultiplyByItself) {
    double coefficients[] = {1.0, 1.0};
    Polynomial p(coefficients, 1);
    p.mul(p);
    testing::internal::CaptureStdout();
    p.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "x^2 + 2x + 1");
}

TEST(PolynomialEvaluation, HornerWorksAtNegativeArgument) {
    double coefficients[] = {1.0, 2.0, 3.0};
    Polynomial p(coefficients, 2);
    EXPECT_DOUBLE_EQ(p.evaluate(-2.0), 9.0);
}

TEST(PolynomialVariant13, SumsAllCoefficients) {
    double coefficients[] = {1.0, 2.0, 3.0};
    Polynomial p(coefficients, 2);
    EXPECT_DOUBLE_EQ(p.coefficient_sum(), 6.0);
    EXPECT_DOUBLE_EQ(p.coefficient_sum(), p.evaluate(1.0));
}

TEST(PolynomialVariant13, SumIncludesNegativeCoefficients) {
    double coefficients[] = {-3.0, 2.0, 4.0};
    Polynomial p(coefficients, 2);
    EXPECT_DOUBLE_EQ(p.coefficient_sum(), 3.0);
}

TEST(PolynomialPrinting, FormatsSignsAndPowers) {
    double coefficients[] = {-1.0, 1.0, -2.0};
    Polynomial p(coefficients, 2);
    testing::internal::CaptureStdout();
    p.print();
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "-2x^2 + x - 1");
}
