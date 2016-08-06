#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

double f(int x);

int main () {
    ofstream file;
    int N = 500;
    long double area;
    double width;
    int n;

    width = (double)20/(N);    

    for(int n = 1;n <= 1000;n++){
        area = 0;

        double start = omp_get_wtime(); 
            omp_set_num_threads(n);
            #pragma omp parallel for reduction(+:area)
            for(int i = 0;i < N;i++){
                area += ( f(i*width) + f((i+1) * width) )/2;
            }

            area *= width;
        double end = omp_get_wtime();

        cout << "Threads " << n << ", " << "Area: " << area << ", " << "Time: " << end-start << endl;

        file.open("results_trapezoid_threads_accuracy.csv", ios::app);
        file << n << "," << area << endl;
        file.close();

        file.open("results_trapezoid_threads_time.csv", ios::app);
        file << n << "," << end-start << endl;
        file.close();
    }
}

double f(int x){
    return x*exp(-x);
}
