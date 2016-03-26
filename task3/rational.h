//
// Created by Антон on 05.03.2016.
//

#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

class Rational {
private:
    int num;
    int denom;

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
