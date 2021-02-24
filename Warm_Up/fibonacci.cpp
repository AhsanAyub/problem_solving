/*
 * This program covers two types of implementation for the N-th Fibonacci number.
 * Fibonacci sequence: F(0) = 0, F(1) = 1, and F(i) = F(i-1) +F(i-1)
 * 
 * The first one is recursive approach (very slow) while the other one (faster)
 * is a list-based approach that iteratively stores all the fibonacci sequence's numbers.
 * 
 * Last Edited on Feb 23, 2021 23:33:57 (Central Standard Time)
 */

#include <iostream>
#include <vector>
#include <chrono> 

using namespace std;

// Utility function of the recursive approach to compute the N-th Fibonacci number.
unsigned long long int getFibonacciNthNumberRecursive(int N)
{
    if (N <= 1)     // Base condition
        return N;
    else            // Recusive call
        return getFibonacciNthNumberRecursive(N-1) + getFibonacciNthNumberRecursive(N-2);
}

// Utility function of the list-based approach to compute the N-th Fibonacci number.
unsigned long long int getFibonacciNthNumber(int N)
{
    vector<unsigned long long int > vFibonacciNumbers;
    
    vFibonacciNumbers.push_back(0);     // F(0) = 0
    vFibonacciNumbers.push_back(1);     // F(1) = 1

    for (int i = 2; i <= N+1; i++)      // F[i] <-- F[i−1] + F[i−2]
        vFibonacciNumbers.push_back(vFibonacciNumbers.at(i-1) + vFibonacciNumbers.at(i-2));

    return vFibonacciNumbers.at(N);     // Return the N-th Fibonacci number
}

int main(int argc, char* argv[])
{
    // Check whether the user passes a valid line argument
    if (argc != 2)
    {
        printf("Usuage: ./<executable> <n-th Fibonacci number>\n");
        return -1;
    }

    // Get the user input
    int N = atoi(argv[1]);

    // Call the recursive approach
    auto recursiveApproachStart = std::chrono::high_resolution_clock::now();
    cout << N << "-th Fibonacci Number (Recusrive Appraoch): " << getFibonacciNthNumberRecursive(N) << endl;
    auto recursiveApproachStop = std::chrono::high_resolution_clock::now();
    auto recursiveApproachDuration = std::chrono::duration_cast<std::chrono::microseconds>(recursiveApproachStop - recursiveApproachStart).count();
    cout << "Duration in miliseconds: " << recursiveApproachDuration << endl;
    
    // Call the list-based approach
    auto listApproachStart = std::chrono::high_resolution_clock::now();
    cout << endl << N << "-th Fibonacci Number (List-based Appraoch): " << getFibonacciNthNumber(N) << endl;
    auto listApproachStop = std::chrono::high_resolution_clock::now();
    auto listApproachDuration = std::chrono::duration_cast<std::chrono::microseconds>(listApproachStop - listApproachStart).count();
    cout << "Duration in miliseconds: " << listApproachDuration << endl;

    return 0;
}