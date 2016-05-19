#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>
#include "format.h"

using namespace std;

namespace Format {

    int formatIndex;

    void getFlag(formatType *prototype, string const &format) {
        while (true) {
            switch (format[formatIndex]) {
                case '-':
                    prototype->negative = 1;
                    formatIndex++;
                    break;
                case '+':
                    prototype->positive = 1;
                    formatIndex++;
                    break;
                case ' ':
                    prototype->space = 1;
                    formatIndex++;
                    break;
                case '#':
                    prototype->sharp = 1;
                    formatIndex++;
                    break;
                case '0':
                    prototype->zero = 1;
                    formatIndex++;
                    break;
                default:
                    return;
            }
        }
    }

    int getNumber(string const &format) {
        int answer = 0; //(!) (!) (!) (!)
        if (format[formatIndex] == '*') {
            formatIndex++;
            return -42;
        }

        while (isdigit(format[formatIndex])) {
            answer = answer * 10 + (format[formatIndex] - '0');
            formatIndex++;
        }
        return answer;
    }

    int getPrecision(string const &format) {
        if (format[formatIndex] != '.') {
            return -1;
        }
        formatIndex++;
        return getNumber(format);
    }

    formatLength getLength(string const &format) {
        if (format[formatIndex] == 'h' && format[formatIndex + 1] == 'h') {
            formatIndex += 2;
            return hh;
        }
        if (format[formatIndex] == 'l' && format[formatIndex + 1] == 'l') {
            formatIndex += 2;
            return ll;
        }
        switch (format[formatIndex]) {
            case 'l':
                formatIndex++;
                return l;
            case 'h':
                formatIndex++;
                return h;
            case 'j':
                formatIndex++;
                return j;
            case 'z':
                formatIndex++;
                return z;
            case 't':
                formatIndex++;
                return t;
            case 'L':
                formatIndex++;
                return L;
            default:
                return lengthNull;
        }
    }

    formatSpecifier getSpecifier(string const &format) {
        switch (format[formatIndex]) {
            case 'd':
                formatIndex++;
                return d;
            case 'i':
                formatIndex++;
                return i;
            case 'u':
                formatIndex++;
                return u;
            case 'o':
                formatIndex++;
                return o;
            case 'x':
                formatIndex++;
                return x;
            case 'X':
                formatIndex++;
                return X;
            case 'f':
                formatIndex++;
                return f;
            case 'F':
                formatIndex++;
                return F;
            case 'e':
                formatIndex++;
                return e;
            case 'E':
                formatIndex++;
                return E;
            case 'g':
                formatIndex++;
                return g;
            case 'G':
                formatIndex++;
                return G;
            case 'a':
                formatIndex++;
                return a;
            case 'A':
                formatIndex++;
                return A;
            case 'c':
                formatIndex++;
                return c;
            case 's':
                formatIndex++;
                return s;
            case 'p':
                formatIndex++;
                return p;
            case 'n':
                formatIndex++;
                return n;
            default:
                throw invalid_argument("Error: wrong specifier");
        }
    }

    formatType readFormat(string const &format) {
        formatType answer;
        formatIndex++;
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
                            answer = "0" + answer;
                        }
/*                        for (int j = 0; j < stringNumber.length(); j++) {
                            if (stringNumber[j] == '+' || stringNumber[j] == '-') {
                                continue;
                            }
                            answer += stringNumber[j];
                        } */
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

    string toString(bool starMode, formatType prototype, string const &format) {
        string answer;
        while (true) { //prints symbols before next "%"
            if (format[formatIndex] == '%' && format[formatIndex + 1] == '%') {
                answer += "%";
                formatIndex += 2;
            }
            if (formatIndex == format.length()) {
                return answer;
            }
            answer += format[formatIndex];
            formatIndex++;
        }
    }
}
