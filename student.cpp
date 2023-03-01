#include "student.h"
#include <string>
#include <iostream>

Student::Student(){

        bnumber = "";
        name = "";
        surname = "";
        userid = "";
        size = 0;
        capacity = 2;
        crns = new string[capacity];

}

Student::Student(string bnum, string uid, string n, string sn){

        bnumber = bnum;
        name = n;
        surname = sn;
        userid = uid;
        size = 0;
        capacity = 2;
        crns = new string[capacity];

}
Student::Student(const Student &rhs) {
    // Copy the primitive member variables
    bnumber = rhs.bnumber;
    name = rhs.name;
    surname = rhs.surname;
    userid = rhs.userid;
    size = rhs.size;
    capacity = rhs.capacity;
    // Allocate a new crns array and copy the contents of the original array
    crns = new string[capacity];
    for (int i = 0; i < size; i++) {
        crns[i] = rhs.crns[i];
    }
}
Student::~Student(){
        delete[] crns;
}

Student &Student::operator=(const Student &rhs){

        if(this!=&rhs){

                bnumber = rhs.bnumber;
                name = rhs.name;
                surname = rhs.surname;
                userid = rhs.userid;
                size = rhs.size;
                capacity = rhs.capacity;

                string *newCrns = new string[capacity];
                for(int i =0;i<size;i++){
                        
                        newCrns[i] = rhs.crns[i];
                }
                delete[] crns;
                crns = newCrns;
        }
        return *this;
}
void Student::addCrn(string crn){
    if(size == capacity){
                capacity = capacity*2;
                string *temp = new string[capacity];
                for(int i=0; i<size;i++){
                    temp[i] = crns[i];
                } 
                temp[size] = crn;
                size++;
                delete[] crns;
                crns = temp;
            }
            else{
                crns[size] = crn;
                size++;
            }
}
void Student::removeCrn(string crn){
        
        for(int i= 0; i<size; i++){
                if(crns[i] == crn){
                    string *newCrns = new string[capacity];
                    for(int j = i; j<size-1;j++)
                        newCrns[j] = crns[j+1];
                    //std::copy(students, students+i, newCrns);
                    //std::copy(students+i+1, students+size, newCrns+i);
                    //delete[] students;
                    //students = newCrns;
                    --size;
                    delete[] crns;
                    crns = newCrns;
                }
            }
        // for(int i= 0; i<size; i++){
        //         if(crns[i] == crn){
        //             string *new_crns = new string[size-1];
        //             std::copy(crns, crns+i, new_crns);
        //             std::copy(crns+i+1, crns+size, new_crns+i);
        //             delete[] crns;
        //             crns = new_crns;
        //             --size;
        //         }
        //     }
}
bool Student::searchCourse(string crn){

        for(int i=0;i<size;i++){

                if(crns[i] == crn)
                        return true; 
        }
        return false;
}
string* Student::getCrns(){return crns;}
string Student::getName(){return name;}
string Student::getSurname(){return surname;}
string Student::getBnum(){return bnumber;}
int Student::getSize(){return size;}
