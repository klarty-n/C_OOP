#include "polynomial.h"
#include <utility>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <cmath>

constexpr double EPSILON = 1e-12;

Polynomial::Polynomial() noexcept : coeffs_(nullptr), degree_(-1) {}

Polynomial::Polynomial(const double* coeffs, int degree) : coeffs_(nullptr), degree_(-1) {
    if (degree < -1 || (degree >= 0 && coeffs == nullptr)) {
        throw std::invalid_argument("invalid coefficients");
    }

    while (degree >= 0 && std::abs(coeffs[degree]) <= EPSILON) {
        --degree;
    }
    if (degree == -1) {
        return; 
    }

    double* new_coeffs = new double[static_cast<std::size_t>(degree) + 1];

    for (int i = 0; i <= degree; ++i) {
        new_coeffs[i] = coeffs[i];
    }

    coeffs_ = new_coeffs;
    degree_ = degree;
}

Polynomial::Polynomial(const Polynomial& other) : Polynomial(other.coeffs_, other.degree_) {}

Polynomial::Polynomial(Polynomial&& other) noexcept : coeffs_(other.coeffs_), degree_(other.degree_) {
    other.coeffs_ = nullptr;
    other.degree_ = -1;    
}

Polynomial::~Polynomial() {
    delete[] coeffs_;
}

Polynomial& Polynomial::operator=(Polynomial other) {
    swap(other);
    return *this;
}

void Polynomial::swap(Polynomial& other) noexcept {
    std::swap(coeffs_, other.coeffs_);
    std::swap(degree_, other.degree_);
}

void Polynomial::trim() {
    int new_degree = degree_;

    while (new_degree >= 0 && std::abs(coeffs_[new_degree]) <= EPSILON) {
        --new_degree;
    }

    if (new_degree == degree_) {
        return;
    }

    if (new_degree == -1) {
        delete[] coeffs_;
        coeffs_ = nullptr;
        degree_ = -1;
        return;
    }

    const auto count = static_cast<std::size_t>(new_degree) + 1;
    double* new_coeffs = new double[count];

    for (int i = 0; i <= new_degree; ++i) {
        new_coeffs[i] = coeffs_[i];
    }

    delete[] coeffs_;
    coeffs_ = new_coeffs;
    degree_ = new_degree;
}

double Polynomial::coefficient_sum() const noexcept {
    double sum = 0.0;

    for (int i = 0; i <= degree_; ++i) {
        sum += coeffs_[i];
    }

    return sum;
}

void Polynomial::add(const Polynomial& other) {
    const int result_degree = degree_ > other.degree_ ? degree_ : other.degree_;

    if (result_degree == -1) {
        return;
    }

    Polynomial result;
    const auto count = static_cast<std::size_t>(result_degree) + 1;
    result.coeffs_ = new double[count]{};
    result.degree_ = result_degree;

    for (int i = 0; i <= degree_; ++i) {
        result.coeffs_[i] += coeffs_[i];
    }

    for (int i = 0; i <= other.degree_; ++i) {
        result.coeffs_[i] += other.coeffs_[i];
    }

    result.trim();
    swap(result);
}

void Polynomial::mul(const Polynomial& other) {
    Polynomial result;

    if (degree_ == -1 || other.degree_ == -1) {
        swap(result);
        return;
    }

    const int result_degree = degree_ + other.degree_;
    const auto count = static_cast<std::size_t>(result_degree) + 1;
    result.coeffs_ = new double[count]{};
    result.degree_ = result_degree;

    for (int i = 0; i <= degree_; ++i) {
        for (int j = 0; j <= other.degree_; ++j) {
            result.coeffs_[i + j] += coeffs_[i] * other.coeffs_[j];
        }
    }

    result.trim();
    swap(result);
}

double Polynomial::evaluate(double x) const noexcept {
    double value = 0.0;

    for (int i = degree_; i >= 0; --i) {
        value = value * x + coeffs_[i];
    }

    return value;
}

void Polynomial::print() const {
    bool firstSign = true;

    for (int i = degree_; i >= 0; --i) {
        const double coefficient = coeffs_[i];

        if (std::abs(coefficient) <= EPSILON) {
            continue;
        }

        const bool negative = coefficient < 0.0;
        const double withoutSign = negative ? -coefficient : coefficient;

        if (firstSign) {
            if (negative) {
                std::cout << '-';
            }
        } else {
            std::cout << (negative ? " - " : " + ");
        }

        if (i == 0 || withoutSign != 1.0) {
            std::cout << withoutSign;
        }

        if (i > 0) {
            std::cout << 'x';
            if (i > 1) {
                std::cout << '^' << i;
            }
        }

        firstSign = false;
    }

    if (firstSign) {
        std::cout << '0';
    }
}
