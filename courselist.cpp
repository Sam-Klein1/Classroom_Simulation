#include <stdlib.h>
#include "courselist.h"

Courselist::Courselist(){

            size = 0;
            capacity = 2;
            courselist = new Course[capacity];
        }
Courselist::~Courselist(){delete[] courselist;}
int Courselist::getSize(){return size;}

int Courselist::searchByCRN(string crn){

            int rindex;
            for(int i=0;i<capacity;i++){
                if(courselist[i].getCrn() == crn){//crn found in courselist
                    rindex = i;
                    return rindex;
                }
            }
            return -1;

        }
void Courselist::addCourse(Course course){

            if(size == capacity){
                capacity = capacity*2;
                Course *temp = new Course[capacity];
                for(int i=0; i<size;i++){
                    temp[i] = courselist[i];
                } 
                temp[size] = course;
                size++;
                delete[] courselist;
                courselist = temp;
            }
            else{
                courselist[size] = course;
                size++;
            }
            
        }
void Courselist::removeCourse(int index){
//found on https://stackoverflow.com/questions/22646257/remove-an-element-from-a-dynamic-array
            for(int i= 0; i<size; i++){
                if(i == index){
                    Course *newCourselist = new Course[capacity];
                    for(int j = i; j<size-1;j++)
                        newCourselist[j] = courselist[j+1];
                    //std::copy(students, students+i, newCourselist);
                    //std::copy(students+i+1, students+size, newCourselist+i);
                    //delete[] students;
                    //students = newCourselist;
                    --size;
                    delete[] courselist;
                    courselist = newCourselist;
                }
            }
            
            
            
            
            // for(int i= 0; i<size; i++){
            //     if(i == index){
            //         Course *newCourselist = new Course[size-1];
            //         std::copy(courselist, courselist+i, newCourselist);
            //         std::copy(courselist+i+1, courselist+size, newCourselist+i);
            //         delete[] courselist;
            //         courselist = newCourselist;
            //         --size;
            //     }
            // }
}
Course* Courselist::findCourse(string const& crn){

    Course *temp = nullptr;
    for(int i=0;i<size;i++){

        if(courselist[i].getCrn() == crn)
            temp = &courselist[i];
    }
    return temp;
}

