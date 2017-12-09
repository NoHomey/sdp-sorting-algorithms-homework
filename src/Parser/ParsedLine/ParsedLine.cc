#include "ParsedLine.h"
#include <utility>

ParsedLine::ParsedLine(
    String&& name,
    const unsigned short age,
    String&& subject,
    const unsigned short grade,
    const unsigned short year,
    const unsigned short month,
    const unsigned short day
) noexcept
: name{std::move(name)},
age{age},
subject{std::move(subject)},
grade{grade},
year{year},
month{month},
day{day} { }