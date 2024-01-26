// Evan Tieu
// COP4520 Assignment 1
// Spring 2024

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

using namespace std;

const int NUM_THREADS = 8;
const int MIN = 1;
const int MAX = 100000000;
const int SEGMENT_SIZE = (MAX - MIN + 1) / NUM_THREADS;

int totalPrimes = 0;
long long sumPrimes = 0;

// Calculates if a given number is prime or not
bool isPrime(int num) 
{
    if (num <= 1)
        return false;

    for (int i = 2; i <= sqrt(num); ++i)
        if (num % i == 0)
            return false;
    
    return true;
}

// Algorithm to find all primes within a certain range
void sieve(int start, int end) 
{
    std::cout << start << " + " << end << endl;
}

int main(void) 
{
    std::vector<int> primesList;

    std::cout << "Hello World!" << endl;

    // Execution start time prior to thread spawn
    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;

    // Spawn 8 threads, each sieving a portion of the total range
	// Each thread has an equivalent workload of range
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = MIN + i * SEGMENT_SIZE;
        int end = start + SEGMENT_SIZE - 1;
        threads.push_back(std::thread(sieve, start, end));
    }

    for (auto& t : threads)
        t.join();
    
    // Execution end time after all threads complete
    auto endTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> executionTime = endTime - startTime;

    //  DON'T INCLUDE ZERO OR ONE IN PRIMES FOUND
    // - output to primes.txt
    //   <execution time> <tot al number of primes found> <sum of all primes found>
    //   <top ten maximum primes, listed in order from lowest to highest>

    std::cout << executionTime.count() << " ms" << endl;
    
    return 0;
}
