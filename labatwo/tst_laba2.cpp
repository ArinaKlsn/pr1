#include <QtTest>
#include <list>
#include "naturalnum.h"

class TestNaturalNumber : public QObject
{
    Q_OBJECT

private slots:
    void testGetFactors();
};

void TestNaturalNumber::testGetFactors()
{
    NaturalNumber numObj;
    std::list<int> factors = numObj.getFactors(12);
    QCOMPARE(factors.size(), 6); // 1, 2, 3, 4, 6, 12
    QVERIFY(factors == std::list<int>({1, 2, 3, 4, 6, 12}));

    factors = numObj.getFactors(7);
    QCOMPARE(factors.size(), 2); // 1, 7
    QVERIFY(factors == std::list<int>({1, 7}));

    factors = numObj.getFactors(1);
    QCOMPARE(factors.size(), 1); // 1
    QVERIFY(factors == std::list<int>({1}));
}

QTEST_APPLESS_MAIN(TestNaturalNumber)

#include "tst_laba2.moc"
