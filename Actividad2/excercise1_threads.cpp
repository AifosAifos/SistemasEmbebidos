// =================================================================
//
// File: exercise01.cpp
// Author(s): Sofía Blanco Prigmore
// Description: This file contains the code to count the number of
//				even numbers within an array. The time this implementation
//				takes will be used as the basis to calculate the
//				improvement obtained with parallel technologies.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstring>
#include <climits>
#include <pthread.h>
#include "utils.h"

using namespace std;
using namespace std::chrono;

// array size
#define SIZE 1000000000
#define MAXTHREADS 8 

// SECUENTIAL version
/*int addEvenElements(int *array, int size){
    int sum = 0; 
    for(int i=0; i<size; i++){
        if(array[i]%2==0){
            sum +=array[i]; 
        }
    }
    return sum; 
}*/

// implement your code
typedef struct {
	int *array; //modificar este 
	double result;
	int start, end; 

} Block; 

void* addEvenElements(void *param){
	Block *block; 
	double sum = 0; 

	block = (Block*) param; 
	for(int i = block->start; i < block->end; i++){
		if(block->array[i]%2 == 0){
			sum += block->array[i]; 
		} 
	}
	block->result = sum;
	return 0; 
}


int main(int argc, char* argv[]) {
	int *array;
	double result; 
	// These variables are used to keep track of the execution time.
	high_resolution_clock::time_point start, end;
	double timeElapsed;

	int blockSize; 
	Block blocks[MAXTHREADS]; 
	pthread_t threads[MAXTHREADS]; 

	array = new int[SIZE];
	fill_array(array, SIZE);
	display_array("array", array);

	//block de blocksize
	blockSize = SIZE / MAXTHREADS; 
	for (int i = 0; i < MAXTHREADS; i++) {
		blocks[i].array = array;
		blocks[i].result = INT_MAX;
		blocks[i].start = (i * blockSize);
		blocks[i].end = (i != (MAXTHREADS - 1))? ((i + 1) * blockSize) : SIZE;
	}

	//starting clock 
	cout << "Starting...\n";
	timeElapsed = 0;
	for (int j = 0; j < N; j++) {
		start = high_resolution_clock::now();

		// call the implemented function
		for (int i=0; i < MAXTHREADS; i++){
			pthread_create(&threads[i], NULL, addEvenElements, (void*) &blocks[i]); 
		}

		result = 0; 
		for (int i = 0; i < MAXTHREADS; i++){
			pthread_join(threads[i], NULL); 
			result += blocks[i].result; 
		} 

		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}
	cout << "result = " << fixed << setprecision(0) << result << "\n";
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	delete [] array;
	return 0;
}
