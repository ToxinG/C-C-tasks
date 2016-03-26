#include <iostream>
#include "rational.h"

using namespace std;

int gcd(int a, int b) {
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
    num = aNum / gcd(aNum, aDenom);
    denom = aDenom / gcd(aNum, aDenom);
}
int Rational::getNum()const {
    return num;
}
int Rational::getDenom()const {
    return denom;
}
Rational Rational::operator +(Rational const & x) const {
    int resNum = num * x.denom + x.num * denom;
    int resDenom = denom * x.denom;
    resNum = resNum / gcd(resNum, resDenom);
    resDenom = resDenom / gcd(resNum, resDenom);
    return Rational(resNum, resDenom);
}

Rational Rational::operator -(Rational const & x) const {
    int resNum = num * x.denom - x.num * denom;
    int resDenom = denom * x.denom;
    resNum = resNum / gcd(resNum, resDenom);
    resDenom = resDenom / gcd(resNum, resDenom);
    return Rational(resNum, resDenom);
}
Rational Rational::operator *(Rational const & x) const {
    return Rational(num * x.num / gcd(num * x.num, denom * x.denom),
                    denom * x.denom / gcd(num * x.num, denom * x.denom));
}
Rational Rational::operator /(Rational const & x) const {
    return Rational(num * x.denom / gcd(num * x.denom, denom * x.num),
                    denom * x.num / gcd(num * x.denom, denom * x.num));
}

int main() {

    return 0;
}