#include "Calculator.h"

#include <iostream>

int main()
{
    double a = 10.0, b = 5.0;
    std::cout << a << " " << b << std::endl;

    Calculator calc;
    std::cout << "sum " << calc.sum(a, b) << std::endl;
    std::cout << "dif " << calc.dif(a, b) << std::endl;
    std::cout << "mul " << calc.mul(a, b) << std::endl;
    std::cout << "div " << calc.div(a, b) << std::endl;

    return 0;
}
