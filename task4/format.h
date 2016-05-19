//
// Created by Антон on 16.04.2016.
//

#ifndef TASK4_FORMAT_H
#define TASK4_FORMAT_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace std;

namespace Format {

    extern int formatIndex;

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

    void getFlag(formatType *prototype, string const &format);

    int getNumber(string const &format);

    int getPrecision(string const &format);

    formatLength getLength(string const &format);

    formatSpecifier getSpecifier(string const &format);

    //gets flags, width, precision, length and specifier from the format string
    formatType readFormat(string const &format);

    //modifies the printable string according to flags, width, and precision
    string stringModifier(formatType prototype, string stringNumber);

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
                snprintf(charNumber, 20, "%hu", newNumber);
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

    //makes string representation of printable value
    string stringComposer(formatType prototype, string variable);

    template<typename T>
    typename std::enable_if<(std::is_convertible<T, string>::value), string>::type
    stringComposer(formatType prototype, T variable) {
        if (prototype.spec == p) {
            string stringNumber;
            char *charNumber = new char[1024];
            snprintf(charNumber, 1024, "%p", variable);
            stringNumber = charNumber;
            return stringNumber;
        }
        if (prototype.spec == s) {
            string stringNumber = variable;
            return stringModifier(prototype, stringNumber);
        } else {
            throw std::invalid_argument("Invalid argument: string expected.");
        }
    }

    template<typename T>
    typename std::enable_if<(!(std::is_convertible<T, string>::value) && (std::is_pointer<T>::value)), string>::type
    stringComposer(formatType prototype, T variable) {
        string stringNumber;
        char *charNumber = new char[1024];
        snprintf(charNumber, 1024, "%p", variable);
        stringNumber = charNumber;
        return stringNumber;
    }

    template<typename T>
    typename std::enable_if<!(std::is_convertible<T, string>::value) && !(std::is_pointer<T>::value), string>::type
    stringComposer(formatType prototype, T variable) {
        string stringNumber;
        if (!is_convertible<T, int>::value) {
            throw std::invalid_argument("Invalid argument.");
        }
        if (prototype.spec == d || prototype.spec == i) {
            stringNumber = intToString(prototype, variable);
            return stringModifier(prototype, stringNumber);
        }
        if (prototype.spec == u || prototype.spec == o || prototype.spec == x || prototype.spec == X) {
            stringNumber = unsignedVar(prototype, variable);
            return stringModifier(prototype, stringNumber);
        }
        if (prototype.spec == f || prototype.spec == F || prototype.spec == e || prototype.spec == E ||
            prototype.spec == g || prototype.spec == G || prototype.spec == a || prototype.spec == A) {
            stringNumber = floatNumbers(prototype, variable);
            return stringModifier(prototype, stringNumber);
        }
        if (prototype.spec == c) {
            stringNumber += variable;
            return stringModifier(prototype, stringNumber);
        }
        throw std::invalid_argument("Invalid argument.");
    }

    //basic function that processes the format string and gets the result according to it
    string toString(bool starMode, formatType prototype, string const &format);

    template<typename T, typename... Args>
    string toString(bool starMode, formatType prototype, string const &format, T first, Args ... args) {
        string answer = "";
        if (!starMode) {
            while (true) { //prints symbols before next "%"
                if (format[formatIndex] == '%' && format[formatIndex + 1] == '%') {
                    answer += "%";
                    formatIndex += 2;
                }
                if (format[formatIndex] == '%' && format[formatIndex + 1] != '%') {
                    break;
                }
                answer += format[formatIndex];
                formatIndex++;
                if (formatIndex == format.length())
                    return answer;
            }
            prototype = readFormat(format);
        }
        //cout << prototype.width << endl;
        //cout << prototype.spec << endl;
        if (prototype.width == -42) {
            answer += starPower(prototype, format, first, args...);
            return answer;
        }
        if (prototype.precision == -42) {
            answer += starPower(prototype, format, first, args...);
            return answer;
        }
        answer += stringComposer(prototype, first);
        answer += toString(false, prototype, format, args...);

        return answer;
    };

    //corrects the work of toString if "*" is used in the format string
    string starPower(formatType prototype, string const &format);

    template<typename T, typename... Args>
    typename std::enable_if<(std::is_convertible<T, int>::value), string>::type
    starPower(formatType prototype, string const &format, T first, Args ... args) {
        if (prototype.width == -42) {
            prototype.width = first;
            return toString(true, prototype, format, args...);
        }
        if (prototype.precision == -42) {
            prototype.precision = first;
            return toString(true, prototype, format, args...);
        }
    };

    template<typename T, typename... Args>
    typename std::enable_if<!(std::is_convertible<T, int>::value), string>::type
    starPower(formatType prototype, string const &format, T first, Args ... args) {
        throw std::invalid_argument("Error: when \"*\" is used width or precision should be expressed with a number.");
    };
}

using namespace Format;

    template<typename ... Args>
    string format(string const &format, Args ... args) {
        formatType x;
        x.length = lengthNull;
        x.spec = u;
        formatIndex = 0;
        string answer = toString(false, x, format, args...);
        return answer;
    }

#endif //TASK4_FORMAT_H
