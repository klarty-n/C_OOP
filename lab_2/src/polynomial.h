#pragma once

class Polynomial {
public:
    Polynomial() noexcept;
    Polynomial(const double* coefficients, int degree);
    Polynomial(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;

    ~Polynomial();

    Polynomial& operator=(Polynomial other);

    void add(const Polynomial& other);
    void mul(const Polynomial& other);
    double evaluate(double x) const noexcept;
    double coefficient_sum() const noexcept;
    void print() const;

private:
    double* coeffs_;
    int degree_;

    void trim();
    void swap(Polynomial& other) noexcept;
};
