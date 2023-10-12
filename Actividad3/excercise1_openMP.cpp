// =================================================================
//
// File: exercise01.cpp
// Author(s): Sofía Blanco Prigmore 
// Description: This file contains the code to count the number of
//				even numbers within an array using the OpenMP 
//				technology. To compile:
//				g++ -o app -fopenmp exercise01.cpp
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include "utils.h"

using namespace std;
using namespace std::chrono;

// array size
#define SIZE 1000000000 //1e9

/*
avg time secuencial = 3052.545 ms
avg time pthread = 1343.673 ms
avg time openmp = 870.201 ms

SPEED UP = 3.5
*/

int addEvenElements(int *array, int size){
    int sum = 0; 

    #pragma omp parallel for reduction(+:sum)
         for(int i = 0; i<size; i++){
            if(array[i]%2==0){
            sum += array[i]; 
            }
        } 
    return sum; 
}


int main(int argc, char* argv[]) {
	int *array, result;
	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	array = new int[SIZE];
	fill_array(array, SIZE);
	display_array("array", array);

	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();

		// call the implemented function
        result = addEvenElements(array, SIZE); 

		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}
	cout << "result = " << result << "\n";
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	delete [] array;
	return 0;
}