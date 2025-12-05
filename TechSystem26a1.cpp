// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"

TechSystem::TechSystem(): globalBonus(0)
{

}

TechSystem::~TechSystem()
{

}

StatusType TechSystem::addStudent(int studentId)
{
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    if (students.find(studentId) != nullptr) {
        return StatusType::FAILURE;
    }

    try {
        std::shared_ptr<StudentData> student = std::make_shared<StudentData>(studentId, -globalBonus);
        bool student_added = students.insert(studentId, student);

        if (!student_added) {
            return StatusType::FAILURE;
        }
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType TechSystem::removeStudent(int studentId)
{
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<StudentData>* studentPtr = students.find(studentId);
    if (studentPtr == nullptr) {
        return StatusType::FAILURE;
    }

    std::shared_ptr<StudentData> student = *studentPtr;
    if (student->numRegisteredCourses > 0) {
        return StatusType::FAILURE;
    }

    bool student_removed = students.remove(studentId);
    if (!student_removed) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType TechSystem::addCourse(int courseId, int points)
{
    if (courseId <= 0 || points <= 0) {
            return StatusType::INVALID_INPUT;
    }

    if (courses.find(courseId) != nullptr) {
        return StatusType::FAILURE;
    }

    try {
        std::shared_ptr<CourseData> course = std::make_shared<CourseData>(courseId, points);
        bool course_added = courses.insert(courseId, course);

        if (!course_added) {
            return StatusType::FAILURE;
        }
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;

}

StatusType TechSystem::removeCourse(int courseId)
{
    if (courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<CourseData>* coursePtr = courses.find(courseId);
    if (coursePtr == nullptr) {
        return StatusType::FAILURE;
    }

    std::shared_ptr<CourseData> course = *coursePtr;
    if (course->numStudentsInCourse > 0) {
        return StatusType::FAILURE;
    }

    bool course_removed = courses.remove(courseId);
    if (!course_removed) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<CourseData>* coursePtr = courses.find(courseId);
    std::shared_ptr<StudentData>* studentPtr = students.find(studentId);

    if (studentPtr == nullptr || coursePtr == nullptr) {
        return StatusType::FAILURE;
    }

    std::shared_ptr<CourseData> course = *coursePtr;
    std::shared_ptr<StudentData> student = *studentPtr;

    // student already enrolled
    if (course->studentsInCourse.find(studentId) != nullptr) {
        return StatusType::FAILURE;
    }

    try {
        bool student_added = course->studentsInCourse.insert(studentId, student);
        if (!student_added) {
            return StatusType::ALLOCATION_ERROR;
        }

        student->numRegisteredCourses += 1;
        course->numStudentsInCourse += 1;

    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    std::shared_ptr<CourseData>* coursePtr = courses.find(courseId);
    if (coursePtr == nullptr) {
        return StatusType::FAILURE;
    }

    std::shared_ptr<CourseData> course = *coursePtr;

    std::shared_ptr<StudentData>* studentPtr = course->studentsInCourse.find(studentId);
    if (studentPtr == nullptr) {
        return StatusType::FAILURE;
    }
    std::shared_ptr<StudentData> student = *studentPtr;


    // student not enrolled
    if (course->studentsInCourse.find(studentId) == nullptr) {
        return StatusType::FAILURE;
    }

    bool student_removed = course->studentsInCourse.remove(studentId);
    if (!student_removed) {
        return StatusType::FAILURE;
    }

    student->numRegisteredCourses -= 1;
    student->baseCredits += course->points;
    course->numStudentsInCourse -= 1;
    return StatusType::SUCCESS;
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    if (points <= 0) {
        return StatusType::INVALID_INPUT;
    }

    globalBonus += points;
    return StatusType::SUCCESS;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    if (studentId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    std::shared_ptr<StudentData>* studentPtr = students.find(studentId);
    if (studentPtr == nullptr) {
        return output_t<int>(StatusType::FAILURE);
    }
    std::shared_ptr<StudentData> student = *studentPtr;

    int points = student->baseCredits + globalBonus;

    return output_t<int>(points);

}