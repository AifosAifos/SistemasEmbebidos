// =================================================================
//
// File: exercise03.cpp
// Author(s): Sofía Blanco Prigmore and Antonio Miranda Baños 
// Description: This file contains the code that implements the
//				enumeration sort algorithm. The time this 
//				implementation takes ill be used as the basis to 
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
#include <cstring>
#include <pthread.h>
#include "utils.h"

using namespace std;
using namespace std::chrono;

#define SIZE 10000
#define MAXTHREADS 8 

typedef struct {
	int *origin, *copy; 
	int start, end; 
} Block; 

// implement your code
void* enumerationSort(void *param){
	Block *block; 
	block = (Block*) param; 
	
	int cont = 0; 

	for (int i = block->start; i < block->end; i++){
		/*for (int j = block->start; j < block->end; j++) {
            if (block->copy[i] > block->copy[j] || (block->copy[i] == block->copy[j] && j < i)) {
                cont++;
            }
        }
		block->copy[cont] = block->copy[i]; */
		int *b = new int[SIZE]; 
		for (int i=0; i<SIZE; i++){
			b[i] = 0; 
		}
		

		for (int i=0; i<SIZE; i++){
			int cont = 0; 
			for (int j=0; j<SIZE; j++){
				//establish conditions for duplicated elements
				if(block->copy[i] > block->copy[j] || (block->copy[i]==block->copy[j] && j<i)){
					cont++; 
				}
			}
			b[cont] = block->copy[i]; //copies element in correct pos
		}
		for (int i = 0; i <SIZE; i++){
			block->copy[i] = b[i]; //copies sorted array into original array
		}
		delete[] b; // b no longer necessary
	
	}
		return 0; 	
}


int main(int argc, char* argv[]) {
	int *origin, *copy; 
	double result;
	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	int blockSize;
	Block blocks[MAXTHREADS];
	pthread_t threads[MAXTHREADS];

	origin = new int[SIZE];
	random_array(origin, SIZE);
	display_array("before", origin);

	copy = new int[SIZE];

	// Divides range of blocks 
	blockSize = SIZE / MAXTHREADS; 
	for (int i = 0; i < MAXTHREADS; i++) {
		blocks[i].origin = origin;
		blocks[i].copy = copy;
		//blocks[i].result = result; 
		blocks[i].start = (i * blockSize);
		blocks[i].end = (i != (MAXTHREADS - 1))? ((i + 1) * blockSize) : SIZE;
	}

	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		memcpy(copy, origin, SIZE * sizeof(int));

		start = high_resolution_clock::now();

		// call the implemented function
		for (int i=0; i < MAXTHREADS; i++){
			pthread_create(&threads[i], NULL, enumerationSort, &blocks[i]); 
		}

		//result = 0; 
		for (int i = 0; i < MAXTHREADS; i++){
			pthread_join(threads[i], NULL); 
			//result += blocks[i].result; 

		} 

		// use the "copy" array to do the sorting.
		for(int i=0; i < SIZE; i++){
			origin[i] = copy[i]; 
		}

		end = high_resolution_clock::now();
		timeElapsed += duration<double, std::milli>(end - start).count();
	}
	display_array("after", copy);
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	delete [] origin;
	delete [] copy;
	
	return 0;
}