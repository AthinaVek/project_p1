#include <iostream>
#include <vector>
#include <random>

#include "help_functions.h"

int reverseInt (int i){
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void read_inputLSH(int* argc, char** argv, string* iFile, string* qFile, int* k, int* L, string* oFile, int* N, double* R, double* w){
	
	if(*argc == 15){                                          // Read input
		for (int i = 1; i < 15; ++i){
			if (string(argv[i]) == "-d"){
				*iFile = argv[i+1];
			}
			else if (string(argv[i]) == "-q"){
				*qFile = argv[i+1];
			}
			else if (string(argv[i]) == "-k"){
				*k = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-L"){
				*L = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-o"){
				*oFile = argv[i+1];
			}
			else if (string(argv[i]) == "-N"){
				*N = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-R"){
				*R = atof(argv[i+1]);
			}
		}
	}
	else{
		cout << "No right input given. Using default values." << endl << endl;

		*iFile = "train-images-idx3-ubyte";                   //default values if not given by user
		*qFile = "t10k-images-idx3-ubyte";
		*oFile = "lsh_results.txt";
		
		*k = 4;				
		*L = 5;
		*N = 1;
		*R = 10000;
	}
	
	*w = 4 * (*R);
	
}

void read_data(ifstream &file, int* magic_number, int* number_of_images, int* n_rows, int* n_cols, vector< vector<unsigned char> >& vec, vector<unsigned char>& tempVec){
	
	file.read((char*)magic_number,sizeof(*magic_number));    // read values from file
	*magic_number = reverseInt(*magic_number);
	file.read((char*)number_of_images,sizeof(*number_of_images));
	*number_of_images = reverseInt(*number_of_images);
	file.read((char*)n_rows,sizeof(*n_rows));
	*n_rows = reverseInt(*n_rows);
	file.read((char*)n_cols,sizeof(*n_cols));
	*n_cols = reverseInt(*n_cols);
	
	for(int i = 0; i < *number_of_images; i++){             // read image
		for(int r = 0; r < *n_rows; r++){
			for(int c = 0; c < *n_cols; c++){
				unsigned char temp = 0;
				file.read((char*)&temp,sizeof(temp));

				tempVec.push_back(temp);
			}
		}
		vec.push_back(tempVec);                           // save vector of pixels for every image
		tempVec.erase(tempVec.begin(), tempVec.end());
	}
	
}


void read_inputCube(int* argc, char** argv, string* iFile, string* qFile, int* k, int* M, int* probes, string* oFile, int* N, double* R, double* w){
	
	if(*argc == 17){                                          // Read input
		for (int i = 1; i < 17; ++i){
			if (string(argv[i]) == "-d"){
				*iFile = argv[i+1];
			}
			else if (string(argv[i]) == "-q"){
				*qFile = argv[i+1];
			}
			else if (string(argv[i]) == "-k"){
				*k = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-M"){
				*M = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-probes"){
				*probes = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-o"){
				*oFile = argv[i+1];
			}
			else if (string(argv[i]) == "-N"){
				*N = atoi(argv[i+1]);
			}
			else if (string(argv[i]) == "-R"){
				*R = atof(argv[i+1]);
			}
		}
	}
	else{
		cout << "No right input given. Using default values." << endl << endl;

		*iFile = "train-images-idx3-ubyte";                   //default values if not given by user
		*qFile = "t10k-images-idx3-ubyte";
		*oFile = "cube_results.txt";
		
		*k = 14;				
		*M = 10;
		*probes = 2;
		*N = 1;
		*R = 10000;
	}
	
	*w = 4 * (*R);
	
}

// void printNestedList(list<list<unsigned char> > nested_list) 
// { 
//     cout << "[\n"; 
  
//     // nested_list`s iterator(same type as nested_list) 
//     // to iterate the nested_list 
//     list<list<unsigned char> >::iterator nested_list_itr; 
  
//     // Print the nested_list 
//     for (nested_list_itr = nested_list.begin(); 
//          nested_list_itr != nested_list.end(); 
//          ++nested_list_itr) { 
  
//         cout << "  ["; 
  
//         // normal_list`s iterator(same type as temp_list) 
//         // to iterate the normal_list 
//         list<unsigned char>::iterator single_list_itr; 
  
//         // pointer of each list one by one in nested list 
//         // as loop goes on 
//         list<unsigned char>& single_list_pointer = *nested_list_itr; 
  
//         for (single_list_itr = single_list_pointer.begin(); 
//              single_list_itr != single_list_pointer.end(); 
//              single_list_itr++) { 
//             cout << " " << *single_list_itr << " "; 
//         } 
//         cout << "]\n"; 
//     } 
//     cout << "]"; 
// } 
