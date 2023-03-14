/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Aditi Deshmukh and Lilli Nappi
 * Version : 1.0
 * Date    : 12/7/2022
 * Description : Finds shortest paths using the Floyd algorithm. 
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>  
#include <climits>  // initialize LONG_MAX

using namespace std;

// Declare infinity
long INF = LONG_MAX;


int len(long x) {
	x /= 10;
	int length = 1;
	while (x>0) {
		x /= 10;
		length++;
	}
	return length;
}

void display_table(long** const matrix, const string &label,
		const bool use_letters, int num_vertices) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}

	int max_cell_width = use_letters ? len(max_val) :
			len(max(static_cast<long>(num_vertices),max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for(int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if(matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

string backtrack(long** const matrix, int i, int j) {
	string result = "";
	if (matrix[i][j] == INF) {
		result = result + static_cast<char>(i + 'A');
		result = result + static_cast<char>(j + 'A');
		return result;
	} else {
		result = result + backtrack(matrix,i,matrix[i][j]);
		result = result + backtrack(matrix,matrix[i][j],j).substr(1);
		return result;
	}
}

struct rline {
	string start, end, distance;
	rline() :
			start(""), end(""), distance("") {
	}
	rline(string _start, string _end, string _distance) :
			start(_start), end(_end), distance(_distance) {
	}
};

int main(int argc, char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
	// Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
	istringstream iss;
	int num_vertices; // number of vertices
	string line;	  // string line read from file
	string str;	      // used to check if it is string
	unsigned int line_number = 1;
	getline(input_file, line);
			iss.str(line);
			if (!(iss >> num_vertices)) {
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
				return 1;
			}
			num_vertices = stoi(line); // number of edges is first line
			if (num_vertices >= 27 || num_vertices <= 0 ) {
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
				return 1;
			}

	// Declare edge and matrix
	rline l = rline();
	long** OGmatrix = new long*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		OGmatrix[i] = new long[num_vertices];
		fill(OGmatrix[i], OGmatrix[i] + num_vertices, INF);
		OGmatrix[i][i] = 0;
	}

	int distance;
	if (argc == 2)
	while (getline(input_file, line)) {
		line_number++;
		iss.clear();
		iss.str(line);
		if (!(iss >> str)) {
			cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
			// Delete Matrix			
			for (int i = 0; i <= num_vertices-1; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;
			return 1;
		}
		l.start = str;
		if (!(iss >> str)) {
			cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
			// Delete Matrix			
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}
		l.end = str;
		if (!(iss >> str)) {
			cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
			// Delete Matrix			
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}
		l.distance = str;
		if ((iss >> str)) {
			cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "." << endl;
			// Delete Matrix			
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}
		if ((l.start[0] < 65 || l.start[0] > (num_vertices + 64))){
			cerr << "Error: Starting vertex '" << l.start << "' on line " << line_number << " is not among valid values A-" << char(64 + num_vertices) << "." << endl;
			// Delete Matrix			
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;

		}
		if (l.start.length() > 1) {
			cerr << "Error: Starting vertex '" << l.start << "' on line " << line_number << " is not among valid values A-" << char(64 + num_vertices) << "." << endl;
			// Delete Matrix			
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}
		

		if ((l.end[0] < 65 || l.end[0] > (num_vertices + 64))) {
			cerr << "Error: Ending vertex '" << l.end << "' on line " << line_number << " is not among valid values A-" << char(64 + num_vertices) << "." << endl;
			// Delete Matrix
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}

		if (l.end.length() > 1) {
			cerr << "Error: Ending vertex '" << l.end << "' on line " << line_number << " is not among valid values A-" << char(64 + num_vertices) << "." << endl;
			// Delete Matrix
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}

		/*
		iss.str(l.distance); 
		int check; 
		
		if (!(iss >> check)){ {
			cerr << "Error: Invalid edge weight '" << l.distance << "' on line " << line_number << "." << endl;
			// Delete Matrix
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}
		distance = stol(l.distance);

		if (distance < 1) {
			cerr << "Error: Invalid edge weight '" << l.distance << "' on line " << line_number << "." << endl;
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
			}
			delete[] OGmatrix;			
			return 1;
		}

		// Place edge in matrix.
		OGmatrix[static_cast<int>(l.start[0]-'A')][static_cast<int>(l.end[0]-'A')] = distance;
	}
	*/
	try {
		distance = stol(l.distance); 
		if (distance < 1){throw invalid_argument("Invalid edge weight");}
	}
	catch (...){
		cerr << "Error: Invalid edge weight '" << l.distance << "' on line " << line_number << "." << endl;
			for (int i = 0; i < num_vertices; i++) {
				delete[] OGmatrix[i];
		}
			delete[] OGmatrix;			
			return 1;
	}

		// Place edge in matrix.
		OGmatrix[static_cast<int>(l.start[0]-'A')][static_cast<int>(l.end[0]-'A')] = distance;
	}

	// Make sure to close file
	input_file.close();

	// Initialize Path Matrix
	long** PMatrix = new long*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		PMatrix[i] = new long[num_vertices];
		for (int j = 0; j < num_vertices; j++) {
			PMatrix[i][j] = OGmatrix[i][j];
		}
	}

	// Initialize Intermediate Matrix
	long** Imatrix = new long*[num_vertices];
	for (int i = 0; i < num_vertices; i++) {
		Imatrix[i] = new long[num_vertices];
		fill(Imatrix[i], Imatrix[i] + num_vertices, INF);
		}

	// Display Distance Matrix
	display_table(OGmatrix, "Distance matrix:", false, num_vertices);

	// Floyd's Algorithm
	for(int k = 0; k < num_vertices; k ++) {
		// Intermediate Vertices
		for(int i = 0; i < num_vertices; i++) {
			// Destination for k
			for(int j = 0; j < num_vertices; j++) {
				// If k is shortest path from i to j then update path matrix[i][j]
				if(k != i && k != j && i != j && PMatrix[k][j] != INF && PMatrix[i][k] != INF) {
						if(PMatrix[i][j] > PMatrix[i][k] + PMatrix[k][j]) {
							PMatrix[i][j] = PMatrix[i][k] + PMatrix[k][j];
							Imatrix[i][j] = k; // k is intermediate vertex
						}
				}
			}
		}
	}

	// Display Path Matrix
	display_table(PMatrix, "Path lengths:", false, num_vertices);

	// Display Intermediate Matrix
	display_table(Imatrix, "Intermediate vertices:", true, num_vertices);
	
	// Display Backtracked Solution
	string result = "";
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			result = "";
			if (PMatrix[i][j] == INF && i != j) {
				cout << static_cast<char> (i + 65) << " -> " << static_cast<char> (j + 65) << ", distance: infinity, path: none" << endl;
			} else if (i == j) {
				cout << static_cast<char> (i + 65) << " -> " << static_cast<char> (j + 65) << ", distance: " << PMatrix[i][j] << ", path: " << (result = static_cast<char> (i + 65)) << endl;
			} else {
				result = backtrack(Imatrix, i, j);
				cout << static_cast<char> (i + 65) << " -> " << static_cast<char> (j + 65) << ", distance: " << PMatrix[i][j] << ", path: " << result[0];
				for(unsigned int k = 1; k < result.length(); k++) {
					cout << " -> " << result[k];
				}
				cout << endl;
			}
		}
	}

	// Delete Matrixes
	for (int i = 0; i < num_vertices; i++) {
		delete[] OGmatrix[i];
		}
		delete[] OGmatrix;	

	for (int i = 0; i < num_vertices; i++) {
		delete[] PMatrix[i];
		}
		delete[] PMatrix;	

	for (int i = 0; i < num_vertices; i++) {
		delete[] Imatrix[i];
		}
		delete[] Imatrix;	
	return 0;
}
