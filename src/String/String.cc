#include "String.h"
#include <cassert>
#include <cstring>

String::String(const char* string, const std::size_t length) noexcept
: str{nullptr}, strLength{length} {
    assert(length);
    assert(str);
    str = new char[length + 1];
    std::memcpy(str, string, length + 1);
}

String::~String() noexcept {
    delete[] str;
    strLength = 0;
}

String::String(const String& other)
: str{new char[other.strLength + 1]}, strLength{other.strLength} {
    std::memcpy(str, other.str, strLength + 1);
}

String::String(String&& other) noexcept
: str{other.str}, strLength{other.strLength} {
    other.str = nullptr;
    other.strLength = 0;
}

String& String::operator=(const String& other) {
    if(this != &other) {
        operator=({other});
    }
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if(this != &other) {
        delete[] str;
        str = other.str;
        strLength = other.strLength;
        other.str = nullptr;
        other.strLength = 0;
    }
    return *this;
}

const char* String::cString() const noexcept {
    return str;
}

std::size_t String::length() const noexcept {
    return strLength;
}