#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

int factorial(int n){
    long int lower_fact = 1;
    long int upper_fact = 1;
    long int fact;

    #pragma omp sections
    {
        #pragma omp section
        {
            for(int i = 0;i < floor(n/2);i++){
                lower_fact = lower_fact * (n-i);
            }
        }

        #pragma omp section
        {
            for(int i = floor(n/2);i < n;i++){
                upper_fact = upper_fact * (n-i);
            }
        } 
    }

    return lower_fact * upper_fact;
}

int main() {
    int n = 10;

    cout << n << "! = " << factorial(n) << endl;   
}

