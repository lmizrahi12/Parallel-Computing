#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

int main () {
    ofstream file;
    double ave = 0;
	int **mat;
    int iterations = 500;
    int adder = 100;

	srand(time(NULL));

for(int n = 100; n <= 5000; n += adder){
    if( n == 1000)
        adder = 1000;

        mat = new int*[n];
        for (int i = 0; i < n; i++) {
            mat[i] = new int[n];
        }

        ave = 0;

        for(int it = 0;it < iterations;it++){
	        double start = omp_get_wtime();	

	        for(int i = 0;i < n;i++){
		        for(int j = 0;j < n;j++){
			        mat[i][j] = rand() % 100 + 1;
		        }
	        }

	        double end = omp_get_wtime();
            ave += (end - start) / iterations;
	        cout << "Array size: " << n << "\tTime: (" << end - start << ")\n";
        }
        cout << "Average time: " << ave << endl;

        file.open("RowVsColumn_row.csv", ios::app);
        file << n << "," << ave << endl;
        file.close();

        for (int i = 0; i < n; i++) {
            delete mat[i];
        }
        delete mat;
}
}
