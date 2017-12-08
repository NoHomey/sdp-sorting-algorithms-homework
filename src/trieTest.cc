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

    trie.insert("Ivo Stratev", {examDate, 21, 6});

    trie.insert("Iva Kostatinowa", {examDate, 19, 6});

    trie.insert("Kia Milanowa", {examDate, 19, 6});

    trie.insert("Kris Keca", {examDate, 20, 5});

    trie.insert("Asia Lozanowa", {examDate, 21, 5});

    trie.insert("Katerina Stoyanowa", {examDate, 19, 4});

    trie.insert("Kat Loizz", {examDate, 19, 3});

    trie.insert("Lia Dobreva", {examDate, 20, 5});

    std::cout << trie.size() << std::endl;

    return 0;
}