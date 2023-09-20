// =================================================================
//
// File: exercise02.cpp
// Author(s):Sofía Blanco Prigmore 
//            A01704567 
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
#include "utils.h"


using namespace std;
using namespace std::chrono;

#define MAXIMUM 5000000 //5e6

// implement your code
bool prime(int num){
    if(num<2){
        return false; 
    }
    if(num<=3){
        return true; 
    }
    if(num%2==0 || num%3==0){
        return false; 
    }
    for(int i=5;i*i<=num;i=i+6){
        if(num%i==0 || num%(i+2)==0){
            return false; 
        }
    }
    return true; 
}

long long primeNumberSum(int max){
    long long sum = 0; 
    for(int i=2; i<=max;i++){
        if(prime(i)){
            sum +=i; 
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

		result = primeNumberSum(MAXIMUM);

		end = high_resolution_clock::now();
		timeElapsed += 
			duration<double, std::milli>(end - start).count();
	}
	cout << "result = " << result << "\n";
	cout << "avg time = " << fixed << setprecision(3) 
		 << (timeElapsed / N) <<  " ms\n";

	return 0;
}