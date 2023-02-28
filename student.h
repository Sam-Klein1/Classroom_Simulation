#ifndef STUDENT
#define STUDENT
#include "course.h"
#include <string>

using namespace std;

class Course;

class Student{

    public:

        Student();
        Student(string bnum, string uid, string n, string sn);
        Student(const Student &rhs);
        ~Student();
        void addCrn(string crn);
        void removeCrn(string crn);
        bool searchCourse(string crn);
        Student &operator=(Student const &rhs);
        string* getCrns();
        string getName();
        string getBnum();
        string getSurname();
        int getSize();

    private:

        string bnumber;
        string name;
        string surname;
        string userid;
        int size;
        int capacity;
        string *crns;
     
};

#endif