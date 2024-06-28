#include "naturalnum.h"

NaturalNumber::NaturalNumber() {}

std::list<int> NaturalNumber::getFactors(int num) {
    std::list<int> factors;
    for (int i = 1; i <= num; ++i) {
        if (num % i == 0) {
            factors.push_back(i);
        }
    }
    return factors;
}
