#ifndef STUDENTLIST
#define STUDENTLIST

#include "student.h"

class Studentlist{

    public:

        Studentlist();
        ~Studentlist();
        Studentlist(int cap, int s);
        void addStudent(Student student);
        void removeStudent(int index);
        int searchByBnum(string bnum);
        Student* findStudent(string const& student);

    private:

        int size;
        int capacity;
        Student *studentlist;

};

#endif