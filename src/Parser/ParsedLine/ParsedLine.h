#pragma once

#include "../../String/String.h"

struct ParsedLine {
    String name;

    String subject;

    unsigned short age;

    unsigned short grade;

    unsigned short year;

    unsigned short month;

    unsigned short day;

    ParsedLine(
        String&& name,
        const unsigned short age,
        String&& subject,
        const unsigned short grade,
        const unsigned short year,
        const unsigned short month,
        const unsigned short day
    ) noexcept;

    ~ParsedLine() noexcept = default;

    ParsedLine(const ParsedLine& other) = default;

    ParsedLine(ParsedLine&& other) noexcept = default;

    ParsedLine& operator=(const ParsedLine& other) = default;

    ParsedLine& operator=(ParsedLine&& other) noexcept = default;
};