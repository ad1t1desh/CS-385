/****************************************************************************************
 * Filename : sqrt.cpp
 * Author : Aditi Deshmukh
 * Version : 1.0
 * Date : 9/8/22
 * Description : Lab 1 Square Root Program
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System. 
 *******************************************************************************************/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits> 
using namespace std; 

double sqrt(double num, double epsilon){
    if (num < 0){
        return numeric_limits<double>::quiet_NaN();
    }
    if (num == 0){
        return num;
    }
    if(num == 1){
        return num;
    } else {
        double n; //next guess 
        double l; //last guess
        l = num; 
        while (num){
            n = (l+(num/l))/2;
            if ((abs(l-n)) < epsilon){
                break;
            }
            l=n; 

        }
        return n; 
    }
    }

int main(int argc, char* argv[]){
    double num,epsilon;
    istringstream iss; 
    //use iss to check if double 

    if (argc < 2 || argc >= 4){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if (argc == 2){
        if (!(iss >> num)){
            cerr << "Error: Value argument must be a double." << endl; 
            return 1;
        } else {
        cout.precision(8);
        cout << fixed << sqrt(num, 1e-7) <<endl; 
        }

    }
    if (argc == 3){
        if (!(iss >> num)){
            cerr << "Error: Value argument must be a double." << endl; 
            return 1;
        }
        iss.clear();
        iss.str(argv[2]);
        if (!(iss >> epsilon) || (epsilon <= 0)) {
            cerr << "Error: Epsilon argument must be a positive double." << endl; 
            return 1; 
        } else {
            cout.precision(8);
            cout << fixed << sqrt(num, epsilon) <<endl;
        }
        
    }

    return 0; 
    
    

}