#include "SubjectAbbreviation.h"
#include <cassert>
#include <cstring>

// storage initializator
char SubjectAbbreviation::hashOutString[maxSubjectAbbreviationStringLength + 1];

SubjectAbbreviation::SubjectAbbreviation(SubjectAbbreviationString abbreviation) noexcept
: hashed{hash(abbreviation)} { }

SubjectAbbreviation::SubjectAbbreviationString SubjectAbbreviation::getSubjectAbbreviation() const noexcept {
    // ignore hashOutString old content
    std::size_t index = 0;
    // copy the hash so it is not affected
    Hash copy = hashed;
    // while there are letter/s to be decoded
    while(copy) {
        // retrive the letter bits and add 'A' to them and substract one to decode exactly the mapped upper case letter
        hashOutString[index] = (static_cast<char>(copy) & mask) + 'A' - 1;
        // remove the read bits
        copy >>= offset;
        // increase string index for the next symbol
        ++index;
    }
    // terminate string
    hashOutString[index] = '\0';
    return hashOutString;
}

void SubjectAbbreviation::setSubjectAbbreviation(SubjectAbbreviationString newSubjectAbbreviation) noexcept {
    // just hash the new value
    hashed = hash(newSubjectAbbreviation);
}

bool SubjectAbbreviation::operator==(const SubjectAbbreviation& other) const noexcept {
    // returns true if and only if the same subject abbreviations are hashed by both objects
    return hashed == other.hashed;
}

bool SubjectAbbreviation::operator!=(const SubjectAbbreviation& other) const noexcept {
    // returns false if and only if the same subject abbreviations are hashed by both objects
    return !operator==(other);
}

bool SubjectAbbreviation::operator<(const SubjectAbbreviation& other) const noexcept {
    // returns true if the this SubjectAbbreviation has hashed string that is lexicographically before the one hashed by other
    return hashed < other.hashed;
}

bool SubjectAbbreviation::operator>(const SubjectAbbreviation& other) const noexcept {
    // returns true if the this SubjectAbbreviation has hahsed string that is lexicographically after the one hashed by other
    return other < (*this);
}

bool SubjectAbbreviation::operator<=(const SubjectAbbreviation& other) const noexcept {
    // this SubjectAbbreviation is less or equal to other if it is not greater than it
    return !operator>(other);
}

bool SubjectAbbreviation::operator>=(const SubjectAbbreviation& other) const noexcept {
    // this SubjectAbbreviation is greater or equal to other if it is not less than it
    return !operator<(other);
}

bool SubjectAbbreviation::isUpperCaseLetter(const char symbol) noexcept {
    // return true if and only if symbol is upper case letter
    return (symbol >= 'A') && (symbol <= 'Z');
}

bool SubjectAbbreviation::isValid(SubjectAbbreviationString abbreviation) noexcept {
    if(abbreviation) {
        const std::size_t length = std::strlen(abbreviation);
        //if length is greater than the max false will be returned to indicate invalidity
        if(length <= maxSubjectAbbreviationStringLength) {
            // for each symbol
            for(std::size_t index = 0; index < length; ++index) {
                // if the current symbol is not upper case letter false is returned to indicate invalidity
                if(!isUpperCaseLetter(abbreviation[index])) {
                    return false;
                }
            }
            // if length is zero, no loop cycle was made and false will be returned
            // else length is atleast 1 and the lop was not broken true will be returned 
            return length;
        }
    }
    // if abbreviation is null pointer or it length is greater than the max false will be returned
    return false;
}

SubjectAbbreviation::Hash SubjectAbbreviation::hash(SubjectAbbreviationString abbreviation) noexcept {
    assert(isValid(abbreviation));
    Hash mapped = 0;
    const std::size_t length = std::strlen(abbreviation);
    // for each upper case letter set the correct bitts with value in the range 1 to 27 (each letter is mapped in to offset bits at (offset * index) bit offset)
    // one is added so if any offset bits are 0 they indicated string end
    for(std::size_t index = 0; index < length; ++index) {
        mapped |= ((abbreviation[index] - 'A' + 1) << (offset * index));
    }
    return mapped;
}