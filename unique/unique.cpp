/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Aditi Deshmukh
 * Date        : 9/25/2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for (unsigned int i = 0; i < s.length(); i++){
        //loop continues running until it finds a character that is not a lowercase letter
            if (islower(s[i])){ 
                continue; 
            } else {
                return false; 
            }
    }
    return true; 
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
    if(is_all_lowercase(s)){
    unsigned int store = 0; //creates a number to store the value
    for (unsigned int i = 0; i< s.length(); i++){
        int asconv = s[i] -97; //number of places to shift
        unsigned int store1 = store >> asconv; //another unsigned int created as to not modify store
        if (store1 & 1){ 
            return false; //duplicate found - there is already a 1 in that position
        } else {
            store |= 1 << asconv; //add a 1 into store to record that a specific letter has been seen
            store1 = 0; //reset store1
        }
    }
    return true; 
    }
    return false;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if (!argv){
        cerr << "Usage: ./unique <string>" << endl; 
    }
    else if (argc > 2 || argc<2){
        cerr << "Usage: ./unique <string>" << endl; 
    }
    else if (!(is_all_lowercase(argv[1]))){
        cerr <<"Error: String must contain only lowercase letters." << endl; 
    } else if (all_unique_letters(argv[1])){
        cout<< "All letters are unique." << endl; 
    } else {
        cout<< "Duplicate letters found." <<endl;
    }
    return 0; 
} 
