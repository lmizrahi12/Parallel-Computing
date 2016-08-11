#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

double f(int x);
void Test_noOfThreads();
void Test_noOfPartitions();

int main () {
    int n = 0;

    while(n != 1 && n != 2){
        cout << "Which test?" << endl;
        cout << "\t 1.Number of Partitions" << endl;
        cout << "\t 2.Number of Threads" << endl;

        cin >> n;

        if(n != 1 && n != 2)
            cout << "Invalid choice  t('^'t)" << endl;
    }

    if(n == 1)
        Test_noOfPartitions();

    else
        Test_noOfThreads();
}

double f(int x){
    return x*exp(-x);
}

void Test_noOfThreads(){
    ofstream file;
    int N = 500;
    long double area;
    double width;
    int noThreads;

    width = (double)20/(N);    

    for(noThreads = 1;noThreads <= 1000;noThreads++){
        area = 0;

        double start = omp_get_wtime(); 
            omp_set_num_threads(noThreads);
            #pragma omp parallel for reduction(+:area)
            for(int i = 0;i < N;i++){
                area += ( f(i*width) + f((i+1) * width) )/2;
            }

            area *= width;
        double end = omp_get_wtime();

        cout << "Threads " << noThreads << ", " << "Area: " << area << ", " << "Time: " << end-start << endl;

        /*file.open("results_trapezoid_threads_accuracy.csv", ios::app);
        file << noThreads << "," << area << endl;
        file.close();

        file.open("results_trapezoid_threads_time.csv", ios::app);
        file << noThreads << "," << end-start << endl;
        file.close();*/
    }
}

void Test_noOfPartitions(){
    ofstream file;
    int N;
    long double area;
    double width;
    int noThreads = 4;    

    for(N = 1;N <= 1000;N++){
        area = 0;
        width = (double)20/(N);

        double start = omp_get_wtime(); 
            omp_set_num_threads(noThreads);
            #pragma omp parallel for reduction(+:area)
            for(int i = 0;i < N;i++){
                area += ( f(i*width) + f((i+1) * width) )/2;
            }

            area *= width;
        double end = omp_get_wtime();

        cout << "Partitions " << N << ", " << "Area: " << area << ", " << "Time: " << end-start << endl;

        /*file.open("temp_results_trapezoid_partitions_accuracy.csv", ios::app);
        file << N << "," << area << endl;
        file.close();

        file.open("results_trapezoid_partitions_time.csv", ios::app);
        file << N << "," << end-start << endl;
        file.close();*/
    }
}
