#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int factorial(int n);

int main () {
    int n = 5;
    cout << n << "! = " << factorial(n) << endl;
}

int factorial(int n){
    int fact;

    if(n <= 1)
        return 1;

    else
        fact = n * factorial(n-1);

    return fact;
}
