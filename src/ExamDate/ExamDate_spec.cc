#include "ExamDate.h"
#include "../test/includes.h"
#include <cstddef>

TEST(ExamDate, isValidExamYear) {
    IT("returns true if year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        EXPECT_TRUE(ExamDate::isValidExamYear(year));
    }

    IT("returns false if year is not in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 0; year < 2000; ++year) {
        EXPECT_FALSE(ExamDate::isValidExamYear(year));
    }

    // from 2128 to the type upper Limit (when it overflows)
    for(ExamDate::Year year = 2128; year; ++year) {
        EXPECT_FALSE(ExamDate::isValidExamYear(year));
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

TEST(ExamDate, isValidExamDate) {
    IT("returns true if date is valid date and the year is in the Natural Numbers range [2000, 2127]");

    IT("returns true if day is in the Natural Numbers range [1, 28], month is in the Natural Numbers range [1, 12] and year is in the Natural Numbers range [2000, 2127]r");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(ExamDate::Day day = 1; day < 29; ++day) {
            for(ExamDate::Month month = 1; month < 13; ++month) {
                EXPECT_TRUE(ExamDate::isValidExamDate(day, month, year));
            }
        }
    }

    IT("returns true if day is 30, month is not February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        EXPECT_TRUE(ExamDate::isValidExamDate(30, 1, year));
        for(ExamDate::Month month = 3; month < 13; ++month) {
            EXPECT_TRUE(ExamDate::isValidExamDate(30, month, year));
        }
    }

    // The months April, June, September, November are with 30 days
    const ExamDate::Month monthsWith30Days[] = {4, 6, 9, 11};
    // The months January, March, May, July, August, October and December are with 31 days
    const ExamDate::Month monthsWith31Days[] = {1, 3, 5, 7, 8, 10, 12};

    IT("returns true if day is 31 if and only if month is in {1, 3, 5, 7, 8, 10, 12} and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 7; ++monthIndex) {
            EXPECT_TRUE(ExamDate::isValidExamDate(31, monthsWith31Days[monthIndex], year));
        }
    }

    IT("returns true if year is leap and the date is 29 of February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; year += 4) {
        if(year != 2100) {
            EXPECT_TRUE(ExamDate::isValidExamDate(29, 2, year));
        }
    }

    IT("returns false if year is not leap and the date is 29 of February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        if(((year % 4) > 0) || (((year % 400) != 0) && ((year % 100) == 0))) {
            EXPECT_FALSE(ExamDate::isValidExamDate(29, 2, year));
        }
    }

    IT("returns false if date is 30 or 31 of February and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        EXPECT_FALSE(ExamDate::isValidExamDate(30, 2, year));
        EXPECT_FALSE(ExamDate::isValidExamDate(31, 2, year));
    }

    IT("returns false if day is 31 and the month is in {4, 6, 9, 11} and the year is in the Natural Numbers range [2000, 2127]");
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(unsigned char monthIndex = 0; monthIndex < 4; ++monthIndex) {
            EXPECT_FALSE(ExamDate::isValidExamDate(31, monthsWith30Days[monthIndex], year));
        }
    }

    IT("returns false if day is not in the Natural Numbers range [1, 31] or month is not in the Natural Numbers range [1, 12] or the year is not in the Natural Numbers range [2000, 2127]");
    
    IT("returns false if date is 0 0 0");
    EXPECT_FALSE(ExamDate::isValidExamDate(0, 0, 0));
    IT("returns false if day is not in the Natural Numbers range [1, 31] no matter what month or year is");
    // counting on that ExamDate::Day, ExamDate::Month and ExamDate::Year are unsigned and it will overflow at 0 to break each loop
    for(ExamDate::Day day = 32; day != 1; ++day) {
        for(ExamDate::Month month = 1; month; ++month) {
            for(ExamDate::Year year = 1; year; ++year) {
                EXPECT_FALSE(ExamDate::isValidExamDate(day, month, year));
            }
        }
    }

    IT("returns false if month is not in the Natural Numbers range [1, 12] no matter what day or year is");
    // counting on that ExamDate::Day, ExamDate::Month and ExamDate::Year are unsigned and it will overflow at 0 to break each loop
    for(ExamDate::Day day = 1; day; ++day) {
        for(ExamDate::Month month = 13; month != 1; ++month) {
            for(ExamDate::Year year = 1; year; ++year) {
                EXPECT_FALSE(ExamDate::isValidExamDate(day, month, year));
            }
        }
    }

    IT("returns false when year is not in the Natural Numbers range [2000, 2127] no matter what day or month it is");
    // counting on that ExamDate::Day and ExamDate::Month are unsigned and it will overflow at 0 to break each loop
    // using that ExamDate::Year overflows
    for(ExamDate::Day day = 1; day; ++day) {
        for(ExamDate::Month month = 1; month; ++month) {
            for(ExamDate::Year year = 2128; year != 2000; ++year) {
                EXPECT_FALSE(ExamDate::isValidExamDate(day, month, year));
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

TEST(ExamDate, RelationalOperators) {
    IT("compares two ExamDates");

    // The months January, March, May, July, August, October and December are with 31 days
    // They are:  1,       3,     5,   7,    8,      10      and 12
    auto has31Days = [](const ExamDate::Month month) -> bool {
        switch(month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return true;
            default: return false;   
        }
    };

    // all years from 2000 to 2127 wich are diviisble by 4 except 2100 (it is divisible by 100 but not by 400)
    auto isLeapYear = [](const ExamDate::Year year) -> bool {
        return (!(year % 4)) && (year != 2100);
    };

    // if month is not February there are 30 + has31Days(month) days in it
    // if the month is February there are 28 + isLeapYear(year) days in it
    auto lastDayOfMonth = [has31Days, isLeapYear](const ExamDate::Month month, const ExamDate::Year year) -> ExamDate::Day {
        return (month != 2) ? (30 + has31Days(month)) : (28 + isLeapYear(year));
    };

    // (7 * 31) - There are exactly 7 months in each year wich have 31 days
    // 28 - In each year February has atleast 28 days 
    // (4 * 30) - There are exactly 4 months in each year wich have 30 days
    // + 31 - there are total of 31 leap years from 2000 to 2127 (all years divisible by 4 except 2100),
    const std::size_t datesCount = (((7 * 31) + 28 + (4 * 30) ) * 128) + 31;

    // the memory need for all ExamDates from 2000-0-0 to 31-12-2127 is exactly their count by there size (datesCount * sizeof(ExamDate))
    char dates[datesCount * sizeof(ExamDate)];

    std::size_t counter = 0;

    // Generating all ExamDates from 2000-0-0 to 31-12-2127
    for(ExamDate::Year year = 2000; year < 2128; ++year) {
        for(ExamDate::Month month = 1; month < 13; ++month) {
            const ExamDate::Day lastDay = lastDayOfMonth(month, year);
            for(ExamDate::Day day = 1; day <= lastDay; ++day) {
                // Using placement new since ExamDate has no default constructor
                new (dates + (counter * sizeof(ExamDate))) ExamDate{day, month, year};
                ++counter;
            }
        }
    }

    // reinterpreting the dates memory as array of ExamDate s
    const ExamDate* examDates = reinterpret_cast<ExamDate*>(dates);

    // foreach ExamDate
    for(std::size_t i = 0; i < datesCount; ++i) {
        // the current ExamDate should be eqaul to itself
        EXPECT_TRUE(examDates[i] == examDates[i]);
        // the current ExamDate should not be uneqaul to itself
        EXPECT_FALSE(examDates[i] != examDates[i]);
        // the current ExamDate should be less than or equal to itself
        EXPECT_TRUE(examDates[i] <= examDates[i]);
        // the current ExamDate should be greater than or equal to itself
        EXPECT_TRUE(examDates[i] >= examDates[i]);
        // All ExamDates which are with index greater than the current ExamDate are greater or equal to the current ExamDate
        for(std::size_t j = i + 1; j < datesCount; ++j) {
            EXPECT_TRUE(examDates[i] != examDates[j]);
            EXPECT_TRUE(examDates[j] != examDates[i]);

            EXPECT_TRUE(examDates[i] < examDates[j]);
            EXPECT_TRUE(examDates[i] <= examDates[j]);
            EXPECT_TRUE(examDates[j] >= examDates[i]);
            EXPECT_TRUE(examDates[j] > examDates[i]);

            // the opposite comparesion should be false
            EXPECT_FALSE(examDates[i] > examDates[j]);
            EXPECT_FALSE(examDates[i] >= examDates[j]);
            EXPECT_FALSE(examDates[j] <= examDates[i]);
            EXPECT_FALSE(examDates[j] < examDates[i]);
        }
    }
}

TEST(ExamDate, isValidExamYearHardCoded) {
    IT("returns true if the given hard coded year is in the Natural Numbers range [2000, 2127]");

    EXPECT_TRUE(ExamDate::isValidExamYear(2000));

    EXPECT_TRUE(ExamDate::isValidExamYear(2001));

    EXPECT_TRUE(ExamDate::isValidExamYear(2016));

    EXPECT_TRUE(ExamDate::isValidExamYear(2023));

    EXPECT_TRUE(ExamDate::isValidExamYear(2100));

    EXPECT_TRUE(ExamDate::isValidExamYear(2122));

    EXPECT_TRUE(ExamDate::isValidExamYear(2127));

    EXPECT_TRUE(ExamDate::isValidExamYear(2126));

    IT("returns false if the given hard coded year is not in the Natural Numbers range [2000, 2127]");

    EXPECT_FALSE(ExamDate::isValidExamYear(1999));

    EXPECT_FALSE(ExamDate::isValidExamYear(1996));

    EXPECT_FALSE(ExamDate::isValidExamYear(116));

    EXPECT_FALSE(ExamDate::isValidExamYear(325));

    EXPECT_FALSE(ExamDate::isValidExamYear(2222));

    EXPECT_FALSE(ExamDate::isValidExamYear(1111));

    EXPECT_FALSE(ExamDate::isValidExamYear(3000));

    EXPECT_FALSE(ExamDate::isValidExamYear(9999));
}

TEST(ExamDate, isLeapYearHardCoded) {
    IT("returns true if the given hard coded year is leap year");

    EXPECT_TRUE(ExamDate::isLeapYear(2000));

    EXPECT_TRUE(ExamDate::isLeapYear(2004));

    EXPECT_TRUE(ExamDate::isLeapYear(2016));

    EXPECT_TRUE(ExamDate::isLeapYear(2024));

    EXPECT_TRUE(ExamDate::isLeapYear(2104));

    EXPECT_TRUE(ExamDate::isLeapYear(2124));

    EXPECT_TRUE(ExamDate::isLeapYear(4000));

    EXPECT_TRUE(ExamDate::isLeapYear(2400));

    IT("returns false if the given hard coded year is not leap year");

    EXPECT_FALSE(ExamDate::isLeapYear(1999));

    EXPECT_FALSE(ExamDate::isLeapYear(1997));

    EXPECT_FALSE(ExamDate::isLeapYear(117));

    EXPECT_FALSE(ExamDate::isLeapYear(325));

    EXPECT_FALSE(ExamDate::isLeapYear(2222));

    EXPECT_FALSE(ExamDate::isLeapYear(1111));

    EXPECT_FALSE(ExamDate::isLeapYear(2100));

    EXPECT_FALSE(ExamDate::isLeapYear(1775));
}

TEST(ExamDate, isValidMonthHardCoded) {
    IT("returns true if the given hard coded number is in the Natural Numbers range [1, 12]");

    EXPECT_TRUE(ExamDate::isValidMonth(1));
    EXPECT_TRUE(ExamDate::isValidMonth(2));
    EXPECT_TRUE(ExamDate::isValidMonth(3));
    EXPECT_TRUE(ExamDate::isValidMonth(4));
    EXPECT_TRUE(ExamDate::isValidMonth(5));
    EXPECT_TRUE(ExamDate::isValidMonth(6));
    EXPECT_TRUE(ExamDate::isValidMonth(7));
    EXPECT_TRUE(ExamDate::isValidMonth(8));
    EXPECT_TRUE(ExamDate::isValidMonth(9));
    EXPECT_TRUE(ExamDate::isValidMonth(10));
    EXPECT_TRUE(ExamDate::isValidMonth(11));
    EXPECT_TRUE(ExamDate::isValidMonth(12));

    IT("returns false if the given hard coded number is not in the Natural Numbers range [1, 12]");

    EXPECT_FALSE(ExamDate::isValidMonth(0));
    EXPECT_FALSE(ExamDate::isValidMonth(22));
    EXPECT_FALSE(ExamDate::isValidMonth(33));
    EXPECT_FALSE(ExamDate::isValidMonth(42));
    EXPECT_FALSE(ExamDate::isValidMonth(15));
    EXPECT_FALSE(ExamDate::isValidMonth(61));
    EXPECT_FALSE(ExamDate::isValidMonth(73));
    EXPECT_FALSE(ExamDate::isValidMonth(18));
    EXPECT_FALSE(ExamDate::isValidMonth(99));
    EXPECT_FALSE(ExamDate::isValidMonth(100));
    EXPECT_FALSE(ExamDate::isValidMonth(111));
    EXPECT_FALSE(ExamDate::isValidMonth(127));
}

TEST(ExamDate, isValidDayHardCoded) {
    IT("returns true if the given hard coded date is with valid day");

    EXPECT_TRUE(ExamDate::isValidDay(1, 1, 1200));
    EXPECT_TRUE(ExamDate::isValidDay(2, 2, 2222));
    EXPECT_TRUE(ExamDate::isValidDay(3, 10, 1999));
    EXPECT_TRUE(ExamDate::isValidDay(4, 4, 2142));
    EXPECT_TRUE(ExamDate::isValidDay(5, 5, 1555));
    EXPECT_TRUE(ExamDate::isValidDay(6, 8, 1886));
    EXPECT_TRUE(ExamDate::isValidDay(7, 12, 2005));
    EXPECT_TRUE(ExamDate::isValidDay(8, 6, 1976));
    EXPECT_TRUE(ExamDate::isValidDay(29, 2, 2000));
    EXPECT_TRUE(ExamDate::isValidDay(31, 12, 2006));
    EXPECT_TRUE(ExamDate::isValidDay(26, 11, 1996));
    EXPECT_TRUE(ExamDate::isValidDay(12, 12, 2012));

    IT("returns false if the given hard coded date is with invalid day");

    EXPECT_FALSE(ExamDate::isValidDay(0, 2, 2000));
    EXPECT_FALSE(ExamDate::isValidDay(29, 2, 2001));
    EXPECT_FALSE(ExamDate::isValidDay(33, 3, 2003));
    EXPECT_FALSE(ExamDate::isValidDay(42, 2, 2010));
    EXPECT_FALSE(ExamDate::isValidDay(32, 10, 2010));
    EXPECT_FALSE(ExamDate::isValidDay(61, 7, 2007));
    EXPECT_FALSE(ExamDate::isValidDay(29, 2, 1999));
    EXPECT_FALSE(ExamDate::isValidDay(33, 5, 1876));
    EXPECT_FALSE(ExamDate::isValidDay(99, 9, 1799));
    EXPECT_FALSE(ExamDate::isValidDay(100, 1, 1111));
    EXPECT_FALSE(ExamDate::isValidDay(31, 4, 1933));
    EXPECT_FALSE(ExamDate::isValidDay(31, 9, 1978));
}

TEST(ExamDate, isValidExamDateHardCoded) {
    IT("returns true if the given hard coded date is with valid ExamDate");

    EXPECT_TRUE(ExamDate::isValidExamDate(1, 1, 2000));
    EXPECT_TRUE(ExamDate::isValidExamDate(2, 2, 2122));
    EXPECT_TRUE(ExamDate::isValidExamDate(3, 10, 2099));
    EXPECT_TRUE(ExamDate::isValidExamDate(4, 4, 2042));
    EXPECT_TRUE(ExamDate::isValidExamDate(5, 5, 2005));
    EXPECT_TRUE(ExamDate::isValidExamDate(6, 8, 2086));
    EXPECT_TRUE(ExamDate::isValidExamDate(7, 12, 2005));
    EXPECT_TRUE(ExamDate::isValidExamDate(8, 6, 2076));
    EXPECT_TRUE(ExamDate::isValidExamDate(29, 2, 2000));
    EXPECT_TRUE(ExamDate::isValidExamDate(31, 12, 2006));
    EXPECT_TRUE(ExamDate::isValidExamDate(26, 11, 2016));
    EXPECT_TRUE(ExamDate::isValidExamDate(12, 12, 2012));

    IT("returns false if the given hard coded date is with invalid ExamDate");

    EXPECT_FALSE(ExamDate::isValidExamDate(0, 2, 2000));
    EXPECT_FALSE(ExamDate::isValidExamDate(29, 2, 2001));
    EXPECT_FALSE(ExamDate::isValidExamDate(33, 3, 2003));
    EXPECT_FALSE(ExamDate::isValidExamDate(42, 2, 2010));
    EXPECT_FALSE(ExamDate::isValidExamDate(32, 10, 2010));
    EXPECT_FALSE(ExamDate::isValidExamDate(61, 7, 2007));
    EXPECT_FALSE(ExamDate::isValidExamDate(29, 2, 1999));
    EXPECT_FALSE(ExamDate::isValidExamDate(33, 5, 1876));
    EXPECT_FALSE(ExamDate::isValidExamDate(99, 9, 1799));
    EXPECT_FALSE(ExamDate::isValidExamDate(10, 12, 1111));
    EXPECT_FALSE(ExamDate::isValidExamDate(31, 1, 1933));
    EXPECT_FALSE(ExamDate::isValidExamDate(31, 7, 1978));
}

TEST(ExamDate, getDayHardCoded) {
    IT("returns the day with wich the hard coded ExamDate was created");

    EXPECT_EQ(ExamDate(1, 1, 2000).getDay(), 1);
    EXPECT_EQ(ExamDate(2, 2, 2122).getDay(), 2);
    EXPECT_EQ(ExamDate(3, 10, 2099).getDay(), 3);
    EXPECT_EQ(ExamDate(4, 4, 2042).getDay(), 4);
    EXPECT_EQ(ExamDate(5, 5, 2005).getDay(), 5);
    EXPECT_EQ(ExamDate(6, 8, 2086).getDay(), 6);
    EXPECT_EQ(ExamDate(7, 12, 2005).getDay(), 7);
    EXPECT_EQ(ExamDate(8, 6, 2076).getDay(), 8);
    EXPECT_EQ(ExamDate(29, 2, 2000).getDay(), 29);
    EXPECT_EQ(ExamDate(31, 12, 2006).getDay(), 31);
    EXPECT_EQ(ExamDate(26, 11, 2016).getDay(), 26);
    EXPECT_EQ(ExamDate(12, 12, 2012).getDay(), 12);
}

TEST(ExamDate, getMonthHardCoded) {
    IT("returns the month with wich the hard coded ExamDate was created");

    EXPECT_EQ(ExamDate(1, 1, 2000).getMonth(), 1);
    EXPECT_EQ(ExamDate(2, 2, 2122).getMonth(), 2);
    EXPECT_EQ(ExamDate(3, 10, 2099).getMonth(), 10);
    EXPECT_EQ(ExamDate(4, 4, 2042).getMonth(), 4);
    EXPECT_EQ(ExamDate(5, 5, 2005).getMonth(), 5);
    EXPECT_EQ(ExamDate(6, 8, 2086).getMonth(), 8);
    EXPECT_EQ(ExamDate(7, 12, 2005).getMonth(), 12);
    EXPECT_EQ(ExamDate(8, 6, 2076).getMonth(), 6);
    EXPECT_EQ(ExamDate(29, 2, 2000).getMonth(), 2);
    EXPECT_EQ(ExamDate(31, 12, 2006).getMonth(), 12);
    EXPECT_EQ(ExamDate(26, 11, 2016).getMonth(), 11);
    EXPECT_EQ(ExamDate(12, 12, 2012).getMonth(), 12);
}

TEST(ExamDate, getYearHardCoded) {
    IT("returns the year with wich the hard coded ExamDate was created");

    EXPECT_EQ(ExamDate(1, 1, 2000).getYear(), 2000);
    EXPECT_EQ(ExamDate(2, 2, 2122).getYear(), 2122);
    EXPECT_EQ(ExamDate(3, 10, 2099).getYear(), 2099);
    EXPECT_EQ(ExamDate(4, 4, 2042).getYear(), 2042);
    EXPECT_EQ(ExamDate(5, 5, 2005).getYear(), 2005);
    EXPECT_EQ(ExamDate(6, 8, 2086).getYear(), 2086);
    EXPECT_EQ(ExamDate(7, 12, 2005).getYear(), 2005);
    EXPECT_EQ(ExamDate(8, 6, 2076).getYear(), 2076);
    EXPECT_EQ(ExamDate(29, 2, 2000).getYear(), 2000);
    EXPECT_EQ(ExamDate(31, 12, 2006).getYear(), 2006);
    EXPECT_EQ(ExamDate(26, 11, 2016).getYear(), 2016);
    EXPECT_EQ(ExamDate(12, 12, 2012).getYear(), 2012);
}

TEST(ExamDate, RelationalOperatorsHardCoded) {
    IT("compares two hard coded ExamDates");

    EXPECT_TRUE(ExamDate(1, 1, 2000) < ExamDate(31, 12, 2127));

    EXPECT_TRUE(ExamDate(1, 1, 2000) < ExamDate(29, 2, 2000));

    EXPECT_TRUE(ExamDate(30, 12, 2127) < ExamDate(31, 12, 2127));

    EXPECT_TRUE(ExamDate(31, 12, 2127) > ExamDate(1, 1, 2000));

    EXPECT_TRUE(ExamDate(29, 2, 2000) > ExamDate(1, 1, 2000));

    EXPECT_TRUE(ExamDate(31, 12, 2127) > ExamDate(30, 12, 2127));

    EXPECT_TRUE(ExamDate(1, 1, 2000) <= ExamDate(31, 12, 2127));

    EXPECT_TRUE(ExamDate(1, 1, 2000) <= ExamDate(29, 2, 2000));

    EXPECT_TRUE(ExamDate(30, 12, 2127) <= ExamDate(31, 12, 2127));

    EXPECT_TRUE(ExamDate(31, 12, 2127) >= ExamDate(1, 1, 2000));

    EXPECT_TRUE(ExamDate(29, 2, 2000) >= ExamDate(1, 1, 2000));

    EXPECT_TRUE(ExamDate(31, 12, 2127) >= ExamDate(30, 12, 2127));

    EXPECT_TRUE(ExamDate(1, 1, 2000) != ExamDate(31, 12, 2127));

    EXPECT_TRUE(ExamDate(1, 1, 2000) != ExamDate(29, 2, 2000));

    EXPECT_TRUE(ExamDate(1, 1, 2000) == ExamDate(1, 1, 2000));

    EXPECT_TRUE(ExamDate(29, 2, 2000) == ExamDate(29, 2, 2000));
}