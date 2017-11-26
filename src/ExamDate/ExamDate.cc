#include "ExamDate.h"
#include <cassert>

ExamDate::ExamDate(const Day day, const Month month, const Year year) noexcept {
    assert(isValidExamDate(day, month, year));
    // date exatly encodes the day of the given Date
    date = day;
    // adding and month to the date (setting month bits)
    date |= (static_cast<Date>(month) << monthBitShifts);
    // adding and year to the date (setting year bits)
    // removing the year offset of the encoded ExamDate
    date |= (static_cast<Date>(year - firstYear) << yearBitShifts);
}

ExamDate::Day ExamDate::getDay() const noexcept {
    // obtaing day by appling dayMask (it is encoded into the first bits)
    return date & dayMask;
}

ExamDate::Month ExamDate::getMonth() const noexcept {
     // obtaing onth by appling monthMask and bit shifting monthBitShifts to left (removing the day bit offset)
    return (date & monthMask) >> monthBitShifts;
}

ExamDate::Year ExamDate::getYear() const noexcept {
    // obtaing year by appling yearMask and bit shifting yearBitShifts to left (removing the day and moth bit offset)
    // and adding back the year offset
    return firstYear + ((date & yearMask) >> yearBitShifts);
}

bool ExamDate::isValidExamYear(const Year year) noexcept {
    // ensure year is in the Natural Number range [firstYear, lastYear]
    return (year >= firstYear) && (year <= lastYear);
}

bool ExamDate::isValidMonth(const Month month) noexcept {
    // ensure month is in the Natural Number range [1, 12]
    return (month > 0) && (month < 13);
}

bool ExamDate::isLeapYear(const Year year) noexcept {
    // returns true if and only if year is leap year
    // leap year is year divisible by 4 and divisible by 100 if and only if divisible by 400
    const bool isDivisibleBy100 = !(year % 100);
    return !(year % 4) && (!isDivisibleBy100 || (isDivisibleBy100 && !(year % 400)));
}

bool ExamDate::isValidDay(const Day day, const Month month, const Year year) noexcept {
    assert(isValidMonth(month));
    // returns true if and only if the day is valid day in the given month and year
    // day is valid if it is in the Natural Numbers range [1, 28]
    // day is valid if it is 30 and the month is not 2 (February)
    if((day > 0) && (day < 32)) {
        switch(month) {
            case 2:
                // day is valid if it is 29 the month is not 2 (February) or the year is leap
                return (day < 30) && ((day != 29) || isLeapYear(year));
            case 4:
            case 6:
            case 9:
            case 11:
                return day != 31;
            // day is valid if it is 31 and the month is in {1, 3, 5, 7, 8, 10, 12}
            default: return true;
        }
    }
    return false;
}

bool ExamDate::isValidExamDate(const Day day, const Month month, const Year year) noexcept {
    // ExamDate is valid if it is valid Date for 2000-1-1 to 2127-12-31
    return isValidMonth(month) && isValidExamYear(year) && isValidDay(day, month, year);
}

bool ExamDate::operator==(const ExamDate& other) const noexcept {
    // returns true if and only if the two ExamDate s were mapped to the same value
    // ensures that they were also constructed with the exact same arguments
    return date == other.date;
}

bool ExamDate::operator!=(const ExamDate& other) const noexcept {
    // returns false if and only if the two ExamDate s were mapped to the same value
    // they are different if are mapped to different values
    return !operator==(other);
}

bool ExamDate::operator<(const ExamDate& other) const noexcept {
    // returns true if and only if the current ExamDate was mapped to value which represent chronological Date before other
    return date < other.date;
}

bool ExamDate::operator>(const ExamDate& other) const noexcept {
    // returns true if and only if the current ExamDate was mapped to value which represent chronological Date after other
    // switching argumetns ensures it
    return other < (*this);
}

bool ExamDate::operator<=(const ExamDate& other) const noexcept {
    // this ExamDate is less or equal to other if it is not greater than it
    return !operator>(other);
}

bool ExamDate::operator>=(const ExamDate& other) const noexcept {
    // this ExamDate is greater or equal to other if it is not less than it
    return !operator<(other);
}