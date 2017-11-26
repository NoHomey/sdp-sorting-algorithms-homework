#pragma once

#include <cstddef>

// maps subject abbreviation (upto 12 upper case letters) to 64 bit value
// uses every 5 bits to encode one upper case letter
// SubjectAbbreviation is perfect hashing storage class
class SubjectAbbreviation {
public:
    using SubjectAbbreviationString = const char*;

public:
    // Any upto 12 upper case letters abbreviation can be the default one, but there can be oly one default constructor, so there is no default constructor
    SubjectAbbreviation() noexcept = delete;

    // There is only one class member wich is from integral type
    ~SubjectAbbreviation() noexcept = default;

    // There is only one class member wich is from integral type
    SubjectAbbreviation(const SubjectAbbreviation& other) noexcept = default;

    // There is only one class member wich is from integral type
    SubjectAbbreviation(SubjectAbbreviation&& other) noexcept = default;

    // There is only one class member wich is from integral type
    SubjectAbbreviation& operator=(const SubjectAbbreviation& other) noexcept = default;

    // There is only one class member wich is from integral type
    SubjectAbbreviation& operator=(SubjectAbbreviation&& other) noexcept = default;

    // upto 12 upper case letters subject abbreviation
    SubjectAbbreviation(SubjectAbbreviationString abbreviation) noexcept;

public:
    // returns the result of hashing out of the hashed subject abbreviation
    // warning: thread unsafe
    SubjectAbbreviationString getSubjectAbbreviation() const noexcept;

public:
    // changes subject abbreviation
    void setSubjectAbbreviation(SubjectAbbreviationString newSubjectAbbreviation) noexcept;

public:
    // returns true if and only if the two SubjectAbbreviation mapped the same subject abbreviation
    bool operator==(const SubjectAbbreviation& other) const noexcept;

    // returns false if and only if the two SubjectAbbreviation mapped the same subject abbreviation
    bool operator!=(const SubjectAbbreviation& other) const noexcept;

    // compares two SubjectAbbreviation lexicographically
    // return true if and only if the this SubjectAbbreviation encodes subject abbreviation that is less than right one
    bool operator<(const SubjectAbbreviation& other) const noexcept;

    // compares two SubjectAbbreviation lexicographically
    // return true if and only if the this SubjectAbbreviation encodes subject abbreviation that is greater than right one
    bool operator>(const SubjectAbbreviation& other) const noexcept;

    // compares two SubjectAbbreviation lexicographically
    // return true if and only if the this SubjectAbbreviation encodes subject abbreviation that is less than or equal to right one
    bool operator<=(const SubjectAbbreviation& other) const noexcept;

    // compares two SubjectAbbreviation lexicographically
    // return true if and only if the this SubjectAbbreviation encodes subject abbreviation that is greater than or equal to right one
    bool operator>=(const SubjectAbbreviation& other) const noexcept;

public:
    // returns true if and only if the given symbol is upper case letter
    static bool isUpperCaseLetter(const char symbol) noexcept;

    // returns true if and only if abbreviation length is greater than 0 and less than or equal to maxSubjectAbbreviationStringLength
    // and all symbols are upper case letters
    static bool isValid(SubjectAbbreviationString abbreviation) noexcept;


public:
    // 64 = 12 * 5 + 4, so upto 12 upper case letter can be perfectly hashed with the current implementation 
    static const std::size_t maxSubjectAbbreviationStringLength = 12;

private:
    // The c++ standart garanties that usnigned long long is atleast 64 bits long
    // see: http://en.cppreference.com/w/cpp/language/types, Properties
    using Hash = unsigned long long;

private:
    // hashes valid subject abbrevaition string
    static Hash hash(SubjectAbbreviationString abbreviation) noexcept;

private:
    // letter mask
    static const char mask = 0b11111;

    // bit offset of each mapped upper case letter
    static const unsigned char offset = 5;

    // buffer used for hashing out mapped subject abbreviation
    static char hashOutString[maxSubjectAbbreviationStringLength + 1];

private:
    // hashed value (the storage)
    Hash hashed;
};