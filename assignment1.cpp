// Evan Tieu
// COP4520 Assignment 1
// Spring 2024

#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const int NUM_THREADS = 8;
const int MIN = 1;
const int MAX = 100000000;
const int SEGMENT_SIZE = (MAX - MIN + 1) / NUM_THREADS;

int totalPrimes = 0;
long long sumPrimes = 0;

// Calculates if a given number is prime or not
bool isPrime(int num) 
{
    if (num <= 1 || num > 2 && num % 2 == 0)
        return false;

    for (int i = 3; i <= sqrt(num); i += 2)
        if (num % i == 0)
            return false;
    
    return true;
}

// Algorithm to find all primes within a certain range
void sieve(int start, int end) 
{
    using namespace std;

    cout << start << " + " << end << endl;

    cout << "is " << start << " prime? " << isPrime(start) << endl;
    cout << "is " << end << " prime? " << isPrime(end) << endl;
}

int main(void) 
{
    // Let's make it easier to type.
    using namespace std;

    // Initialize a 2D integer vector of length
    // equivalent to the number of threads.
    // Each thread has their own list of primes.
    vector<vector<int>> listPrimes(NUM_THREADS);

    cout << "Hello World!" << endl;

    // Execution start time prior to thread spawn.
    auto startTime = chrono::high_resolution_clock::now();
    
    vector<thread> threads;

    // Spawn 8 threads, each sieving a portion of the total range.
	// Each thread has an equivalent workload of range.
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = MIN + i * SEGMENT_SIZE;
        int end = start + SEGMENT_SIZE - 1;
        threads.push_back(std::thread(sieve, start, end));
    }

    for (auto& t : threads)
        t.join();
    
    // Execution end time after all threads complete.
    auto endTime = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime = endTime - startTime;

    //  DON'T INCLUDE ZERO OR ONE IN PRIMES FOUND
    // - output to primes.txt
    //   <execution time> <tot al number of primes found> <sum of all primes found>
    //   <top ten maximum primes, listed in order from lowest to highest>

    cout << executionTime.count() << " ms" << endl;
    cout << "SUM " << sumPrimes << endl;
    
    return 0;
}
