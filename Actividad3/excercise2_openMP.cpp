// =================================================================
//
// File: exercise02.cpp
// Author(s): Sofía Blanco Prigmore 
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM using the OpenMP 
//				technology. To compile:
//				g++ -o app -fopenmp exercise02.cpp
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include <cmath>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define MAXIMUM 5000000 //5e6

/*
avg time secuencial = 6950.382 ms
avg time pthread = 1277.313 ms
avg time openmp = 1032.380 ms

SPEED UP: 6.7
*/

//Function to detect prime numbers
bool prime(int num) {
    if (num < 2)
        return false;
 
    // check for all factors
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

double PrimeNumberSum(int size){
    double sum = 0; 
    
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++){
		if(prime(i)){ 
			sum += i; 
		}
	}
	return sum; 
}

int main(int argc, char* argv[]) {
	double result;
	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();

		// call the implemented function
        PrimeNumberSum(MAXIMUM); 

		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}
	cout << "result = " << result << "\n";
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	return 0;
}