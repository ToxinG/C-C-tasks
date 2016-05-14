#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include "format.h"

using namespace std;

namespace Format {

    int index = 0;

    void getFlag(formatType *prototype, string const &format) {
        while (true) {
            switch (format[index]) {
                case '-':
                    prototype->negative = 1;
                    index++;
                    break;
                case '+':
                    prototype->positive = 1;
                    index++;
                    break;
                case ' ':
                    prototype->space = 1;
                    index++;
                    break;
                case '#':
                    prototype->sharp = 1;
                    index++;
                    break;
                case '0':
                    prototype->zero = 1;
                    index++;
                    break;
                default:
                    return;
            }
        }
    }

    int getNumber(string const &format) {
        int answer = 0; //(!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!) (!)
        if (format[index] == '*') {
            index++;
            return -42;
        }

        while (isdigit(format[index])) {
            answer = answer * 10 + (format[index] - '0');
            index++;
        }
        return answer;
    }

    int getPrecision(string const &format) {
        if (format[index] != '.') {
            return -1;
        }
        index++;
        return getNumber(format);
    }

    formatLength getLength(string const &format) {
        if (format[index] == 'h' && format[index + 1] == 'h') {
            index += 2;
            return hh;
        }
        if (format[index] == 'l' && format[index + 1] == 'l') {
            index += 2;
            return ll;
        }
        switch (format[index]) {
            case 'l':
                index++;
                return l;
            case 'h':
                index++;
                return h;
            case 'j':
                index++;
                return j;
            case 'z':
                index++;
                return z;
            case 't':
                index++;
                return t;
            case 'L':
                index++;
                return L;
            default:
                return lengthNull;
        }
    }

    formatSpecifier getSpecifier(string const &format) {
        switch (format[index]) {
            case 'd':
                index++;
                return d;
            case 'i':
                index++;
                return i;
            case 'u':
                index++;
                return u;
            case 'o':
                index++;
                return o;
            case 'x':
                index++;
                return x;
            case 'X':
                index++;
                return X;
            case 'f':
                index++;
                return f;
            case 'F':
                index++;
                return F;
            case 'e':
                index++;
                return e;
            case 'E':
                index++;
                return E;
            case 'g':
                index++;
                return g;
            case 'G':
                index++;
                return G;
            case 'a':
                index++;
                return a;
            case 'A':
                index++;
                return A;
            case 'c':
                index++;
                return c;
            case 's':
                index++;
                return s;
            case 'p':
                index++;
                return p;
            case 'n':
                index++;
                return n;
            default:
                throw invalid_argument("Error: wrong specifier");
        }
    }

    formatType readFormat(string const &format) {
        formatType answer;
        index++;
        getFlag(&answer, format);
        answer.width = getNumber(format);
        answer.precision = getPrecision(format);
        answer.length = getLength(format);
        answer.spec = getSpecifier(format);
        return answer;
    }

    string lvlOfString(formatType prototype, string stringNumber) {
        string answer;
        if (prototype.positive) {
            if (stringNumber[0] != '-') {
                stringNumber = "+" + stringNumber;
            }
        }

        int length = stringNumber.length();
        if (stringNumber[0] == '+' || stringNumber[0] == '-') {
            length--;
        }

        if (prototype.precision > length) {
            if (stringNumber[0] == '+' || stringNumber[0] == '-') {
                answer += stringNumber[0];
            }
            for (int j = 0; j < prototype.precision - length; j++) {
                answer = answer + "0";
            }
            for (int j = 0; j < stringNumber.length(); j++) {
                if (stringNumber[j] == '+' || stringNumber[j] == '-') {
                    continue;
                }
                answer += stringNumber[j];
            }
        } else {
            answer = stringNumber;
        }


        if (prototype.width > answer.length()) {
            if (prototype.negative) {
                for (; 0 < prototype.width - answer.length();) {
                    answer = answer + " ";
                }
            }
            if (prototype.zero) {
                if (!(prototype.spec == d || prototype.spec == i || prototype.spec == o ||
                      prototype.spec == u || prototype.spec == x || prototype.spec == X) || prototype.precision == -1) {
                    if (0 < prototype.width - answer.length()) {
                        if (stringNumber[0] == '+' || stringNumber[0] == '-') {
                            answer = stringNumber[0];
                        }
                        for (int j = 0; j < prototype.width - stringNumber.length(); j++) {
                            answer = answer + "0";
                        }
                        for (int j = 0; j < stringNumber.length(); j++) {
                            if (stringNumber[j] == '+' || stringNumber[j] == '-') {
                                continue;
                            }
                            answer += stringNumber[j];
                        }
                    }
                }
            }

            for (; 0 < prototype.width - answer.length();) {
                answer = " " + answer;
            }
        }

        if (prototype.space) {
            if (stringNumber[0] != '+' && stringNumber[0] != '-') {
                answer = " " + answer;
            }
        }
        return answer;
    }
}