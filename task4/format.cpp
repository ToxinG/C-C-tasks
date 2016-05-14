#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include "format.h"

using namespace std;

int index = 0;

enum formatLength {
    h,
    hh,
    j,
    l,
    lengthNull,
    ll,
    L,
    t,
    z,
};

enum formatSpecifier {
    a,
    A,
    c,
    d,
    e,
    E,
    f,
    F,
    g,
    G,
    i,
    n,
    o,
    p,
    s,
    u,
    x,
    X
};

struct formatType {
    bool negative = 0;
    bool positive = 0;
    bool space = 0;
    bool sharp = 0;
    bool zero = 0;
    int width = 0;
    int precision = 0;
    formatLength length;
    formatSpecifier spec;
};

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

template<typename T>
string intToString(formatType prototype, T number) {
    string stringNumber;
    char *charNumber = new char[20];
    switch (prototype.length) {
        case hh:
            snprintf(charNumber, 20, "%hhd", number);
            break;
        case h:
            snprintf(charNumber, 20, "%hd", number);
            break;
        case l:
            snprintf(charNumber, 20, "%ld", number);
            break;
        case ll:
            snprintf(charNumber, 20, "%lld", number);
            break;
        case j:
            snprintf(charNumber, 20, "%jd", number);
            break;
        case z:
            snprintf(charNumber, 20, "%zd", number);
            break;
        case t:
            snprintf(charNumber, 20, "%td", number);
            break;
        default:
            snprintf(charNumber, 20, "%d", number);
    }
    stringNumber = charNumber;
    return stringNumber;
}

template<typename T>
string toOctHex(formatType prototype, T newNumber, string oldString) {
    string stringNumber;
    char *charNumber = new char[20];
    string mod = "";
    if (prototype.sharp)
        mod += "#";
    if (prototype.spec == o) {
        snprintf(charNumber, 20, ("%" + mod + "o").c_str(), newNumber);
        stringNumber = charNumber;
        return stringNumber;
    }
    if (prototype.spec == x) {
        snprintf(charNumber, 20, ("%" + mod + "x").c_str(), newNumber);
        stringNumber = charNumber;
        return stringNumber;
    }
    if (prototype.spec == X) {
        snprintf(charNumber, 20, ("%" + mod + "X").c_str(), newNumber);
        stringNumber = charNumber;
        for (int j = 0; i < stringNumber.length(); j++) {
            if (!isdigit(stringNumber[j])) {
                stringNumber[j] = toupper(stringNumber[j]);
            }
        }
        return stringNumber;
    }
    return oldString;
}

template<typename T>
string unsignedVar(formatType prototype, T number) {
    string stringNumber;
    char *charNumber = new char[20];
    switch (prototype.length) {
        case hh: {
            unsigned char newNumber = (unsigned char) number;
            snprintf(charNumber, 20, "%hhu", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case h: {
            unsigned short int newNumber = (unsigned short int) number;
            snprintf(charNumber, 20, "%hu", newNumber); //stringNumber = to_string(newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case l: {
            unsigned long int newNumber = (unsigned long int) number;
            snprintf(charNumber, 20, "%lu", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case ll: {
            unsigned long long int newNumber = (unsigned long long int) number;
            snprintf(charNumber, 20, "%llu", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case j: {
            uintmax_t newNumber = (uintmax_t) number;
            snprintf(charNumber, 20, "%ju", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case z: {
            size_t newNumber = (size_t) number;
            snprintf(charNumber, 20, "%zu", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case t: {
            ptrdiff_t newNumber = (ptrdiff_t) number;
            snprintf(charNumber, 20, "%tu", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        default: {
            unsigned int newNumber = (unsigned int) number;
            snprintf(charNumber, 20, "%u", newNumber);
            stringNumber = charNumber;
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
        }
    }
    return stringNumber;
}

template<typename T>
string floatSpec(formatType prototype, T number) {
    string stringNumber;
    char *charNumber = new char[1024];
    string mod = "";
    if (prototype.sharp)
        mod += "#";
    if (prototype.precision != -1) {
        mod += ".";
        char *tempPr = new char[20];
        snprintf(tempPr, 20, "%d", prototype.precision);
        mod += tempPr;
    }
    switch (prototype.spec) {
        case E:
            snprintf(charNumber, 1024, ("%" + mod + "E").c_str(), number);
            break;
        case e:
            snprintf(charNumber, 1024, ("%" + mod + "e").c_str(), number);
            break;
        case F:
            snprintf(charNumber, 1024, ("%" + mod + "F").c_str(), number);
            break;
        case f:
            snprintf(charNumber, 1024, ("%" + mod + "f").c_str(), number);
            break;
        case A:
            snprintf(charNumber, 1024, ("%" + mod + "A").c_str(), number);
            break;
        case a:
            snprintf(charNumber, 1024, ("%" + mod + "a").c_str(), number);
            break;
        case G:
            snprintf(charNumber, 1024, ("%" + mod + "G").c_str(), number);
            break;
        case g:
            snprintf(charNumber, 1024, ("%" + mod + "g").c_str(), number);
            break;
    }
    stringNumber = charNumber;
    return stringNumber;
}

template<typename T>
string floatNumbers(formatType prototype, T number) {
    string stringNumber;

    switch (prototype.length) {
        case L: {
            long double newNumber = (long double) number;
            stringNumber = floatSpec(prototype, newNumber);
            break;
        }
        default: {
            double newNumber = (double) number;
            stringNumber = floatSpec(prototype, newNumber);
        }
    }
    return stringNumber;
}

template<typename T>
string writeVar(formatType prototype, T variable) {
    string stringNumber;
    if (prototype.spec == d || prototype.spec == i) {
        stringNumber = intToString(prototype, variable);
        return lvlOfString(prototype, stringNumber);
    }
    if (prototype.spec == u || prototype.spec == o || prototype.spec == x || prototype.spec == X) {
        stringNumber = unsignedVar(prototype, variable);
        return lvlOfString(prototype, stringNumber);
    }
    if (prototype.spec == f || prototype.spec == F || prototype.spec == e || prototype.spec == E ||
        prototype.spec == g || prototype.spec == G || prototype.spec == a || prototype.spec == A) {
        stringNumber = floatNumbers(prototype, variable);
        return lvlOfString(prototype, stringNumber);
    }
    if (prototype.spec == c) {
        stringNumber += variable;
        return lvlOfString(prototype, stringNumber);
    }
    if (prototype.spec == s) {
        return lvlOfString(prototype, variable);
    }
}

template<typename T, typename... Args>
string toString(bool starMode, formatType prototype, string const &format, T first, Args ... args) {
    string answer = "";
    if (!starMode) {
        while (true) { //prints symbols before next "%"
            if (format[index] == '%' && format[index + 1] == '%') {
                answer += "%";
                index += 2;
            }
            if (format[index] == '%' && format[index + 1] != '%') {
                break;
            }
            answer += format[index];
            index++;
            if (index == format.length())
                return answer;
        }
        prototype = readFormat(format);
    }
    //cout << prototype.width << endl;
    //cout << prototype.spec << endl;
    if (prototype.width == -42) {
        prototype.width = (int)first;
        answer += toString(true, prototype, format, args...);
    }
    if (prototype.precision == -42) {
        prototype.precision = (int)first;
        answer += toString(true, prototype, format, args...);
    }

    answer += writeVar(prototype, first);
    answer += toString(false, prototype, format, args...);

    return answer;
};

template<typename ... Args>
string format(string const &format, Args ... args) {
    formatType x;
    string answer = toString(false, x, format, args...);
    return answer;
}

int main() {
    long long int g = 22;
    cout << format("%F", 392.65);
    printf("\n%-10c", 'd');
}