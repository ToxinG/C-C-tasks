#include <iostream>
#include "rational.h"

using namespace std;

int Rational::gcd(int a, int b) const {
    int sign = 1;
    if (a < 0) {
        sign = -1;
        a *= -1;
    }
    while (a != 0 && b != 0)
        if (a < b)
            a = a % b;
        else
            b = b % a;
    a *= sign;
    return (a + b);
}

Rational::Rational(int aNum) {
    num = aNum;
    denom = 1;
}
Rational::Rational(int aNum, int aDenom) {
    num = aNum / gcd(aNum, aDenom);
    denom = aDenom / gcd(aNum, aDenom);
}
int Rational::getNum()const {
    return num;
}
int Rational::getDenom()const {
    return denom;
}
Rational Rational::operator +(const Rational & x) const {
    int resNum = num * x.denom + x.num * denom;
    int resDenom = denom * x.denom;
    if ((resNum >= 0 && resDenom < 0) || (resNum < 0 && resDenom < 0)) {
        resNum *= -1;
        resDenom *= -1;
    }
    Rational res = Rational(resNum / gcd(resNum, resDenom), resDenom / gcd(resNum, resDenom));
    return res;
}

Rational Rational::operator -(const Rational & x) const {
    int resNum = num * x.denom - x.num * denom;
    int resDenom = denom * x.denom;
    if ((resNum >= 0 && resDenom < 0) || (resNum < 0 && resDenom < 0)) {
        resNum *= -1;
        resDenom *= -1;
    }
    Rational res = Rational(resNum / gcd(resNum, resDenom), resDenom / gcd(resNum, resDenom));
    return res;
}
Rational Rational::operator *(const Rational & x) const {
    int resNum = num * x.num;
    int resDenom = denom * x.denom;
    if ((resNum >= 0 && resDenom < 0) || (resNum < 0 && resDenom < 0)) {
        resNum *= -1;
        resDenom *= -1;
    }
    Rational res = Rational(resNum / gcd(resNum, resDenom), resDenom / gcd(resNum, resDenom));
    return res;
}
Rational Rational::operator /(const Rational & x) const {
    int resNum = num * x.denom;
    int resDenom = denom * x.num;
    if ((resNum >= 0 && resDenom < 0) || (resNum < 0 && resDenom < 0)) {
        resNum *= -1;
        resDenom *= -1;
    }
    Rational res = Rational(resNum / gcd(resNum, resDenom), resDenom / gcd(resNum, resDenom));
    return res;
}
