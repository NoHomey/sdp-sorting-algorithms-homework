#include <iostream>
#include "StudentExam/StudentExam.h"
#include "SparseTrie/SparseTrie.thd"

std::size_t gradeSelector(const StudentExam& studentExam) noexcept {
    return studentExam.getGrade() - 2;
}

std::ostream& operator<<(std::ostream& out, const ExamDate& examDate) {
    return out << static_cast<unsigned short>(examDate.getDay())
        << '-' << static_cast<unsigned short>(examDate.getMonth())
        << '-' << examDate.getYear();
}

std::ostream& operator<<(std::ostream& out, const StudentExam& exam) {
    return out << exam.getExamDate() << ' '
            << static_cast<unsigned short>(exam.getAge()) << ' '
            << static_cast<unsigned short>(exam.getGrade()) << std::endl;
}

int main() {
    const ExamDate examDate{2, 12, 2017};
    
    SparseTrie<StudentExam> trie;

    trie.insert("abcd", {examDate, 21, 6});
    trie.insert("abbb", {examDate, 19, 6});
    trie.insert("bbb", {examDate, 19, 6});
    trie.insert("a", {examDate, 20, 5});
    trie.insert("b", {examDate, 21, 5});
    trie.insert("aabb", {examDate, 19, 4});
    trie.insert("abcde", {examDate, 19, 3});
    trie.insert("abcdee", {examDate, 19, 3});
    trie.insert("abcdf", {examDate, 20, 5});
    trie.insert("bb", {examDate, 19, 6});
    trie.insert("ab", {examDate, 20, 5});
    trie.insert("abc", {examDate, 21, 5});
    trie.insert("abb", {examDate, 19, 4});
    trie.insert("aa", {examDate, 19, 3});
    trie.insert("aab", {examDate, 20, 5});

    std::cout << trie.size() << std::endl;

    {
        SparseTrie<StudentExam>::AscOrderConstIterator iter = trie.ascOrderFirst();
        for(std::size_t i = 0; iter; ++iter, ++i) {
            auto res = *iter;
            std::cout << i << ' ' << res.first << ' ' << res.second;
        }
    }

    {
        SparseTrie<StudentExam>::DescOrderConstIterator iter = trie.descOrderFirst();
        for(std::size_t i = 0; iter; ++iter, ++i) {
            auto res = *iter;
            std::cout << i << ' ' << res.first << ' ' << res.second;
        }
    }

    return 0;
}