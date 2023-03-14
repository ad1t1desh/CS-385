/****************************************************************************
 * Filename: student.cpp
 * Author  : Aditi Deshmukh
 * Version : 1.0
 * Date    : September 15, 2022
 * Description: kenjwenfjffelewkweEDIT
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System. 
 *****************************************************************************/
#include <iostream> 
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std; 

class Student{
    
    public: 
    Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id}{}


    string full_name() const{
        return first_ + " " + last_;  

    }
    int id() const{
        return id_; 

    }
    float gpa() const{
        return gpa_; 

    }
    void print_info() const{
        cout.precision(2);
        cout << full_name() << ", GPA: " <<fixed<<gpa()<< ", ID: "<< id()<<endl;//set precision 

        
    }

    private: 
    string first_; 
    string last_; 
    float gpa_;
    int id_; 
};

    /**
     * Takes a vector of Student object, and returns a new vector 
     * with all Students whose GPA is < 1.0. 
     */

    vector<Student> find_failing_students(const vector<Student> &students){
        vector<Student> failing_students;
        
        for (auto it = students.begin(); it != students.end(); it++){
            if (it->gpa() < 1.0){
                failing_students.push_back(*it); 
            }
        }
        return failing_students; 
        
    }

        //Iterates through the students vectors, appending each student whose gpa is 
        //less than 1.0 to the failing_students vector. 

    /**
     * Takes a vector of Student objects and prints them to the screen. 
     */
    void print_students(const vector<Student> &students){
        for (auto it = students.begin(); it != students.end(); it++){
            it->print_info(); 
        }
    }


int main(){
    string first_name, last_name; 
    float gpa;
    int id; 
    char repeat; 
    vector<Student> students; 

    do {
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name; 
        gpa = -1;
        while (gpa<0 || gpa>4){
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa; 
        }
        cout << "Enter student's ID: ";
        cin >> id; 
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat; 
    } while (repeat == 'Y' || repeat == 'y');

    cout << endl << "All students:" << endl; 
    print_students(students);

    cout << endl << "Failing students:";
    //TODO
    //Print a space and the word 'None' on the same line if no students are failing.
    //Otherwise, print each failing student on a separate line. 

    if (find_failing_students(students).empty()){
        cout << " None" ; 
    } else {
        cout<<endl; 
        print_students(find_failing_students(students)); 
    }

    return 0; 
}
