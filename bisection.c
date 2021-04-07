/*
 * -- bisecton.c -- This function finds the root of an equation using the bisection method: https://en.wikipedia.org/wiki/Bisection_method
 * Code written by Aftersol (c) 2021
 */

#define ENABLE_SLEEP 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ctype.h>
#include <math.h>

#ifdef ENABLE_SLEEP
#include "usleep.h" // For putting a program to sleep so we can see the results
#endif

int sign(double x)
{
    return (x < 0) ? -1 : (x > 0) ? 1 : 0;
}

double midpoint(double a, double b)
{
    return (a+b)/2.0;
}

double rootFind(double x) // Replace this function with your own function for finding root for different functions
{
    return log(x) + (x*x) - 3;
}

/* Based on GeeksForGeeks code https://www.geeksforgeeks.org/program-for-bisection-method/
 * and
/* https://bookdown.org/rdpeng/advstatcomp/bisection-algorithm.html */
bool bisection(double (*function)(double), double a, double b, double tolerance, double* result, unsigned int n)
{
    if (sign(a) != sign(b) || n <= 0) // does it return a negative number
        return false;

    unsigned int iterations = 0u; // Current iterations
    double mid; // Midpoint value

    while (iterations < n) // Keep looping through iterations until a solution is found
    {
        mid = midpoint(a,b);

        if (function(mid) == 0 || fabs(function(mid)) < tolerance) // solution for a root is found
            break;

        iterations++;

        if (sign(function(a)) == sign(function(mid))) // Has the signs changed yet
            a = mid;

        else
            b = mid; 
    } 

    *result = mid; // Returns the result of the bisection function
    return true;
}

bool strn_isDigit(const char* str, size_t len)
{
    size_t pos = 0;

    bool strIsDigit = true;
    bool hasADot = false;
    bool hasAnE = false;
    bool hasA_Negative = false;

    for (pos = 0; pos < len; pos++)
    {
        if (str[pos] == '\0' || str[pos] == '\n') // Stop when the terminating character is reached
            break;

        if ((str[pos] >= '0' && str[pos] <= '9')) // Only accepts numerical values
        {
            continue;
        }
        else if (str[pos] == '.') // decimal character
        {
            if (hasADot || hasAnE)
            {
                strIsDigit = false;
                break;
            }
            else
                hasADot = true;
        }
        else if (str[pos] == 'e' || str[pos] == 'E') // exponent character
        {
            if (hasAnE)
            {
                strIsDigit = false;
                break;
            }
            else
            {
                hasADot = true;
                hasAnE = true;
            }
        }
        else if (str[pos] == '-') // Negative character
        {
            if (hasA_Negative || pos > 0)
            {
                strIsDigit = false;
                break;
            }
            else
            {
                hasA_Negative = true;
            }
        }
        else
        {
            strIsDigit = false;
            break;
        }
    }

    return strIsDigit;
}

int main()
{
    char* buffer = (char*)malloc(1025 * sizeof(char)); // Allocate 1024 char elements plus an extra character for the NULL terminator
    if (!buffer)
        return -1;

    double a, b, tolerance;
    int iterations;

    bool success[5]; // Sucessful input?

    do // Makes sure this program is run at least once
    {
        success[0] = false, success[1] = false, success[2] = false, success[3] = false, success[4] = false;
        do
        {
            
            printf("Enter first value: ");
            success[0] = (fgets(buffer, 1024, stdin) != NULL);
            if (strn_isDigit(buffer, 1024))
            {
                a = atof(buffer); // Convert a string into a float
                success[0] = true;
            }
            else
                success[0] = false;

        } while (success[0] == false);

        do
        {
            printf("Enter second value: ");
            success[1] = (fgets(buffer, 1024, stdin) != NULL);
            if (strn_isDigit(buffer, 1024))
            {
                b = atof(buffer);
                success[1] = true;
            }
            else
                success[1] = false;

        } while (success[1] == false);

        do
        {
            
            printf("Enter tolerance: ");
            success[2] = (fgets(buffer, 1024, stdin) != NULL);
            if (strn_isDigit(buffer, 1024))
            {
                tolerance = atof(buffer);
                success[2] = true;
            }
            else
                success[2] = false;
                
        } while (success[2] == false);

        do
        {
            
            printf("How many iterations: ");
            success[2] = (fgets(buffer, 1024, stdin) != NULL);
            if (strn_isDigit(buffer, 1024))
            {
                iterations = atol(buffer);
                success[3] = true;
            }
            else
                success[3] = false;
                
        } while (success[3] == false);


        double result = 0.0;

        if (bisection(rootFind, a, b, tolerance, &result, iterations))
        {
            printf("The root for %f and %f with the tolerance of %f is %f.\n", a, b, tolerance, result);
            success[4] = true;
        }
        else
            printf("The first and second must be a number the opposite signs of each other returned from a function or the number of iterations must be positive.\n");

    } while (success[4] == false); // Automatically tries again if the bisection algorithm fails to return a root

#ifdef ENABLE_SLEEP
    sleep_ms(5000);
#endif

    return 0;
}