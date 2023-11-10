/* PROGRAM NumericalIntegration */
#include <stdlib.h>
#include <math.h>

#define numproc 40 /*number of processes*/
#define numpoints 30 /*number of points per process*/

float process[numproc];
float stream globalSumValue[numproc];
float globalsum;
int i;

spinlock L;

float f(float t) { /*Function to be integrated*/
    /*Compute value of f(t)*/
    return sqrt(4 - t * t);

}

main( ) {
    cout.precision(10);
    float start, end, w, answer;
    /*Initialize values of end points “a” and “b”*/
    start = 0;
    end = 2;
    w = (end-start)/(numproc*numpoints); /*spacing of points*/
    forall i = 0 to numproc-1 do {
        /*Create processes*/
        float sum = 0;
        float t;
        int j;
        t = start + i * (end - start) / numproc;
        for(j = 0; j < numpoints; j++) {
            sum = sum + f(t);
            t = t + w;
        }
        sum = w * sum;
        Lock(L);
        globalsum = globalsum + sum;
        Unlock(L);
    }
    for(i = 0; i < numproc; i++) {
        globalsum = globalsum + process[i];
    }
    answer = globalsum + w/2 *(f(end)-f(start)); /*end points*/
	cout << "Integral of f(x) from a to b :" << answer;
}