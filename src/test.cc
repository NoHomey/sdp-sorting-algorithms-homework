#include <iostream>
#include "StudentExam/StudentExam.h"
#include "SingleLinkedList/SingleLinkedList.thd"
#include "SingleLinkedList/NodeAllocator/ChunkAllocator/ChunkAllocator.thd"

using StudentExams = SingleLinkedList<StudentExam, ChunkAllocator>;

std::size_t gradeSelector(const StudentExam& studentExam) noexcept {
    return studentExam.getGrade() - 2;
}

std::ostream& operator<<(std::ostream& out, const ExamDate& examDate) {
    return out << static_cast<unsigned short>(examDate.getDay())
        << '-' << static_cast<unsigned short>(examDate.getMonth())
        << '-' << examDate.getYear();
}

void print(const StudentExams& exams) {
    for(StudentExams::ConstIterator iter = exams.first(); iter; ++iter) {
        std::cout << iter->getExamDate() << ' '
            << static_cast<unsigned short>(iter->getAge()) << ' '
            << static_cast<unsigned short>(iter->getGrade()) << std::endl;
    }
}

bool lessThanOrEqualAge(const StudentExam& a, const StudentExam& b) noexcept {
    return a.getAge() <= b.getAge();
}

bool greaterThanOrEqualAge(const StudentExam& a, const StudentExam& b) noexcept {
    return a.getAge() >= b.getAge();
}

int main() {
    const ExamDate examDate{2, 12, 2017};
    StudentExams exams{10};

    exams.prepend({examDate, 20, 6});
    exams.prepend({examDate, 21, 5});
    exams.prepend({examDate, 21, 3});
    exams.prepend({examDate, 21, 4});
    exams.prepend({examDate, 21, 4});
    exams.prepend({examDate, 21, 5});
    exams.prepend({examDate, 22, 6});
    exams.prepend({examDate, 20, 6});
    exams.prepend({examDate, 20, 6});
    exams.prepend({examDate, 20, 2});
    exams.prepend({examDate, 20, 3});
    exams.prepend({examDate, 19, 6});
    exams.prepend({examDate, 19, 2});
    exams.prepend({examDate, 19, 2});

    StudentExams copy = exams;

    print(exams);

    std::cout << "--------------------copy---------------------" << std::endl;

    print(copy);

    exams.mergeSort(lessThanOrEqualAge);

    std::cout << "--------------------merge--------------------" << std::endl;

    print(exams);

    exams.mergeSort(greaterThanOrEqualAge);

    std::cout << "---------------------------------------------" << std::endl;
    
    print(exams);

    exams.bucketSort<5>(gradeSelector);

    std::cout << "--------------------bucket---------------------" << std::endl;

    print(exams);

    exams.bucketSort<5>(gradeSelector, false);

    std::cout << "---------------------------------------------" << std::endl;

    print(exams);

    return 0;
}