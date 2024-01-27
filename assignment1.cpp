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
    if (num < 2 || num % 2 == 0)
        return false;

    // Start from 3 as we already have cases for <= 2.
    // Use sieve to check if a number is prime, skipping even numbers.
    for (int i = 3; i*i <= num; i += 2)
        if (num % i == 0)
            return false;
    
    // Our number is prime!
    return true;
}

// Algorithm to find all primes within a certain range.
void sieve(int start, int end) 
{
    using namespace std;

    // Initialize local variables for our current thread.
    int total = 0;
    long long sum = 0;

    // Loop through the range of numbers, checking for primality.
    // Skip even numbers.
    for (int i = (start % 2 == 0) ? start + 1 : start; i <= end; i += 2)
    {
        if (isPrime(i))
        {
            total++;
            sum += i;
        }      
    }

    // Protect the updated variables.
    lock_guard<mutex> lock(mtx);
    totalNumPrimes += total;
    sumPrimes += sum;
}

int main(void) 
{
    using namespace std;

    // Execution start time prior to thread spawn.
    auto startTime = chrono::high_resolution_clock::now();
    
    vector<thread> threads;

    // Spawn threads, each sieving a portion of the total range.
	// Each thread has an equivalent workload of range.
    for (int i = 0; i < NUM_THREADS; ++i)
    {
        int start = MIN + i * SEGMENT_SIZE;
        int end = start + SEGMENT_SIZE - 1;
        threads.push_back(thread(sieve, start, end));
    }

    // Merge threads afterwards.
    for (auto& t : threads)
        t.join();

    // Execution end time after all threads complete.
    auto endTime = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> executionTime = endTime - startTime;

    // We skip the number 2 in our algorithm.
    // So, include that in the total number and sum.
    ++totalNumPrimes;
    sumPrimes += 2;

    // Now find the top ten maximum primes in our range,
    // starting from the biggest number.
    vector<int> topTenPrimes;

    for (int i = MAX; i >= MIN; --i)
    {
        if (isPrime(i))
        {
            topTenPrimes.push_back(i);
            
            if (topTenPrimes.size() == 10)
                break;
        }
    }

    // Sort the maximum primes from lowest to highest.
    sort(topTenPrimes.begin(), topTenPrimes.end());
    
    //  Write our output to 'primes.txt'.
    //  <execution time> <total number of primes found> <sum of all primes found>
    //  <top ten maximum primes, listed in order from lowest to highest>

    ofstream outFile("primes.txt");

    outFile << "<" << executionTime.count() << " ms> ";
    outFile << "<" << totalNumPrimes << "> ";
    outFile << "<" << sumPrimes << ">" << endl;
    
    for (int prime : topTenPrimes)
        outFile << prime << " ";

    outFile << endl;

    // Debugging prints
    cout << "< " << executionTime.count() << " ms" << " > ";
    cout << "< "<< "TOTAL NUM " << totalNumPrimes << " > ";
    cout << "< " << "SUM " << sumPrimes << " >" << endl;
    
    cout << "top ten primes" << endl;

    for (int prime : topTenPrimes)
        cout << prime << " ";

    cout << endl;

    // Don't forget to close file.
    outFile.close();

    return 0;
}
