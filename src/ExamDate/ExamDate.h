#pragma once

class ExamDate {
public:
    using Day = unsigned char;
    
    using Month = unsigned char;

    using Year = unsigned short;

public:
    ExamDate() noexcept = delete;

    ExamDate(const Day day, const Month month, const Year year) noexcept;

    ~ExamDate() noexcept = default;

    ExamDate(const ExamDate& other) noexcept = default;

    ExamDate(ExamDate&& other) noexcept = default;

    ExamDate& operator=(const ExamDate& other) noexcept = default;

    ExamDate& operator=(ExamDate&& other) noexcept = default;

public:
    Day getDay() const noexcept;

    Month getMonth() const noexcept;

    Year getYear() const noexcept;

public:
    static bool isValidYear(const Year year) noexcept;

    static bool isValidMonth(const Month month) noexcept;

    static bool isLeapYear(const Year year) noexcept;
    
    static bool isValidDay(const Day day, const Month month, const Year year) noexcept;

    static bool isValidDate(const Day day, const Month month, const Year year) noexcept;

private:
    using Date = unsigned short;

public:
    static const Year firstYear = 2000;

    static const Year lastYear = firstYear + ((1 << 7) - 1);

private:
    static const Date dayMask = 0b11111;

    static const Date monthMask = 0b111100000;

    static const unsigned char monthBitShifts = 5;

    static const Date yearMask = 0b1111111000000000;

    static const unsigned char yearBitShifts = 9;

private:
    Date date;
};