#include <QtTest>

#include "../app/Calculator.h"

class tst_Calculator : public QObject
{
    Q_OBJECT

public:
    tst_Calculator();
    ~tst_Calculator();

private slots:
    void testSum();
    void testDif();
   void testMul();
    void testDiv();

};

tst_Calculator::tst_Calculator()
{

}

tst_Calculator::~tst_Calculator()
{

}

void tst_Calculator::testSum()
{
    Calculator calc;
    QCOMPARE(calc.sum(2.0, 3.0), 5.0);
    QCOMPARE(calc.sum(-2.0, 3.0), 1.0);
    QCOMPARE(calc.sum(2.0, -3.0), -1.0);
    QCOMPARE(calc.sum(-2.0, -3.0), -5.0);
    QCOMPARE(calc.sum(0.0, 3.0), 3.0);
    QCOMPARE(calc.sum(2.0, 0.0), 2.0);
    QCOMPARE(calc.sum(0.0, 0.0), 0.0);
}

void tst_Calculator::testDif()
{
    Calculator calc;
    QCOMPARE(calc.dif(2.0, 3.0), -1.0);
    QCOMPARE(calc.dif(-2.0, 3.0), -5.0);
    QCOMPARE(calc.dif(2.0, -3.0), 5.0);
    QCOMPARE(calc.dif(-2.0, -3.0), 1.0);
    QCOMPARE(calc.dif(0.0, 3.0), -3.0);
    QCOMPARE(calc.dif(2.0, 0.0), 2.0);
    QCOMPARE(calc.dif(0.0, 0.0), 0.0);
}

void tst_Calculator::testMul()
{
    Calculator calc;
    QCOMPARE(calc.mul(2.0, 3.0), 6.0);
    QCOMPARE(calc.mul(-2.0, 3.0), -6.0);
    QCOMPARE(calc.mul(2.0, -3.0), -6.0);
    QCOMPARE(calc.mul(-2.0, -3.0), 6.0);
    QCOMPARE(calc.mul(0.0, 3.0), 0.0);
    QCOMPARE(calc.mul(2.0, 0.0), 0.0);
    QCOMPARE(calc.mul(0.0, 0.0), 0.0);
}

void tst_Calculator::testDiv()
{
    Calculator calc;
    QVERIFY((calc.div(2.0, 3.0) - 0.666) < 1.e-3);
    QVERIFY((calc.div(-2.0, 3.0) + 0.666) < 1.e-3);
    QVERIFY((calc.div(2.0, -3.0) + 0.666) < 1.e-3);
    QVERIFY((calc.div(-2.0, -3.0) - 0.666) < 1.e-3);
    QCOMPARE(calc.div(0.0, 3.0), 0.0);
    QCOMPARE(calc.div(2.0, 0.0), qInf());
    QCOMPARE(calc.div(0.0, 0.0), qQNaN());
}

QTEST_APPLESS_MAIN(tst_Calculator)

#include "tst_calculator.moc"
