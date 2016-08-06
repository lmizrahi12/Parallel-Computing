#include "stdio.h"
#include "omp.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main () {

    omp_set_num_threads(20);
    #pragma omp parallel
    {
        cout << "Thread ID: (" << omp_get_thread_num() << ")\n";
    }
}
