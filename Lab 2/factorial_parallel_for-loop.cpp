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

    omp_set_num_threads(4);
    #pragma omp parallel for reduction(*:factorial)
    for(int i = 0;i < n;i++){
    cout << omp_get_num_threads() << endl;
        factorial = factorial * (n-i);
    }

    cout << n << "! = " << factorial << endl;
}
