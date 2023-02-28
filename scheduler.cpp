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

    vector<string> cmdLine; //vector to hold commands and params
    string userInput;
    string token; //individual command to be pushed into the vector
    Courselist list_of_courses; //obj to represent "global" registry of courses
    Studentlist list_of_students; //obj to represent "global" registry of students
    string fullname; //only used if the name is more than one word

    showPrompt();

    while(getline(cin, userInput)){ //loop to continually ask for command and paramters 

        stringstream ss(userInput); //string stream object to pass thru as our source string

        while (getline(ss, token, ' ')){ //loop thru command and parameters
            if(!token.empty())
                cmdLine.push_back(token); //command = cmdLine[0], parameters in cmdLine[i]
        }
        if(cmdLine.empty()){//empty line clause
            showPrompt();
            continue;
        }  
        else if(cmdLine[0] == "quit")
            break; //command to break out of 'menu'

        else if(cmdLine[0] == "build"){

            if(!regex_match(cmdLine[1], regex("[0-9]{6}"))) //check crn
                cout << "Input Error: illegal CRN" << endl;
            else if(!regex_match(cmdLine[2], regex("[A-Z]{2,4}"))) //check department
                cout << "Input Error: illegal department" << endl;
            else if(!((stoi(cmdLine[3]) >= 100) && (stoi(cmdLine[3]) <= 700)))//check number
                cout << "Input Error: illegal number" << endl; 
            else if(!regex_match(cmdLine[4], regex("(.*?)")))//check name
                cout << "Input Error: illegal name" << endl;
            else{ 
                
                string fullcourseName;
                for(int i = 4; i < (int)cmdLine.size(); i++){
                        fullcourseName += cmdLine[i];
                        if (i != (int)cmdLine.size() - 1)
                            fullcourseName += " "; 
                }
                cout << fullcourseName << endl;
                cmdLine[4] = fullcourseName;
                cout << cmdLine[4] << endl;
                Course course(cmdLine[1], cmdLine[3], cmdLine[4], cmdLine[2]);
                if(list_of_courses.searchByCRN(course.getCrn()) == -1){ // if this returns -1 then course not in courselist
                    //add the course
                    list_of_courses.addCourse(course);
                    cout << "Success: built course ";
                    cout << cmdLine[1] << " " << cmdLine[2] << cmdLine[3];
                    cout << " (CRN: " << cmdLine[3] << ") : ";
                    cout << cmdLine[4] << " " << endl;
                }
                else
                    cout << "Fail: cannot build course " << cmdLine[2] << cmdLine[3] << "(CRN: " << cmdLine[1] << "): CRN exists" << endl;
                     
            }

        }
        else if(cmdLine[0] == "cancel"){
            
            if(!regex_match(cmdLine[1], regex("[0-9]{6}"))) //check crn first
                cout << "Input Error: illegal CRN" << endl;
            //find course in list of courses, then remove it
            if(cmdLine.size() > 2)
                cout << "Warning: ignoring extra argument(s)" << endl;
            if(list_of_courses.searchByCRN(cmdLine[1]) == -1)
                cout << "Fail: cannot cancel course, CRN does not exist" << cmdLine[1] << endl;
            else{
                int index = list_of_courses.searchByCRN(cmdLine[1]);

                list_of_courses.removeCourse(index);
                cout << "Success: cancelled course " << cmdLine[1] << endl;
            }
        }
        else if(cmdLine[0] == "enroll"){
            

            //Error checking
            if(cmdLine.size() < 5)
                cout << "Input Error: too few arguments" << endl;
            if(!regex_match(cmdLine[1], regex("B[0-9]{8}")))
                cout << "Input Error: illegal B number" << endl;
            else if(!regex_match(cmdLine[2], regex("^[a-zA-Z][a-zA-Z0-9]+")))
                cout << "Input Error: illegal userid" << endl;
            else if(!regex_match(cmdLine[3], regex("[a-zA-Z]+")))
                cout << "Input Error: illegal first name" << endl;
            else if(!regex_match(cmdLine[4], regex("[a-zA-Z]+")))
                cout << "Input Error: illegal last name" << endl;
            else{
                Student student(cmdLine[1], cmdLine[2], cmdLine[3], cmdLine[4]);
                if(list_of_students.searchByBnum(student.getBnum()) == -1){
                    list_of_students.addStudent(student);
                    cout << "Success: enrolled student " << cmdLine[1] << " (" << cmdLine[2] << ") " << cmdLine[4] << ", " << cmdLine[3] << endl;
                }
                else 
                    cout << "Fail: cannot enroll student, B Number exists" << endl;
            }
        }
        else if(cmdLine[0] == "add"){

            //Error checking
            if(!regex_match(cmdLine[1], regex("B[0-9]{8}")))
                cout << "Input Error: illegal B number" << endl;
            else if(!regex_match(cmdLine[2], regex("[0-9]{6}")))
                cout << "Input Error: illegal CRN" << endl;

            if(list_of_students.searchByBnum(cmdLine[1]) == -1)
                cout << "cant find student" << endl;
            else if(list_of_courses.searchByCRN(cmdLine[2]) == -1)
                cout << "cant find course" << endl;
            else{
                if(list_of_students.findStudent(cmdLine[1])->searchCourse(cmdLine[2]))//if true, student is already enrolled in course
                    cout << "Fail: cannot add, student " << cmdLine[1] << "already enrolled in course " << cmdLine[2] << endl;
                else{
                    list_of_courses.findCourse(cmdLine[2])->addStudent(*list_of_students.findStudent(cmdLine[1]));
                    list_of_students.findStudent(cmdLine[1])->addCrn(list_of_courses.findCourse(cmdLine[2])->getCrn());
                    cout << "Success: added student " << cmdLine[1] << " into course " << cmdLine[2] << endl;
                }
            }
        }
        else if(cmdLine[0] == "drop"){
            
            //Error checking
            if(!regex_match(cmdLine[1], regex("B[0-9]{8}")))
                cout << "Input Error: illegal B number" << endl;
            else if(!regex_match(cmdLine[2], regex("[0-9]{6}")))
                cout << "Input Error: illegal CRN" << endl;

            if(list_of_students.searchByBnum(cmdLine[1]) == -1)
                cout << "cant find student" << endl;
            else if(list_of_courses.searchByCRN(cmdLine[2]) == -1)
                cout << "cant find course" << endl;
            else{
                if(list_of_students.findStudent(cmdLine[1])->searchCourse(cmdLine[2])){//if true, student is enrolled in course
                    
                    list_of_courses.findCourse(cmdLine[2])->removeStudent(*list_of_students.findStudent(cmdLine[1]));
                    list_of_students.findStudent(cmdLine[1])->removeCrn(list_of_courses.findCourse(cmdLine[2])->getCrn());
                    cout << "Success: removed student " << cmdLine[1] << " from course " << cmdLine[2] << endl;
                }
                else
                    cout << "Fail: cannot drop, student " << cmdLine[1] << " not enrolled in course " << cmdLine[2] << endl;
                
            }
        }
        else if(cmdLine[0] == "roster"){
                
            //Error checking
            if(!regex_match(cmdLine[1], regex("[0-9]{6}")))
                cout << "Input Error: illegal CRN" << endl;
            else if(list_of_courses.searchByCRN(cmdLine[1]) == -1)
                cout << "couldnt find course" << endl;
            else{
                cout << "CRN: " << cmdLine[1] << endl;
                list_of_courses.findCourse(cmdLine[1])->showStudents();
            }

            /*display list_of_courses
               display *list_of_courses.courselist
                display *list_of_courses.courselist.students
                display list_of_students
                display *list_of_students.studentlist
                display *list_of_students.studentlist.crns*/
        }
        else if(cmdLine[0] == "schedule"){
            
            //Error checking
            if(!regex_match(cmdLine[1], regex("B[0-9]{8}")))
                cout << "Input Error: illegal B number" << endl;
            else if(list_of_students.searchByBnum(cmdLine[1]) == -1)
                cout << "couldnt find course" << endl;
            else{
                cout << "Student: " << cmdLine[1] << " " << list_of_students.findStudent(cmdLine[1])->getName() << " " << list_of_students.findStudent(cmdLine[1])->getSurname() << endl;
                //get list of CRNs from student object
                string *crns = list_of_students.findStudent(cmdLine[1])->getCrns();
                int size = list_of_students.findStudent(cmdLine[1])->getSize();
                for(int i=0; i<size;i++){
                    if(list_of_courses.findCourse(crns[i]) != nullptr)
                        cout << list_of_courses.findCourse(crns[i])->getCrn() << " " << list_of_courses.findCourse(crns[i])->getCdep() << " " << list_of_courses.findCourse(crns[i])->getCnum() << " " << list_of_courses.findCourse(crns[i])->getCname() << endl;
                }
                delete[] crns;
            }
        }
        else{//unrecognized command
            cout << "Invalid command, try again" << endl;
        }
        
        cmdLine.clear();
        showPrompt();
    }

}