// Evan Tieu
// COP4520 Assignment 1
// Spring 2024

#include <chrono>
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

using namespace std;

constexpr int NUM_THREADS = 8;
constexpr int MAX = 100000000;
int totalPrimes = 0;
long long sumPrimes = 0;

// - spawn 8 threads that will perform the necessary computation

// - work is distributed such that the computational execution time is
//   approximately equivalent among the threads

// - output to primes.txt
//   <execution time> <tot al number of primes found> <sum of all primes found>
//   <top ten maximum primes, listed in order from lowest to highest>

//  DON'T INCLUDE ZERO OR ONE IN PRIMES FOUND
//  execution time should start prior to spawning the threads 
//  and end after all threads  complete

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

    auto startTime = std::chrono::high_resolution_clock::now();
    
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads.push_back(std::thread(sieve, i));
    }

    for (auto& t : threads)
        t.join();
    
    auto endTime = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double, std::milli> executionTime = endTime - startTime;

    // std::thread t1(sieve, num);

    std::cout << executionTime.count() << " ms" << endl;
    
    return 0;
}
