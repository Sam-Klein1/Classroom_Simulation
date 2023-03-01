#include <iostream>
#include <stdlib.h>
#include <string>
#include "course.h"

using namespace std;

Course::Course(){
            cCrn = "";
            courseNum = "";
            courseName = "";
            cDepartment = "";
            size = 0;
            capacity = 2;
            students = new Student[capacity];
        }
Course::Course(string crn, string cNum, string name, string department){

            cCrn = crn;
            courseNum = cNum;
            courseName = name;
            cDepartment = department;
            size = 0;
            capacity = 2;
            students = new Student[capacity];

        }
Course::Course(const Course &rhs) {
    // Copy the primitive member variables
            cCrn = rhs.cCrn;
            courseNum = rhs.courseNum;
            courseName = rhs.courseName;
            cDepartment = rhs.cDepartment;
            size = rhs.size;
            capacity = rhs.capacity;
            // Allocate a new students array and copy the contents of the original array
            students = new Student[capacity];
            for (int i = 0; i < size; i++) {
                students[i] = Student(rhs.students[i]);
             }
}
Course &Course::operator=(const Course &rhs){

        if(this!=&rhs){

                cCrn = rhs.cCrn;
                courseNum = rhs.courseNum;
                courseName = rhs.courseName;
                cDepartment = rhs.cDepartment;
                size = rhs.size;
                capacity = rhs.capacity;

                Student *newStudentlist = new Student[capacity];
                for(int i =0;i<size;i++){
                        
                        newStudentlist[i] = rhs.students[i];
                }

                delete[] students;
                students = newStudentlist;
        }
        return *this;
}
string Course::getCrn(){return cCrn;}
string Course::getCname(){return courseName;}
string Course::getCdep(){return cDepartment;}
string Course::getCnum(){return courseNum;}
Course::~Course() {delete[] students;}

void Course::showStudents(){
            
            cout << "Students: " << size << endl;
            for(int i=0; i<size; i++){
                cout << students[i].getBnum() << " " << students[i].getName() << " " << students[i].getSurname() << endl;
            }
        }
void Course::addStudent(Student student){
    if(size == capacity){
                capacity = capacity*2;
                Student *temp = new Student[capacity];
                for(int i=0; i<size;i++){
                    temp[i] = students[i];
                } 
                temp[size] = student;
                size++;
                delete[] students;
                students = temp;
            }
            else{
                students[size] = student;
                size++;
            }
}
void Course::removeStudent(Student student){

            Student* newStudentlist = new Student[capacity];
            for(int i= 0; i<size; i++){
                if(students[i].getBnum() == student.getBnum()){
                    for(int j = i; j<size-1;j++)
                        newStudentlist[j] = students[j+1];
                    --size;
                    break;
                }
                else{
                    newStudentlist[i] = students[i];
                }
            }
            delete[] students;
            students = newStudentlist;
}