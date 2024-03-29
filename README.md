# cop4520prog1
cop4520 programming assignment 1

Task: Find all primes between 1 and 10^8 (100000000)

- Approach

I searched for algorithms online to find all possible primes up to a number, and landed on multiple Sieve algorithms. I used these as a baseline for my program. I double-checked correctness for the total number of primes found by using dcode's Prime Counting Calculator.

I also estimated for correctness by substituting our current range into the prime number theorem, which gave me approximate values for both the total number of primes and the sum of all primes. 

I optimized my program for efficiency dividing the range across multiple threads, each of which concurrently implemented the sieve algorithm to find the primes within their range. I also skipped even numbers, which we know are not prime (except for 2). This shaved off a few seconds of execution time. 

- Experimental Evaluation

I tested my program with different values, such as 10^5 and 10^10, cross-checking with the methods described above (Prime Counting Calculator, prime number theorem) for approximate values for total number of primes and sum of all primes.

- Instructions
1. Download 'assignment1.cpp'
2. Move file to directory of your choice
3. Compile by typing 'g++ assignment1.cpp'
4. Execute the file by typing './a.out'
