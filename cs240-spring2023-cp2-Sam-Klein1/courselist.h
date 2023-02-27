#ifndef COURSELIST
#define COURSELIST

#include "course.h"

class Courselist{

    public:

        Courselist();
        ~Courselist();
        Courselist(int cap, int s);
        Course* findCourse(string const& crn);
        int getSize();
        int searchByCRN(string crn);
        void addCourse(Course course);
        void removeCourse(int index);

    private:

        int size;
        int capacity;
        Course *courselist;

};

#endif