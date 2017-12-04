#include "StudentExam.h"
#include <utility>
#include <cassert>

StudentExam::StudentExam(const ExamDate& examDate, const StudentAge studentAge, const Grade grade) noexcept
: examDate{examDate}, studentAge{studentAge}, grade{grade} {
    assert(isValidAge(studentAge) && isValidGrade(grade));
}

StudentExam::StudentExam(ExamDate&& examDate, const StudentAge studentAge, const Grade grade) noexcept
: examDate{std::move(examDate)}, studentAge{studentAge}, grade{grade} {
    assert(isValidAge(studentAge) && isValidGrade(grade));
}

const ExamDate& StudentExam::getExamDate() const noexcept {
    return examDate;
}

StudentExam::StudentAge StudentExam::getAge() const noexcept {
    return studentAge;
}

StudentExam::Grade StudentExam::getGrade() const noexcept {
    return grade;
}

void StudentExam::setExamDate(const ExamDate& newExamDate) noexcept {
    examDate = newExamDate;
}

void StudentExam::setExamDate(ExamDate&& newExamDate) noexcept {
    examDate = std::move(newExamDate);
}

void StudentExam::setStudentAge(const StudentAge newStudentAge) noexcept {
    assert(isValidAge(newStudentAge));
    studentAge = newStudentAge;
}

void StudentExam::setGrade(const Grade newGrade) noexcept {
    assert(isValidGrade(newGrade));
    grade = newGrade;
}

bool StudentExam::isValidGrade(const Grade grade) noexcept {
    return (grade >= 2) && (grade <= 6);
}

bool StudentExam::isValidAge(const StudentAge age) noexcept {
    return (age >= 16) && (age <= 80);
}