#ifndef NATURALNUMBER_H
#define NATURALNUMBER_H

#include <list>

class NaturalNumber
{
public:
    NaturalNumber();
    std::list<int> getFactors(int num);
};

#endif // NATURALNUMBER_H
