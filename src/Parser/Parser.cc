#include "Parser.h"
#include <limits>
#include <stdexcept>

Parser::Parser(const char* fileName)
: input{fileName}, buffer{initialBuffferCapacity} {
    if(!input) {
        throw std::runtime_error{"could not open file"};
    }
}

void Parser::ParserignoreHeading() {
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

 ParsedLine Parser::ParserreadLine() {
    buffer.empty();
    readString();
    if(!input) {
        throw std::runtime_error{"error while reading"};
    }
    const std::size_t subjectOffset = buffer.size();
    const unsigned short age = readNumber();
    if(!input) {
        throw std::runtime_error{"error while reading"};
    }
    readString();
    if(!input) {
        throw std::runtime_error{"error while reading"};
    }
    const unsigned short grade = readNumber();
    if(!input) {
        throw std::runtime_error{"error while reading"};
    }
    unsigned short year;
    input >> year;
    input.ignore();
    if(!input) {
        throw std::runtime_error{"error while reading"};
    }
    unsigned short month;
    input >> month;
    input.ignore();
    if(!input) {
        throw std::runtime_error{"error while reading"};
    }
    unsigned short day;
    input >> day;
    input.ignore();
    if(!input && !input.eof()) {
        throw std::runtime_error{"error while reading"};
    }
    return {
        String{buffer.data(), subjectOffset - 1},
        age,
        String{buffer.data() + subjectOffset, buffer.size() - (subjectOffset + 1)},
        grade,
        year,
        month,
        day
    };
 }

 bool Parser::isWhiteSpace(const char symbol) noexcept {
    return (symbol == ' ') || (symbol == '\t');
 }

 bool Parser::isDelimiter(const char symbol) noexcept {
    return symbol == ',';
 }

 void Parser::readString() {
    char symbol;
    while(input) {
        symbol = input.get();
        if(isDelimiter(symbol)) {
            symbol = buffer.top();
            while(isWhiteSpace(symbol)) {
                buffer.pop();
                symbol = buffer.top();
            }
            buffer.push('\0');
            return;
        }
        buffer.push(symbol);
    }
 }

 unsigned short Parser::readNumber() {
    unsigned short number;
    input >> number;
    char symbol = input.peek();
    while(isWhiteSpace(symbol)) {
        symbol = input.peek();
    }
    if(isDelimiter(symbol)) {
        input.ignore();
    }
    return number;
 }