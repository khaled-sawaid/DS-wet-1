// 
// 234218 Data Structures 1.
// Semester: 2026A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef TechSystem26WINTER_WET1_H_
#define TechSystem26WINTER_WET1_H_

#include "wet1util.h"
#include "AVLTree.h"
#include <memory>

class TechSystem {
private:
    struct StudentData {
        int studentId;
        int numRegisteredCourses;
        int baseCredits;

        StudentData(int studentId, int baseCredits)
        : studentId(studentId), baseCredits(baseCredits), numRegisteredCourses(0) {}
    };

    struct CourseData {
        int courseId;
        int points;
        int numStudentsInCourse;
        AVLTree<int, std::shared_ptr<StudentData>> studentsInCourse;

        CourseData(int courseId, int points)
        : courseId(courseId), points(points), numStudentsInCourse(0) {}
    };

    // key = courseId
    AVLTree<int, std::shared_ptr<CourseData>> courses;
    // key = studentId
    AVLTree<int, std::shared_ptr<StudentData>> students;

    int globalBonus;

    //
    // Here you may add anything you want
    //
    
public:
    // <DO-NOT-MODIFY> {
    TechSystem();

    ~TechSystem();

    StatusType addStudent(int studentId);

    StatusType removeStudent(int studentId);

    StatusType addCourse(int courseId, int points);

    StatusType removeCourse(int courseId);

    StatusType enrollStudent(int studentId, int courseId);

    StatusType completeCourse(int studentId, int courseId);

    StatusType awardAcademicPoints(int points);
                    
    output_t<int> getStudentPoints(int studentId);

    // } </DO-NOT-MODIFY>
};

#endif // TechSystem26WINTER_WET1_H_
