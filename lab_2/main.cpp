#include "polynomial.h"
#include <iostream>

int main() {
    double p_coefficients[] = {1.0, 2.0};
    double q_coefficients[] = {0.0, 1.0, 1.0};

    Polynomial p(p_coefficients, 1);
    Polynomial q(q_coefficients, 2);

    std::cout << "P(x) = ";
    p.print();
    std::cout << '\n';

    std::cout << "Q(x) = ";
    q.print();
    std::cout << '\n';

    Polynomial sum(p);
    sum.add(q);
    std::cout << "P(x) + Q(x) = ";
    sum.print();
    std::cout << '\n';

    Polynomial product(p);
    product.mul(q);
    std::cout << "P(x) * Q(x) = ";
    product.print();
    std::cout << '\n';

    std::cout << "(P + Q)(2) = " << sum.evaluate(2.0) << '\n';
    std::cout << "Sum of P coefficients = " << p.coefficient_sum() << '\n';

    return 0;
}