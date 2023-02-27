#ifndef COURSE
#define COURSE
#include "student.h"
#include <string>

using namespace std;

class Student;

class Course{

    public:

        Course();
        Course(string crn, string cNum, string name, string department);
        Course(const Course &rhs);
        ~Course();
        string getCrn();
        string getCdep();
        string getCname();
        string getCnum();
        Course &operator=(const Course &rhs);
        void showStudents();
        void addStudent(Student student);
        void removeStudent(Student student);

    private:

        int capacity;
        int size;
        string cCrn;
        string courseNum;
        string courseName;
        string cDepartment;
        Student *students;


        
};

#endif