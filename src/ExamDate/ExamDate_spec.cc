#include "ExamDate.h"
#include "../test/includes.h"

TEST(ExamDate, isValidYear) {
    IT("returns true if year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        EXPECT_TRUE(ExamDate::isValidYear(year));
    }
    IT("returns false if year is not in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 0; year < 2000; ++year) {
        EXPECT_FALSE(ExamDate::isValidYear(year));
    }
    // from 2128 to the type upper Limit (when it overflows)
    for(ExamDate::Year year = 2128; year; ++year) {
        EXPECT_FALSE(ExamDate::isValidYear(year));
    }
}

TEST(ExamDate, isLeapYear) {
    IT("returns true if year is leap (it is exactly divisible by 4 except for century years (years ending with 00) which are not exactly divisible by 400");
    IT("returns true if year is equal to 0");
    EXPECT_TRUE(ExamDate::isLeapYear(0));
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    IT("returns true if year is exactly divisible by 4 and not exactly divisible by 100");
    for(ExamDate::Year year = 4; year; year += 4) {
        if((year % 100) > 0) {
            EXPECT_TRUE(ExamDate::isLeapYear(year));
        }
    }
    IT("returns true if year is centure year (years ending with 00) and it is divisible by 400");
    // from first positive divisible by 400 year to the type upper Limit (when it overflows)
    for(ExamDate::Year year = 400; year; year += 400) {
        EXPECT_TRUE(ExamDate::isLeapYear(year));
    }
    IT("returns false if year is centure year (years ending with 00) and it is not divisible by 400");
    //(infinit loop may be possible if overflow happens at number larger than 100)
    for(ExamDate::Year year = 100; year > 100; year += 100) {
        EXPECT_EQ(ExamDate::isLeapYear(year), (year % 400) > 0);
    }
    IT("returns false if year is not divisible by 4");
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        if((year % 4) > 0) {
            EXPECT_FALSE(ExamDate::isLeapYear(year));
        }
    }
}

TEST(ExamDate, isValidMonth) {
    IT("returns true if month is in the Natural Numbers range [1, 12]");
    for(ExamDate::Month month = 1; month < 13; ++month) {
        EXPECT_TRUE(ExamDate::isValidMonth(month));
    }
    IT("returns false if month is not in the Natural Numbers range [1, 12]");
    EXPECT_FALSE(ExamDate::isValidMonth(0));
    // from 13 to the type upper Limit (when it overflows)
    for(ExamDate::Month month = 13; month; ++month) {
        EXPECT_FALSE(ExamDate::isValidMonth(month));
    }
}

TEST(ExamDate, isValidDay) {
    IT("returns true if day is valid");
    IT("returns true if day is in the Natural Numbers range [1, 28] and month is in the Natural Numbers range [1, 12] no matter the year");
    // one loop for the 0 year
    for(ExamDate::Day day = 1; day < 29; ++day) {
        for(ExamDate::Month month = 1; month < 13; ++month) {
            EXPECT_TRUE(ExamDate::isValidDay(day, month, 0));
        }
    }
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        for(ExamDate::Day day = 1; day < 29; ++day) {
            for(ExamDate::Month month = 1; month < 13; ++month) {
                EXPECT_TRUE(ExamDate::isValidDay(day, month, year));
            }
        }
    }
    IT("returns true if day is 30 if and month is not February no matter the year");
    // one loop for the 0 year
    EXPECT_TRUE(ExamDate::isValidDay(30, 1, 0));
    for(ExamDate::Month month = 3; month < 13; ++month) {
        EXPECT_TRUE(ExamDate::isValidDay(30, month, 0));
    }
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        EXPECT_TRUE(ExamDate::isValidDay(30, 1, year));
        for(ExamDate::Month month = 3; month < 13; ++month) {
            EXPECT_TRUE(ExamDate::isValidDay(30, month, year));
        }
    }
    // The months April, June, September, November are with 30 days
    const ExamDate::Month monthsWith30Days[] = {4, 6, 9, 11};
    // The months January, March, May, July, August, October and December are with 31 days
    const ExamDate::Month monthsWith31Days[] = {1, 3, 5, 7, 8, 10, 12};
    IT("returns true if day is 31 if and only if month is in {1, 3, 5, 7, 8, 10, 12} no matter the year");
    // one loop for the 0 year
    for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
        EXPECT_TRUE(ExamDate::isValidDay(31, monthsWith31Days[monthIndex], 0));
    }
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
            EXPECT_TRUE(ExamDate::isValidDay(31, monthsWith31Days[monthIndex], year));
        }
    }
    IT("returns true if year is leap and the date is 29 of February");
    EXPECT_TRUE(ExamDate::isValidDay(29, 2, 0));
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 4; year; year += 4) {
        if(((year % 100) > 0) || ((year % 400) == 0)) {
            EXPECT_TRUE(ExamDate::isValidDay(29, 2, year));
        }
    }
    IT("returns false if year is not leap and the date is 29 of February");
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        if(((year % 4) > 0) || (((year % 400) != 0) && ((year % 100) == 0))) {
            EXPECT_FALSE(ExamDate::isValidDay(29, 2, year));
        }
    }
    IT("returns false if date is 30 or 31 of February");
    EXPECT_FALSE(ExamDate::isValidDay(30, 2, 0));
    EXPECT_FALSE(ExamDate::isValidDay(31, 2, 0));
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        EXPECT_FALSE(ExamDate::isValidDay(30, 2, year));
        EXPECT_FALSE(ExamDate::isValidDay(31, 2, year));
    }
    IT("returns false if day is 31 and the month is in {4, 6, 9, 11} no matter the year");
    // one loop for the 0 year
    for(unsigned char monthIndex = 0; monthIndex < 4; ++monthIndex) {
        EXPECT_FALSE(ExamDate::isValidDay(31, monthsWith30Days[monthIndex], 0));
    }
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 4; ++monthIndex) {
            EXPECT_FALSE(ExamDate::isValidDay(31, monthsWith30Days[monthIndex], year));
        }
    }
    IT("returns false if day is 0 or greater than 31 and month is in the Natural Numbers range [1, 12] no matter the year");
    // one loop for the 0 year
    for(ExamDate::Month month = 1; month < 13; ++month) {
        EXPECT_FALSE(ExamDate::isValidDay(0, month, 0));
        // counting on that ExamDate::Day is unsigned and it will overflow at 0 to break the loop
        for(ExamDate::Day day = 32; day; ++day) {
            EXPECT_FALSE(ExamDate::isValidDay(day, month, 0));
        }
    }
    // counting on that ExamDate::Year is unsigned and it will overflow at 0 to break the loop
    for(ExamDate::Year year = 1; year; ++year) {
        for(ExamDate::Month month = 1; month < 13; ++month) {
            EXPECT_FALSE(ExamDate::isValidDay(0, month, year));
            // counting on that ExamDate::Day is unsigned and it will overflow at 0 to break the loop
            for(ExamDate::Day day = 32; day; ++day) {
                EXPECT_FALSE(ExamDate::isValidDay(day, month, year));
            }
        }
    }
}

TEST(ExamDate, isValidDate) {
    IT("returns true if date is valid date and the year is in the Natural Numbers range [2000, 2127]");
    IT("returns true if day is in the Natural Numbers range [1, 28], month is in the Natural Numbers range [1, 12] and year is in the Natural Numbers range [2000, 2127]r");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(ExamDate::Day day = 1; day < 29; ++day) {
            for(ExamDate::Month month = 1; month < 13; ++month) {
                EXPECT_TRUE(ExamDate::isValidDate(day, month, year));
            }
        }
    }
    IT("returns true if day is 30, month is not February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        EXPECT_TRUE(ExamDate::isValidDate(30, 1, year));
        for(ExamDate::Month month = 3; month < 13; ++month) {
            EXPECT_TRUE(ExamDate::isValidDate(30, month, year));
        }
    }
    // The months April, June, September, November are with 30 days
    const ExamDate::Month monthsWith30Days[] = {4, 6, 9, 11};
    // The months January, March, May, July, August, October and December are with 31 days
    const ExamDate::Month monthsWith31Days[] = {1, 3, 5, 7, 8, 10, 12};
    IT("returns true if day is 31 if and only if month is in {1, 3, 5, 7, 8, 10, 12} and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
            EXPECT_TRUE(ExamDate::isValidDate(31, monthsWith31Days[monthIndex], year));
        }
    }
    IT("returns true if year is leap and the date is 29 of February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; year += 4) {
        if(year != 2100) {
            EXPECT_TRUE(ExamDate::isValidDate(29, 2, year));
        }
    }
    IT("returns false if year is not leap and the date is 29 of February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        if(((year % 4) > 0) || (((year % 400) != 0) && ((year % 100) == 0))) {
            EXPECT_FALSE(ExamDate::isValidDate(29, 2, year));
        }
    }
    IT("returns false if date is 30 or 31 of February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        EXPECT_FALSE(ExamDate::isValidDate(30, 2, year));
        EXPECT_FALSE(ExamDate::isValidDate(31, 2, year));
    }
    IT("returns false if day is 31 and the month is in {4, 6, 9, 11} and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 4; ++monthIndex) {
            EXPECT_FALSE(ExamDate::isValidDate(31, monthsWith30Days[monthIndex], year));
        }
    }
    IT("returns false if day is not in the Natural Numbers range [1, 31] or month is not in the Natural Numbers range [1, 12] or the year is not in the Natural Numbers range [2000, 2127]");
    IT("returns false if date is 0 0 0");
    EXPECT_FALSE(ExamDate::isValidDate(0, 0, 0));
    IT("returns false if day is not in the Natural Numbers range [1, 31] no matter what month or year is");
    // counting on that ExamDate::Day, ExamDate::Month and ExamDate::Year are unsigned and it will overflow at 0 to break each loop
    for(ExamDate::Day day = 32; day != 1; ++day) {
        for(ExamDate::Month month = 1; month; ++month) {
            for(ExamDate::Year year = 1; year; ++year) {
                EXPECT_FALSE(ExamDate::isValidDate(day, month, year));
            }
        }
    }
    IT("returns false if month is not in the Natural Numbers range [1, 12] no matter what day or year is");
    // counting on that ExamDate::Day, ExamDate::Month and ExamDate::Year are unsigned and it will overflow at 0 to break each loop
    for(ExamDate::Day day = 1; day; ++day) {
        for(ExamDate::Month month = 13; month != 1; ++month) {
            for(ExamDate::Year year = 1; year; ++year) {
                EXPECT_FALSE(ExamDate::isValidDate(day, month, year));
            }
        }
    }
    IT("returns false when year is not in the Natural Numbers range [2000, 2127] no matter what day or month it is");
    // counting on that ExamDate::Day and ExamDate::Month are unsigned and it will overflow at 0 to break each loop
    // using that ExamDate::Year overflows
    for(ExamDate::Day day = 1; day; ++day) {
        for(ExamDate::Month month = 1; month; ++month) {
            for(ExamDate::Year year = 2128; year != 2000; ++year) {
                EXPECT_FALSE(ExamDate::isValidDate(day, month, year));
            }
        }
    }
}

TEST(ExamDate, getDay) {
    IT("returns the day with wich the ExamDate obect was created");
    for(ExamDate::Day day = 1; day < 29; ++day) {
        for(ExamDate::Month month = 1; month < 13; ++month) {
            for(ExamDate::Year year = 2000; year < 2128; ++year) {
                const ExamDate date = {day, month, year};
                EXPECT_EQ(date.getDay(), day);
            }
        }
    }
    for(ExamDate::Day day = 29; day < 31; ++day) {
        for(ExamDate::Year year = 2000; year < 2128; ++year) {
            const ExamDate date = {day, 1, year};
            EXPECT_EQ(date.getDay(), day);
        }
    }
    for(ExamDate::Day day = 29; day < 31; ++day) {
        for(ExamDate::Month month = 3; month < 13; ++month) {
            for(ExamDate::Year year = 2000; year < 2128; ++year) {
                const ExamDate date = {day, month, year};
                EXPECT_EQ(date.getDay(), day);
            }
        }
    }
    const ExamDate::Month monthsWith31Days[] = {1, 3, 5, 7, 8, 10, 12};
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
            const ExamDate date = {31, monthsWith31Days[monthIndex], year};
            EXPECT_EQ(date.getDay(), 31);
        }
    }
    for(ExamDate::Year year = 2000; year < 2128; year += 4) {
        if(year != 2100) {
            const ExamDate date = {29, 2, year};
            EXPECT_EQ(date.getDay(), 29);
        }
    }
}

TEST(ExamDate, getMonth) {
    IT("returns the month with wich the ExamDate obect was created");
    for(ExamDate::Day day = 1; day < 29; ++day) {
        for(ExamDate::Month month = 1; month < 13; ++month) {
            for(ExamDate::Year year = 2000; year < 2128; ++year) {
                const ExamDate date = {day, month, year};
                EXPECT_EQ(date.getMonth(), month);
            }
        }
    }
    for(ExamDate::Day day = 29; day < 31; ++day) {
        for(ExamDate::Year year = 2000; year < 2128; ++year) {
            const ExamDate date = {day, 1, year};
            EXPECT_EQ(date.getMonth(), 1);
        }
    }
    for(ExamDate::Day day = 29; day < 31; ++day) {
        for(ExamDate::Month month = 3; month < 13; ++month) {
            for(ExamDate::Year year = 2000; year < 2128; ++year) {
                const ExamDate date = {day, month, year};
                EXPECT_EQ(date.getMonth(), month);
            }
        }
    }
    const ExamDate::Month monthsWith31Days[] = {1, 3, 5, 7, 8, 10, 12};
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
            const ExamDate date = {31, monthsWith31Days[monthIndex], year};
            EXPECT_EQ(date.getMonth(), monthsWith31Days[monthIndex]);
        }
    }
    for(ExamDate::Year year = 2000; year < 2128; year += 4) {
        if(year != 2100) {
            const ExamDate date = {29, 2, year};
            EXPECT_EQ(date.getMonth(), 2);
        }
    }
}

TEST(ExamDate, getYear) {
    IT("returns the year with wich the ExamDate obect was created");
    for(ExamDate::Day day = 1; day < 29; ++day) {
        for(ExamDate::Month month = 1; month < 13; ++month) {
            for(ExamDate::Year year = 2000; year < 2128; ++year) {
                const ExamDate date = {day, month, year};
                EXPECT_EQ(date.getYear(), year);
            }
        }
    }
    for(ExamDate::Day day = 29; day < 31; ++day) {
        for(ExamDate::Year year = 2000; year < 2128; ++year) {
            const ExamDate date = {day, 1, year};
            EXPECT_EQ(date.getYear(), year);
        }
    }
    for(ExamDate::Day day = 29; day < 31; ++day) {
        for(ExamDate::Month month = 3; month < 13; ++month) {
            for(ExamDate::Year year = 2000; year < 2128; ++year) {
                const ExamDate date = {day, month, year};
                EXPECT_EQ(date.getYear(), year);
            }
        }
    }
    const ExamDate::Month monthsWith31Days[] = {1, 3, 5, 7, 8, 10, 12};
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
            const ExamDate date = {31, monthsWith31Days[monthIndex], year};
            EXPECT_EQ(date.getYear(), year);
        }
    }
    for(ExamDate::Year year = 2000; year < 2128; year += 4) {
        if(year != 2100) {
            const ExamDate date = {29, 2, year};
            EXPECT_EQ(date.getYear(), year);
        }
    }
}