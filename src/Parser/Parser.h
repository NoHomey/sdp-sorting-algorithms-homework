#pragma once

#include "ParsedLine/ParsedLine.h"
#include "../Stack/Stack.thd"
#include <fstream>

class Parser {
public:
    Parser(const char* fileName);

    void ignoreHeading();

    ParsedLine readLine();

private:
    static bool isWhiteSpace(const char symbol) noexcept;

    static bool isDelimiter(const char symbol) noexcept;

private:
    void readString();

    unsigned short readNumber();

private:
    static const std::size_t initialBuffferCapacity = 1024;

private:
    std::ifstream input;

    Stack<char> buffer;
};