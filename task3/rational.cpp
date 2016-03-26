#include <iostream>
#include "rational.h"

using namespace std;

int Rational::gcd(int a, int b) const {
    if (a < 0) {
        a *= -a;
    }
    while (a != 0 && b != 0)
        if (a < b)
            a = a % b;
        else
            b = b % a;
    return (a + b);
}

Rational::Rational(int aNum) {
    num = aNum;
    denom = 1;
}
Rational::Rational(int aNum, int aDenom) {
    if (aDenom < 0) {
        aNum = -aNum;
        aDenom = -aDenom;
    }
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
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    Rational res = Rational(resNum / k, resDenom / k);
    return res;
}

Rational Rational::operator -(const Rational & x) const {
    int resNum = num * x.denom - x.num * denom;
    int resDenom = denom * x.denom;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    Rational res = Rational(resNum / k, resDenom / k);
    return res;
}
Rational Rational::operator *(const Rational & x) const {
    int resNum = num * x.num;
    int resDenom = denom * x.denom;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    Rational res = Rational(resNum / k, resDenom / k);
    return res;
}
Rational Rational::operator /(const Rational & x) const {
    int resNum = num * x.denom;
    int resDenom = denom * x.num;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    Rational res = Rational(resNum / k, resDenom / k);
    return res;
}
