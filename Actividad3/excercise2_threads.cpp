// =================================================================
//
// File: exercise02.cpp
// Author(s): Sofía Blanco Prigmore and Antonio Miranda Baños 
// Description: This file contains the code to brute-force all
//				prime numbers less than MAXIMUM. The time this
//				implementation takes will be used as the basis to
//				calculate the improvement obtained with parallel
//				technologies.
//
// Copyright (c) 2023 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <pthread.h>
#include "utils.h"
#include <cmath>

using namespace std;
using namespace std::chrono;

#define MAXIMUM 20 //5000000 //5e6
#define MAXTHREADS 8 

typedef struct {
	double sum; 
	int start, end; 
} Block; 

// implement your code

//SECUENTIAL CODE 
/* 
long long primeNumberSum(int max){
    long long sum = 0; 
    for(int i=2; i<=max;i++){
        if(prime(i)){
            sum +=i; 
        }
    }
    return sum; 
}
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

void* primeNumberSum(void* param){
	Block *block; 
	block = (Block*) param; 

	double sum = 0; 
	for (int i = block->start; i< block->end; i++){
		if(prime(i)){
			sum += i; 
		}
	}
	block->sum = sum; 
	return 0; 
}


int main(int argc, char* argv[]) {
	double result;
	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	int blockSize;
	Block blocks[MAXTHREADS];
	pthread_t threads[MAXTHREADS];

	// Divides range / threads 
	blockSize = MAXIMUM / MAXTHREADS; 
	for (int i = 0; i< MAXTHREADS; i++){
		blocks[i].start = i * blockSize;
		blocks[i].end = (i == MAXTHREADS -1) ? MAXIMUM : (i+1) * blockSize; 
	}

	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();

		// call the implemented function
		for (int i=0; i < MAXTHREADS; i++){
			pthread_create(&threads[i], NULL, primeNumberSum, &blocks[i]); 
		}

		result = 0;
		for (int i = 0; i < MAXTHREADS; i++){
			pthread_join(threads[i], NULL); 
			result += blocks[i].sum; 
			//cout << result << "\n";
		}

		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}
	cout << "result = " << fixed << setprecision(0) << result << "\n";
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	return 0;
}