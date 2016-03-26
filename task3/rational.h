#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

class Rational {
private:
    int num;
    int denom;
    int gcd (int a, int b) const;

public:
    Rational(int);
    Rational(int, int);
    int getNum()const;
    int getDenom()const;
    Rational operator +(Rational const &) const;
    Rational operator -(Rational const &) const;
    Rational operator *(Rational const &) const;
    Rational operator /(Rational const &) const;

};

#endif //RATIONAL_RATIONAL_H
