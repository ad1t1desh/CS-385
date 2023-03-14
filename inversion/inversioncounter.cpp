/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Aditi Deshmukh
 * Version     : 1.0
 * Date        : 11/2/2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count = 0; 
    for (int i = 0; i < length - 1; i++){
        for (int j = i+1; j < length; j++){
            if (array[j] < array[i]){
                count++; 
            }
        }

    }
    return count; 
}

//long int inversions = 0; //is it ok

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // Hint: Use mergesort!
    int *scratch = new int[length]; 
    int low = 0; 
    int high = length-1; 
    long inversions = mergesort(array, scratch, low, high);
    delete[] scratch; 
    return inversions; 
    
}

long merge(int array[], int scratch[], int low, int mid, int high){
    int i1 = low; 
    int i2 = mid; 
    int i = low; 
    long inversions = 0; 
    while(i1 <= mid-1 && i2 <= high){
        if (array[i1] <= array[i2]){
            scratch[i++] = array[i1++];
        } else {
            scratch[i++] = array[i2++];
            //increment inversion counter 
            inversions += (mid-i1); 
        }
    }
    while (i1 <= mid-1){ // may have to change to while
        scratch[i++] = array[i1++];
    }
    while (i2 <= high){ // may have to chnage to while 
        scratch[i++] = array[i2++]; 
    }
    //copy back into array
    for (int j = low; j<= high; j++){
        array[j] = scratch[j]; 
    }// rteurn inversion count 
    return inversions; 
    //return 1; 
} 

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long inversions = 0; 
    int mid = low + (high -low)/2; 
    if (low < high){
        inversions = mergesort(array, scratch, low, mid);
        inversions += mergesort(array, scratch, mid + 1, high);
        inversions += merge(array, scratch, low, mid + 1, high); 
    }//return inversion count
    return inversions; 
} 


int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    //istringstream ss; 
    if (argc >= 3) {
		cerr << "Usage: ./inversioncounter [slow]";
		return 1;
	}
	if ((argv[1] != NULL) && (strcmp(argv[1], "slow"))){
		cerr << "Error: Unrecognized option '" << argv[1] << "'.";
		return 1;
	}
    /*
    if (argv[1] != NULL && (strcmp(argv[1], ""))) {
		cerr << "Error: Unrecognized option *'" << argv[1] << "'."; 
		return 1;
	}*/


    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output
    //if slow else fast
    //if (strcmp(argv[1], "slow")){

    if (values.size() == 0){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    if (argc == 2){
        cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    } else {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl; 
    }

    return 0;
}
