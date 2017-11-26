#pragma once

// ExamDate maps Dates from 2000-1-1 to 2127-12-31 to 16 bit values
// It uses the first 5 bits for the day exatcly encoding all days form 1 to 31
// It uses bits 6 to 9 to encode months numbers from 1 to 12
// And it uses bits 10 to 16 to encode the year starting from year 2000 to year 2127
// 2^(16 - 10 + 1) - 1 = 127 total years
// ExamDate is perfect hashing storage class
class ExamDate {
public:
    // Day is Natural Number in the range [1, 31]
    using Day = unsigned char;
    
    // Month is Natural Number in the range [1, 12]
    using Month = unsigned char;

    // Year is Natural Number in the range [2000, 2127]
    using Year = unsigned short;

public:
    // Any Date from 2000-1-1 to 2127-12-31 can be the default Date, but there can be oly one default Date, so there is no default constructor
    ExamDate() noexcept = delete;

    // day is in range [1, 31], month in range [1, 12] and year in the range [2000, 2127]
    ExamDate(const Day day, const Month month, const Year year) noexcept;

    // There is only one class member wich is from integral type
    ~ExamDate() noexcept = default;

    // There is only one class member wich is from integral type
    ExamDate(const ExamDate& other) noexcept = default;

    // There is only one class member wich is from integral type
    ExamDate(ExamDate&& other) noexcept = default;

    // There is only one class member wich is from integral type
    ExamDate& operator=(const ExamDate& other) noexcept = default;

    // There is only one class member wich is from integral type
    ExamDate& operator=(ExamDate&& other) noexcept = default;

public:
    // returns the day with wich the ExamDate was constructed
    Day getDay() const noexcept;

    // returns the month with wich the ExamDate was constructed
    Month getMonth() const noexcept;

    // returns the year with wich the ExamDate was constructed
    Year getYear() const noexcept;

public:
    // returns true if and only if the two ExamDates were constructed with the exact same arguments
    bool operator==(const ExamDate& other) const noexcept;

    // returns false if and only if the two ExamDates were constructed with the exact same arguments
    bool operator!=(const ExamDate& other) const noexcept;

    // compares two ExamDates chronolocally (return true if and only if the left ExamDate encodes ExamDate before right one)
    bool operator<(const ExamDate& other) const noexcept;

    // compares two ExamDates chronolocally (return true if and only if the left ExamDate encodes ExamDate after right one)
    bool operator>(const ExamDate& other) const noexcept;

    // compares two ExamDates chronolocally (return false if and only if the left ExamDate encodes ExamDate after right one)
    bool operator<=(const ExamDate& other) const noexcept;

    // compares two ExamDates chronolocally (return false if and only if the left ExamDate encodes ExamDate before right one)
    bool operator>=(const ExamDate& other) const noexcept;

public:
    // returns true if and only if year is in the Natural Numbers range [2000, 2127]
    static bool isValidExamYear(const Year year) noexcept;

    // returns true if and only if month is in the Natural Numbers range [1, 12]
    static bool isValidMonth(const Month month) noexcept;

    // returns true if and only if year is leap year
    // leap year is year divisible by 4 and divisible by 100 if and only if divisible by 400
    static bool isLeapYear(const Year year) noexcept;
    
    // returns true if and only if the day is valid day in the given month and year
    // day is valid if it is in the Natural Numbers range [1, 28]
    // day is valid if it is 29 the month is not 2 (February) or the year is leap
    // day is valid if it is 30 and the month is not 2 (February)
    // day is valid if it is 31 and the month is in {1, 3, 5, 7, 8, 10, 12}
    static bool isValidDay(const Day day, const Month month, const Year year) noexcept;

    // return true if and only if the given spreaded date is valid date in the range 2000-1-1 to 2127-12-31
    static bool isValidExamDate(const Day day, const Month month, const Year year) noexcept;

private:
    // The c++ standart garanties that usnigned shor is atleast 16 bits long
    // see: http://en.cppreference.com/w/cpp/language/types, Properties
    using Date = unsigned short;

public:
    // The first year that can be encoded is the year 2000 (in the current implementation)
    static const Year firstYear = 2000;

    // The last year that can be encoded is the year 2127 (in the current implementation)
    // 2000 + 2^(16 - 10 + 1) - 1 = 2127
    static const Year lastYear = firstYear + ((1 << 7) - 1);

private:
    // bit mask for the day (first 5 bits)
    static const Date dayMask = 0b11111;

    // bit mask for the month (bits 6 to 9)
    static const Date monthMask = 0b111100000;

    // month is on offset 5 bits (after the day)
    static const unsigned char monthBitShifts = 5;

    // bit mask for the year (bits 10 to 16)
    static const Date yearMask = 0b1111111000000000;

    // month is on offset 9 = 5 + 4 bits (after the day and the month)
    static const unsigned char yearBitShifts = 9;

private:
    // 16 bit integral value to represent valid dates from 2000-1-1 to 2127-12-31
    Date date;
};