#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

class rational {
private:
    int num;
    int denom;
    int gcd (int a, int b) const;

public:
    rational(int);
    rational(int, int);
    int getNum()const;
    int getDenom()const;
    rational operator +(rational const &) const;
    rational operator -(rational const &) const;
    rational operator *(rational const &) const;
    rational operator /(rational const &) const;

};

#endif //RATIONAL_rATIONAL_H
