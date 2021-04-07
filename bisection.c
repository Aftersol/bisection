/*
 * -- bisecton.c -- This function finds the root of an equation using the bisection method: https://en.wikipedia.org/wiki/Bisection_method
 * Code written by Aftersol (c) 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ctype.h>
#include <math.h>

#include "usleep.h"

int sign(double x)
{
    return (x < 0) ? -1 : (x > 0) ? 1 : 0;
}

double midpoint(double a, double b)
{
    return (a+b)/2.0;
}

double rootFind(double x)
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

    unsigned int iterations = 0u;
    double c;

    while (iterations < n) 
    {
        c = midpoint(a,b);

        if (function(c) == 0 || fabs(function(c)) < tolerance)
            break;

        iterations++;

        if (sign(function(a)) == sign(function(c)))
            a = c;

        else
            b = c; 
    } 

    *result = c;
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
        if (str[pos] == '\0' || str[pos] == '\n')
            break;

        if ((str[pos] >= '0' && str[pos] <= '9'))
        {
            continue;
        }
        else if (str[pos] == '.')
        {
            if (hasADot || hasAnE)
            {
                strIsDigit = false;
                break;
            }
            else
                hasADot = true;
        }
        else if (str[pos] == 'e')
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
        else if (str[pos] == '-')
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
    char* buffer = (char*)malloc(1025 * sizeof(char)); // 1024 + 1 char space for NULL terminator
    if (!buffer)
        return -1;

    double a, b, tolerance;
    int iterations;

    bool success[5]; // sucessful input?

    do
    {
        success[0] = false, success[1] = false, success[2] = false, success[3] = false, success[4] = false;
        do
        {
            
            printf("Enter first value: ");
            success[0] = (fgets(buffer, 1024, stdin) != NULL);
            if (strn_isDigit(buffer, 1024))
            {
                a = atof(buffer);
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
        {
            printf("The first and second must be a number the opposite signs of each other returned from a function or the number of iterations must be positive.\n");
        }
    } while (success[4] == false);

    sleep_ms(5000);

    return 0;
}