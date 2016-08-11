#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int main () {

    int n = 10;
    int factorial = 1;

    for(int i = 0;i < n;i++){
        factorial = factorial * (n-i);
    }

    cout << n << "! = " << factorial << endl;
}
