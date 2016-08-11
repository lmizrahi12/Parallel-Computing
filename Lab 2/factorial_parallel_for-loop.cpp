#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int main () {

    int n = 15;
    long long int factorial = 1;

    #pragma omp parallel reduction(*:factorial)
    for(int i = 0;i < n;i++){
        factorial = factorial * (n-i);
    }

    cout << n << "! = " << factorial << endl;
}
