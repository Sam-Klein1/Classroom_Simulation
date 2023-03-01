#include <stdlib.h>
#include "studentlist.h"

Studentlist::Studentlist(){

            size = 0;
            capacity = 2;
            studentlist = new Student[capacity];
        }
Studentlist::~Studentlist(){delete[] studentlist;}
        
int Studentlist::searchByBnum(string bnum){

            int rindex;
            for(int i=0;i<capacity;i++){
                if(studentlist[i].getBnum() == bnum){//crn found in courselist
                    rindex = i;
                    return rindex;
                }
            }
            return -1;

        }
void Studentlist::addStudent(Student student){

            if(size == capacity){
                capacity = capacity*2;
                Student *temp = new Student[capacity];
                for(int i=0; i<size;i++){
                    temp[i] = studentlist[i];
                } 
                temp[size] = student;
                size++;
                delete[] studentlist;
                studentlist = temp;
            }
            else{
                studentlist[size] = student;
                size++;
            }
            
}
void Studentlist::removeStudent(int index){

            Student *newStudentlist = new Student[capacity];
            for(int i= 0; i<size; i++){
                if(i == index){
                    for(int j = i; j<size-1;j++)
                        newStudentlist[j] = studentlist[j+1];
                    --size;
                    break;
                }
                else{
                    newStudentlist[i] = studentlist[i];
                }
            }
            delete[] studentlist;
            studentlist = newStudentlist;
        
}
Student* Studentlist::findStudent(string const& bnum){

    Student *temp = nullptr;
    for(int i=0;i<size;i++){

        if(studentlist[i].getBnum() == bnum)
            temp = &studentlist[i];
    }
    return temp;
}