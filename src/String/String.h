#pragma once

#include <cstddef>
#include <cassert>

class String {
public:
    String() noexcept = delete;

    ~String() noexcept;

    String(const char* string, const std::size_t length) noexcept;

    String(const String& other);

    String(String&& other) noexcept;

    String& operator=(const String& other);

    String& operator=(String&& other) noexcept;

public:
    const char* cString() const noexcept;

    std::size_t length() const noexcept;

private:
    char* str;

    std::size_t strLength;
};