// Evan Tieu
// COP4520 Assignment 1
// Spring 2024

#include <chrono>
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const int NUM_THREADS = 8;
const int MIN = 1;
const int MAX = 100000000;
const int SEGMENT_SIZE = (MAX - MIN + 1) / NUM_THREADS;

int totalNumPrimes = 0;
long long sumPrimes = 0;

std::mutex mtx;

// Calculates if a given number is prime or not.
bool isPrime(int num) 
{
    // 0 and 1 are not prime (nor composite).
    // Skip even numbers.
    if (num <= 1 || num > 2 && num % 2 == 0)
        return false;

    // Start from 3 as we already have cases for <= 2.
    // Use sieve to check if a number is prime, skipping even numbers.
    for (int i = 3; i <= sqrt(num); i += 2)
        if (num % i == 0)
            return false;
    
    // Our number is prime!
    return true;
}

// Algorithm to find all primes within a certain range.
void sieve(int start, int end) 
{
    int total = 0;
    int sum = 0;

    for (int i = (start % 2 == 0) ? start + 1 : start; i <= end; i += 2)
    {
        if (isPrime(i))
        {
            ++total;
            sum += i;
        }      
    }

}

int main(void) 
{
    // Let's make it easier to type.
    using namespace std;

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
        threads.push_back(thread(sieve, start, end));
    }

    for (auto& t : threads)
        t.join();

    // Execution end time after all threads complete.
    auto endTime = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime = endTime - startTime;

    //  DON'T INCLUDE ZERO OR ONE IN PRIMES FOUND
    // - output to primes.txt
    //   <execution time> <total number of primes found> <sum of all primes found>
    //   <top ten maximum primes, listed in order from lowest to highest>

    cout << executionTime.count() << " ms" << endl;
    cout << "SUM " << sumPrimes << endl;
    
    return 0;
}
