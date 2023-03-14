/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Aditi Deshmukh
 * Date        : October 1 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    if (num_stairs <= 0){
        vector<int> dummy;
        ways.push_back(dummy); 
    } else {
          for (int i =1; i<4; i++){
            if (num_stairs >=i){
              vector<vector<int>> result = get_ways(num_stairs -i);
              //prepending i to all solutions in result:
              for (size_t j = 0; j < result.size(); j++){
                result[j].insert(result[j].begin(), i); // creates the vector result to be appended to ways vector 
              }
                ways.insert(ways.end(),result.begin(),result.end()); //adds result to the end of the end of the ways vector 
            }
          }
      }
          return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    // find  number of digits in the final way, and fill the beginning with spaces 
    if(ways.size() <= 9){ // if there are less than 10 ways 
      for(size_t i = 0; i<ways.size(); i++){
        cout<< i+1 << ". " << "["; 
        for (size_t j = 0; j < ways[i].size(); j++){
          if (j < ways[i].size()-1){
            cout<< ways[i][j] << ", ";
          } else {
            cout<<ways[i][j]; 
          }
        }
        cout << "]"<< endl;
      }
      } else { 
      for(size_t i = 0; i<ways.size(); i++){ // 10 or more ways 
        if (i<9){
          cout << " " << i+1 << ". " << "[";
        } else {
          cout<< i+1 << ". " << "[";
        }
        for (size_t j = 0; j < ways[i].size(); j++){
          if (j < ways[i].size()-1){
            cout<< ways[i][j] << ", ";
          } else {
            cout<<ways[i][j]; 
          }
        }
        cout << "]"<< endl;
    }

}
}

int main(int argc, char * const argv[]) {
  int num_stairs; 
  istringstream iss; 
  //Case 1: No input arguments
  if (argc == 1){
    cerr<< "Usage: ./stairclimber <number of stairs>" << endl; 
    return 1; 
  }
  //Case 2: Too many input arguments 
  if (argc >= 3){
    cerr<< "Usage: ./stairclimber <number of stairs>" << endl; 
    return 1;
  }
  //Case 3: Bad input
  iss.str(argv[1]);
  if (!(iss >> num_stairs)){
    cerr << "Error: Number of stairs must be a positive integer." << endl;
    return 1; 
  }
  iss.clear();
  //Case 4: Bad input
  if(num_stairs < 1){
    cerr << "Error: Number of stairs must be a positive integer." << endl;
    return 1; 
  }
  if (num_stairs == 1){
    cout << get_ways(num_stairs).size() << " way to climb " << num_stairs << " stair." << endl; 
  } else {
  cout << get_ways(num_stairs).size() << " ways to climb " << num_stairs << " stairs." << endl; 
  }
  display_ways(get_ways(num_stairs));
  return 0; 
}
