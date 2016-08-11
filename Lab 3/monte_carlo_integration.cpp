#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

double f(int x);
double AreaOfBox(double length, double height);
double Random(double low, double high);
void Test_noOfThreads();
void Test_noOfPoints();

int main () {

    srand(time(0));

    int n = 0;

    while(n != 1 && n != 2){
        cout << "Which test?" << endl;
        cout << "\t 1.Number of Points" << endl;
        cout << "\t 2.Number of Threads" << endl;

        cin >> n;

        if(n != 1 && n != 2)
            cout << "Invalid choice  t('^'t)" << endl;
    }

    if(n == 1)
        Test_noOfPoints();

    else
        Test_noOfThreads();

}

double f(int x){
    return x*exp(-x);
}

double AreaOfBox(double length, double height){
    return length * height;
}

double Random(double low, double high){
    return low + (double) (rand()) / ( (double) (RAND_MAX/(high-low)));
}

void Test_noOfThreads(){
    ofstream file;
    double randX;
    double randY;
    double boxHeight = 0.5;
    double boxLength = 20;
    int noOfPoints = 5000;
    int pointsUnderCurve = 0;
    long double approximateArea = 0;
    int noThreads = 2;
    
    for(noThreads = 2; noThreads < 1000; noThreads++){
        approximateArea = 0;
        pointsUnderCurve = 0;

        double start = omp_get_wtime();

        omp_set_num_threads(noThreads);
        #pragma parallel for private(randX, randY, pointsUnderCurve) shared(boxLength, boxHeight) reduction(+:pointsUnderCurve)
        for(int i = 0;i < noOfPoints;i++){
            randX = Random(0, boxLength);
            randY = Random(0, boxHeight);

            if( randY <= f( randX ))
                pointsUnderCurve++;
        }

        approximateArea = AreaOfBox(boxLength, boxHeight) * ((double) pointsUnderCurve / noOfPoints);

        double end = omp_get_wtime();

        /*file.open("monte_carlo_noThreads.csv", ios::app);
        file << noThreads << "," << approximateArea << "," << end - start << endl;
        file.close();*/


        cout << "noThreads: " << noThreads << " , Approximate area: " << approximateArea << ", Time: " << end - start << endl;

    }

}

void Test_noOfPoints(){
    ofstream file;
    double randX;
    double randY;
    double boxHeight = 0.5;
    double boxLength = 20;
    int noOfPoints = 100;
    int pointsUnderCurve = 0;
    long double approximateArea = 0;
    int noThreads = 4;
    
    for(noOfPoints = 100; noOfPoints < 50000; noOfPoints += 100){
        approximateArea = 0;
        pointsUnderCurve = 0;

        double start = omp_get_wtime();

        omp_set_num_threads(noThreads);
        #pragma parallel for private(randX, randY, pointsUnderCurve) shared(boxLength, boxHeight) reduction(+:pointsUnderCurve)
        for(int i = 0;i < noOfPoints;i++){
            randX = Random(0, boxLength);
            randY = Random(0, boxHeight);

            if( randY <= f( randX ))
                pointsUnderCurve++;
        }

        approximateArea = AreaOfBox(boxLength, boxHeight) * ((double) pointsUnderCurve / noOfPoints);

        double end = omp_get_wtime();

        /*file.open("monte_carlo_noOfPoints.csv", ios::app);
        file << noOfPoints << "," << approximateArea << "," << end - start << endl;
        file.close();*/


        cout << "Num of points: " << noOfPoints << " , Approximate area: " << approximateArea << ", Time: " << end - start << endl;

    }

}
