/*
 * This program covers two types of implementation for the Greatest Common Divisor (GCD).
 * The main goal of the GCD is to put the fraction a / b in the simplest form possible.
 * For example, the fraction of 10 / 4 could be rewritten as 5 / 2, where the GCD is 2.
 * 
 * The first one is a naive solution that is designed from the defination (slow).
 * Based on the key lemma, the second one is much faster (logarithmic complexity).
 * 
 * Last Edited on Feb 25, 2021 23:25:05 (Central Standard Time)
 */

#include <iostream>
#include <vector>
#include <chrono> 

using namespace std;

// Utility function to compute the GCD of a and b as per the mathematical defination.
int naiveGCD(int a, int b)
{
    /*
        We will divide the numerator and denominator by d, to get (a / d) / (b / d)
        The selection of the value of d will be done iteratively and the best value
        will be stored in the variable called iGCDValue
    */
    int iGCDValue = 0, d = 1;
    
    while(d <= a + b)   // (a+b) is the runtime
    {
        if ((a % d) == 0 && (b % d) == 0)
            iGCDValue = d;
        d++;    // We want d to be as large as possible
    }
    return iGCDValue;           
}

// Utility function to compute the GCD of a and b as per the euclidean method.
int euclidGCD(int a, int b)
{
    // Base condition
    if (b == 0)
        return a;
    // Compute a' for the next iteration
    a = a % b;
    return euclidGCD(b, a);     // log(ab) is the runtime
}

int main(int argc, char* argv[])
{
    // Check whether the user passes a valid line argument
    if (argc != 3)
    {
        printf("Usuage: ./<executable> <a> <b>\n");
        return -1;
    }

    // Get the user inputs
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    // Call the naive solution
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Mathematical Defination Approach - GCD("<< a << ", " << b << "): " << naiveGCD(a,b) << endl;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    cout << "Duration in miliseconds: " << duration << endl;
    
    // Call the euclidean method approach
    start = std::chrono::high_resolution_clock::now();
    cout << "\nEuclidean Method - GCD("<< a << ", " << b << "): " << euclidGCD(a,b) << endl;
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    cout << "Duration in miliseconds: " << duration << endl;

    return 0;
}