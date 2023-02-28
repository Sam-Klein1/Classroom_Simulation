#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include "courselist.h"
#include "studentlist.h"

using namespace std;

void showPrompt() {
   std::cout << "Enter [\"build <crn> <department> <number> <name>\"" << std::endl <<
                "       \"cancel <crn>\"" << std::endl <<
                "       \"enroll <bnumber> <userid> <first> <last>\"" << std::endl <<
                "       \"add <bnumber> <crn>\"" << std::endl <<
                "       \"drop <bnumber> <crn>\"" << std::endl <<
                "       \"roster <crn>\"" << std::endl <<
                "       \"schedule <bnumber>\"" << std::endl <<
                "       \"quit\"]" << endl <<
                ": ";
};
int main(){

    vector<string> strArr; //vector to hold commands and params
    string userInput;
    string token; //individual command to be pushed into the vector
    
    Courselist list_of_courses; //obj to represent "global" registry of courses
    Studentlist list_of_students; //obj to represent "global" registry of students

    showPrompt();

    while(getline(cin, userInput)){ //loop to continually ask for command and paramters 

        stringstream ss(userInput); //string stream object to pass thru as our source string

        while (getline(ss, token, ' ')){ //loop thru command and parameters
            if(!token.empty())
                strArr.push_back(token); //command = strArr[0], parameters in strArr[i]
        }
        if(strArr.empty()){//empty line clause
            showPrompt();
            continue;
        }  
        else if(strArr[0] == "quit")
            break; //command to break out of 'menu'

        else if(strArr[0] == "build"){

            if(!regex_match(strArr[1], regex("[0-9]{6}"))) //check crn
                cout << "Input Error: illegal CRN" << endl;
            else if(!regex_match(strArr[2], regex("[A-Z]{2,4}"))) //check department
                cout << "Input Error: illegal department" << endl;
            else if(!((stoi(strArr[3]) >= 100) && (stoi(strArr[3]) <= 700)))//check number
                cout << "Input Error: illegal number" << endl; 
            else if(!regex_match(strArr[4], regex("(.*?)")))//check name
                cout << "Input Error: illegal name" << endl;
            else{ 
                //if we get here we have valid parameters
                //Now, build the course
                Course course(strArr[1], strArr[3], strArr[4], strArr[2]);
                if(list_of_courses.searchByCRN(course.getCrn()) == -1){ // if this returns -1 then course not in courselist
                    //add the course
                    list_of_courses.addCourse(course);
                    cout << "Success: built course ";
                    cout << strArr[1] << " " << strArr[2] << strArr[3];
                    cout << " (CRN: " << strArr[3] << ") : ";
                    cout << strArr[4] << " ";
                    for(int i = 5; i < (int)strArr.size(); i++){
                        cout << strArr[i] << " ";
                    }
                    cout << endl;
                }
                else
                    cout << "Fail: cannot build course " << strArr[2] << strArr[3] << "(CRN: " << strArr[1] << "): CRN exists" << endl;
                     
            }

        }
        else if(strArr[0] == "cancel"){
            
            if(!regex_match(strArr[1], regex("[0-9]{6}"))) //check crn first
                cout << "Input Error: illegal CRN" << endl;
            //find course in list of courses, then remove it
            if(strArr.size() > 2)
                cout << "Warning: ignoring extra argument(s)" << endl;
            if(list_of_courses.searchByCRN(strArr[1]) == -1)
                cout << "Fail: cannot cancel course, CRN does not exist" << strArr[1] << endl;
            else{
                int index = list_of_courses.searchByCRN(strArr[1]);
                list_of_courses.removeCourse(index);
                cout << "Success: cancelled course " << strArr[1] << endl;
            }
        }
        else if(strArr[0] == "enroll"){

            if(strArr.size() < 5)
                cout << "Input Error: too few arguments" << endl;
            if(!regex_match(strArr[1], regex("B[0-9]{8}")))
                cout << "Input Error: illegal B number" << endl;
            else if(!regex_match(strArr[2], regex("^[a-zA-Z][a-zA-Z0-9]+")))
                cout << "Input Error: illegal userid" << endl;
            else if(!regex_match(strArr[3], regex("[a-zA-Z]+")))
                cout << "Input Error: illegal first name" << endl;
            else if(!regex_match(strArr[4], regex("[a-zA-Z]+")))
                cout << "Input Error: illegal last name" << endl;
            else{
                Student student(strArr[1], strArr[2], strArr[3], strArr[4]);
                if(list_of_students.searchByBnum(student.getBnum()) == -1){
                    list_of_students.addStudent(student);
                    cout << "Success: enrolled student " << strArr[1] << " (" << strArr[2] << ") " << strArr[4] << ", " << strArr[3] << endl;
                }
                else 
                    cout << "Fail: cannot enroll student, B Number exists" << endl;
            }
        }
        else if(strArr[0] == "add"){
            
            if(list_of_students.searchByBnum(strArr[1]) == -1)
                cout << "cant find student" << endl;
            else if(list_of_courses.searchByCRN(strArr[2]) == -1)
                cout << "cant find course" << endl;
            else{
                if(list_of_students.findStudent(strArr[1])->searchCourse(strArr[2]))//if true, student is already enrolled in course
                    cout << "Fail: cannot add, student " << strArr[1] << "already enrolled in course " << strArr[2] << endl;
                else{
                    list_of_courses.findCourse(strArr[2])->addStudent(*list_of_students.findStudent(strArr[1]));
                    list_of_students.findStudent(strArr[1])->addCrn(list_of_courses.findCourse(strArr[2])->getCrn());
                    cout << "Success: added student " << strArr[1] << " into course " << strArr[2] << endl;
                }
            }
        }
        else if(strArr[0] == "drop"){
                
            if(list_of_students.searchByBnum(strArr[1]) == -1)
                cout << "cant find student" << endl;
            else if(list_of_courses.searchByCRN(strArr[2]) == -1)
                cout << "cant find course" << endl;
            else{
                if(list_of_students.findStudent(strArr[1])->searchCourse(strArr[2])){//if true, student is already enrolled in course
                    
                    list_of_courses.findCourse(strArr[2])->removeStudent(*list_of_students.findStudent(strArr[1]));
                    list_of_students.findStudent(strArr[1])->removeCrn(list_of_courses.findCourse(strArr[2])->getCrn());
                    cout << "Success: removed student " << strArr[1] << " from course " << strArr[2] << endl;
                }
                else
                    cout << "Fail: cannot drop, student " << strArr[1] << " not enrolled in course " << strArr[2] << endl;
                
            }
        }
        else if(strArr[0] == "roster"){
                
            if(list_of_courses.searchByCRN(strArr[1]) == -1)
                cout << "couldnt find course" << endl;
            else{
                cout << "CRN: " << strArr[1] << endl;
                list_of_courses.findCourse(strArr[1])->showStudents();
            }

            
        }
        else if(strArr[0] == "schedule"){
                
            if(list_of_students.searchByBnum(strArr[1]) == -1)
                cout << "couldnt find course" << endl;
            else{
                cout << "Student: " << strArr[1] << " " << list_of_students.findStudent(strArr[1])->getName() << " " << list_of_students.findStudent(strArr[1])->getSurname() << endl;
                //get list of CRNs from student object
                string *crns = list_of_students.findStudent(strArr[1])->getCrns();
                int size = (int)sizeof(crns)/sizeof(crns[0]);
                for(int i=0; i<size;i++){
                    cout << list_of_courses.findCourse(crns[i])->getCrn() << list_of_courses.findCourse(crns[i])->getCdep() << list_of_courses.findCourse(crns[i])->getCnum() << list_of_courses.findCourse(crns[i])->getCname() << endl;
                }
                delete[] crns;
            }
        }
        else if(strArr[0] == "\t"){
            cout << "Invalid command, try again" << endl;
        }
        else{//unrecognized command
            cout << "Invalid command, try again" << endl;
        }
        
        strArr.clear();
        showPrompt();
    }

}