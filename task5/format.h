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
        X,
        doge,
        none
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
        string mod = "";
        if (prototype.sharp)
            mod = "#";
        switch (prototype.length) {
            case hh:
                snprintf(charNumber, 20, ("%" + mod + "hhd").c_str(), number);
                break;
            case h:
                snprintf(charNumber, 20, ("%" + mod + "hd").c_str(), number);
                break;
            case l:
                snprintf(charNumber, 20, ("%" + mod + "ld").c_str(), number);
                break;
            case ll:
                snprintf(charNumber, 20, ("%" + mod + "lld").c_str(), number);
                break;
            case j:
                snprintf(charNumber, 20, ("%" + mod + "jd").c_str(), number);
                break;
            case z:
                snprintf(charNumber, 20, ("%" + mod + "zd").c_str(), number);
                break;
            case t:
                snprintf(charNumber, 20, ("%" + mod + "td").c_str(), number);
                break;
            default:
                snprintf(charNumber, 20, ("%" + mod + "d").c_str(), number);
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

    string atComposer(nullptr_t variable);

    template<typename T>
    typename std::enable_if<!std::is_integral<T>::value &&
                            !std::is_convertible<T, string>::value && !std::is_pointer<T>::value, string>::type
    atComposer(const T& variable){
        throw std::invalid_argument("Invalid argument type.");
    }

    template<typename T>
    typename std::enable_if<(std::is_integral<T>::value), string>::type
    atComposer(T variable) {
        return std::to_string(variable);
    }

	template<typename T, int num> 
	typename std::enable_if<!std::is_convertible<T*, std::string>::value, std::string>::type
    atComposer(const T (&a)[num]) {
        std::string r = "[";
        for(int i = 0; i < num - 1; i++){
            r.append(std::to_string(a[i]) + ",");
        }
        r.append(std::to_string(a[num - 1]) + ']');
        return r;
    }

    template<typename T>
    typename std::enable_if<(std::is_convertible<T, string>::value), string>::type
    atComposer(const T& variable){
        return variable;
    }

    template<typename T>
    typename std::enable_if<((!std::is_array<T>::value) &&
            (!std::is_convertible<T, string>::value) && (std::is_pointer<T>::value)), string>::type
    atComposer(T& variable){
        std::string r;
        std::string type = typeid(*variable).name();
        if(type == "i"){
            type = "int";
        } else if(type == "Ss"){
            type = "std::string";
        }
        if(variable == 0){
            r.append("nullptr<").append(type).append(">");
        } else {
            formatType k; // k means kostyl'
            k.length = lengthNull;
            k.spec = u;
            formatIndex = 0;
            r.append("ptr<").append(type).append(">(").append(toString(false, k, "%@", *variable)).append(")");
        }
        return r;
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
        }
        else {
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
        if (prototype.precision == 0 && variable == 0)
            return "";
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
    string toString(bool starMode, formatType prototype, string const &format, const T &first, const Args &... args) {
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
                if (format[formatIndex] == '\0') {
                    if (format.size() == 0 || formatIndex == format.size()) {
                        throw std::invalid_argument("Too many arguments.");
                    }
                    answer += format[formatIndex];
                    return answer;
                }
                answer += format[formatIndex];
                formatIndex++;
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
        if (prototype.spec == doge)
            answer += atComposer(first);
        else
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

/**
 * returns string formatted according to the format string in the same way as in printf
 * modification: new specifier @ for pointers processing
 *
 * @param   args
 *          Arguments declared in format string by special symbols
 *
 * @throws  std::invalid_argument
 *          Thrown when the function gets an argument with wrong type
 *
 * @throws  std::out_of_range
 *          Thrown when there are not enough arguments
 */

template<typename ... Args>
string format(const string &format, Args ... args) {
    formatType x;
    x.length = lengthNull;
    x.spec = u;
    formatIndex = 0;
    string answer = toString(false, x, format, args...);
    return answer;
};

#endif //TASK4_FORMAT_H
