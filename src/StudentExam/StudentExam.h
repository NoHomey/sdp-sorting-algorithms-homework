#pragma once

#include "../ExamDate/ExamDate.h"

class StudentExam {
public:
    using StudentAge = unsigned char;

    using Grade = unsigned char;

public:
    StudentExam(const ExamDate& examDate, const StudentAge studentAge, const Grade grade) noexcept;

    StudentExam(ExamDate&& examDate, const StudentAge studentAge, const Grade grade) noexcept;

    StudentExam(const StudentExam& other) noexcept = default;

    StudentExam(StudentExam&& other) noexcept = default;

    StudentExam& operator=(const StudentExam& other) noexcept = default;

    StudentExam& operator=(StudentExam&& other) noexcept = default;

public:
    const ExamDate& getExamDate() const noexcept;

    StudentAge getAge() const noexcept;

    Grade getGrade() const noexcept;

public:
    void setExamDate(const ExamDate& newExamDate) noexcept;

    void setExamDate(ExamDate&& newExamDate) noexcept;

    void setStudentAge(const StudentAge newStudentAge) noexcept;

    void setGrade(const Grade newGrade) noexcept;

public:
    static bool isValidGrade(const Grade grade) noexcept;

    static bool isValidAge(const StudentAge age) noexcept;

private:
    ExamDate examDate;

    StudentAge studentAge;

    Grade grade;
};