#include "ExamDate.h"
#include <cassert>

ExamDate::ExamDate(const Day day, const Month month, const Year year) noexcept {
    assert(isValidDate(day, month, year));
    date = day;
    date |= (static_cast<Date>(month) << monthBitShifts);
    date |= (static_cast<Date>(year - firstYear) << yearBitShifts);
}

ExamDate::Day ExamDate::getDay() const noexcept {
    return date & dayMask;
}

ExamDate::Month ExamDate::getMonth() const noexcept {
    return (date & monthMask) >> monthBitShifts;
}

ExamDate::Year ExamDate::getYear() const noexcept {
    return firstYear + ((date & yearMask) >> yearBitShifts);
}

bool ExamDate::isValidYear(const Year year) noexcept {
    return (year >= firstYear) && (year <= lastYear);
}

bool ExamDate::isValidMonth(const Month month) noexcept {
    return (month > 0) && (month < 13);
}

bool ExamDate::isLeapYear(const Year year) noexcept {
    const bool isDivisibleBy100 = !(year % 100);
    return !(year % 4) && (!isDivisibleBy100 || (isDivisibleBy100 && !(year % 400)));
}

bool ExamDate::isValidDay(const Day day, const Month month, const Year year) noexcept {
    assert(isValidMonth(month));
    if((day > 0) && (day < 32)) {
        switch(month) {
            case 2:
                return day < 30 ? (isLeapYear(year) ? true : (day != 29)) : false;
            case 4:
            case 6:
            case 9:
            case 11:
                return day != 31;
            default: return true;
        }
    }
    return false;
}

bool ExamDate::isValidDate(const Day day, const Month month, const Year year) noexcept {
    return isValidMonth(month) && isValidYear(year) && isValidDay(day, month, year);
}