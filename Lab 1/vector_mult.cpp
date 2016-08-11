#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <array>
#include <fstream>

using namespace std;

int n = 50000;

void Print_Vector(int* vec){
    cout << "[" << vec[0];
    for(int i = 1;i < n;i++){
        cout << "," << vec[i] ;
    }
    cout << "]" << endl;
}

int* Randomise(int* vec){
    for(int i = 0;i < n;i++){
	    vec[i] = rand() % 10 + 1;
    }
    return vec;
}

int* Parallel_Randomise(int* vec){
    #pragma omp parallel for
        for(int i = 0;i < n;i++){
	        vec[i] = rand() % 10 + 1;
        }
    return vec;
}

int Parallel_Dot_Product(int* vec1, int* vec2){
    int dot_product = 0;
    #pragma omp parallel for reduction(+:dot_product)
		for(int	i = 0;i < n;i++){
            dot_product += vec1[i] * vec2[i];
	    }
    return dot_product;
}

int Parallel_Dot_Product(int* vec1, int* vec2, int num_threads){
    int dot_product = 0;
    omp_set_num_threads(num_threads);
    #pragma omp parallel for reduction(+:dot_product)
		for(int	i = 0;i < n;i++){
            dot_product += vec1[i] * vec2[i];
	    }
    return dot_product;
}

int main () {
    int *vec1;
    int *vec2;
    int dot_product = 0;
    double start;
    double end;
    double ave = 0;
    ofstream file;
    int adder = 100;
    int threads = 0;

    srand(time(NULL));

for(n = 100;n <= 50000;n += adder){
//for(threads = 10;threads <= 5000;threads += adder){
    ave = 0;
    /*if(n == 1000)
        adder = 1000;*/
    for(int it = 0;it < 500;it++){
        vec1 = new int[n];
        vec2 = new int[n];        
        
        start = omp_get_wtime();

            vec1 = Parallel_Randomise(vec1);
            vec2 = Parallel_Randomise(vec2);
	        dot_product = Parallel_Dot_Product(vec1, vec2, threads);

	    end = omp_get_wtime();

        cout << "Array Size: " << n << "\t";
	    cout << "Time: (" << end - start << ")" << endl;
        ave += (end - start)/500;
            
        delete vec1;
        delete vec2;
    }

    cout << "Average Time: " << ave << endl;
    file.open("Dot_prod_parallel_rng_points.csv", ios::app);
    file << n << "," << ave << endl;
    file.close();
   }
}
