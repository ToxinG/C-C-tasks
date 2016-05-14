//
// Created by Антон on 16.04.2016.
//

#ifndef TASK4_FORMAT_H
#define TASK4_FORMAT_H

#include "format.cpp"

enum formatLength;

enum formatSpecifier;

struct formatType;

void getFlag(formatType *prototype, std::string const &format);

int getNumber(std::string const &format);

int getPrecision(std::string const &format);

formatLength getLength(std::string const &format);

formatSpecifier getSpecifier(std::string const &format);

formatType readFormat(std::string const &format);

std::string lvlOfString(formatType prototype, std::string stringNumber);

template<typename T>
std::string intToString(formatType prototype, T number);

template<typename T>
std::string unsignedVar(formatType prototype, T number);

template<typename T>
std::string floatSpec(formatType prototype, T number);

template<typename T>
std::string floatNumbers(formatType prototype, T number);

template<typename T>
std::string writeVar(formatType prototype, T variable);

std::string toSting(std::string const &format);

template<typename T, typename... Args>
std::string toString(std::string const &format, T first, Args ... args);

template<typename ... Args>
std::string format(std::string const &format, Args ... args);

#endif //TASK4_FORMAT_H
