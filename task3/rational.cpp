#include <iostream>
#include "rational.h"

using namespace std;

int rational::gcd(int a, int b) const {
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

rational::rational(int aNum) {
    num = aNum;
    denom = 1;
}
rational::rational(int aNum, int aDenom) {
    if (aDenom < 0) {
        aNum = -aNum;
        aDenom = -aDenom;
    }
    num = aNum / gcd(aNum, aDenom);
    denom = aDenom / gcd(aNum, aDenom);
}
int rational::getNum()const {
    return num;
}
int rational::getDenom()const {
    return denom;
}
rational rational::operator +(const rational & x) const {
    int resNum = num * x.denom + x.num * denom;
    int resDenom = denom * x.denom;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    rational res = rational(resNum / k, resDenom / k);
    return res;
}

rational rational::operator -(const rational & x) const {
    int resNum = num * x.denom - x.num * denom;
    int resDenom = denom * x.denom;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    rational res = rational(resNum / k, resDenom / k);
    return res;
}
rational rational::operator *(const rational & x) const {
    int resNum = num * x.num;
    int resDenom = denom * x.denom;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    rational res = rational(resNum / k, resDenom / k);
    return res;
}
rational rational::operator /(const rational & x) const {
    int resNum = num * x.denom;
    int resDenom = denom * x.num;
    if (resDenom < 0) {
        resNum = -resNum;
        resDenom = -resDenom;
    }
    int k = gcd(resNum, resDenom);
    rational res = rational(resNum / k, resDenom / k);
    return res;
}
