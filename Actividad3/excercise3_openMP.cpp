// =================================================================
//
// File: exercise03.cpp
// Author(s): Sofía Blanco Prigmore 
// Description: This file contains the code that implements the
//				enumeration sort algorithm using the OpenMP 
//				technology. To compile:
//				g++ -o app -fopenmp exercise03.cpp
//
// Copyright (c) 2024 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define SIZE 10000

//avg time monohilo = 545.129ms 
//avg time pthreads = 138.873 ms
//avg time openmp = 82.831ms [80-85ms]

// implement your code
void parallel_EnumerationSort(int *array, int size){
    int *b = new int[size]; 

   #pragma omp parallel for
    for (int i = 0; i < size; i++){
        int cont = 0; 
        for(int j = 0; j<size; j++){
            if (array[i] > array[j] || array[i] == array[j] && j<i){
                cont++; 
            }
        }
        b[cont] = array[i]; 
    }
    
    memcpy(array, b, sizeof(int) * size);
    delete[] b; 
}

int main(int argc, char* argv[]) {
	int *origin, *copy, result;
	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	origin = new int[SIZE];
	random_array(origin, SIZE);
	display_array("before", origin);

	copy = new int[SIZE];

	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		memcpy(copy, origin, SIZE * sizeof(int));

		start = high_resolution_clock::now();

		// call the implemented function
        parallel_EnumerationSort(copy,SIZE);
		// use the "copy" array to do the sorting.
        
		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}

	display_array("after", copy);
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	delete [] origin;
	delete [] copy;
	
	return 0;
}