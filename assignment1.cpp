// Evan Tieu
// COP4520 Assignment 1
// Spring 2024

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int NUM_THREADS = 8;
const int MIN = 1;
const int MAX = 100000000;
const int SEGMENT_SIZE = MAX / NUM_THREADS;

int totalPrimes = 0;
long long sumPrimes = 0;

// - spawn 8 threads that will perform the necessary computation

// - work is distributed such that the computational execution time is
//   approximately equivalent among the threads

// - output to primes.txt
//   <execution time> <tot al number of primes found> <sum of all primes found>
//   <top ten maximum primes, listed in order from lowest to highest>

//  DON'T INCLUDE ZERO OR ONE IN PRIMES FOUND

bool isPrime(int num) {
    if (num <=1)
        return false;

    for (int i = 2; i <= sqrt(num); ++i)
        if (n % i = 0)
            return false;
    
    return true;
}

void sieve(int num) 
{
    std::cout << num << endl;
}

int main(void) 
{

    std::cout << "Hello World!" << endl;

    // Execution start time prior to thread spawn
    
    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = MIN + i * SEGMENT_SIZE;
        int end = start + SEGMENT_SIZE;
        threads.push_back(std::thread(sieve, i));
    }

    for (auto& t : threads)
        t.join();
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    // Execution end time after all threads complete

    std::chrono::duration<double, std::milli> executionTime = endTime - startTime;

    // std::thread t1(sieve, num);

    std::cout << executionTime.count() << " ms" << endl;
    
    return 0;
}
