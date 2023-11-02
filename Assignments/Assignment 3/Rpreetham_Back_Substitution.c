/* PROGRAM BackSubstitution */
#include <stdlib.h>
#include <math.h>
#define n 4
float A[n+1][n+1];

float B[n+1] = {0, 5, 2, 1, 7};

float x[n+1];
float stream pipechan[n+2];
int i, j;
void PipeProcess(int i) {
    /*Solves Equation i to compute x[i]*/
    int j;
    float sum, xvalue;
    sum = 0;
    for (j = 1; j <= i-1; j++) {
        recv(pipechan[i],xvalue); /*Read x[j] from left*/
        send(pipechan[i+1],xvalue); /*Send x[j] to right*/
        sum = sum + A[i][j]*xvalue;
    }
    x[i] = (B[i]-sum) / A[i][i]; /*Compute x[i]*/
    send(pipechan[i+1],x[i]); /*Send x[i] to right*/
}
main( ) {
    cout.precision(2);
    /* cout << (rand() % 10000)/100.0; */
    /*Initialize arrays A and B */
    for(i = 1; i <= n;i++){
        for(j = 1; j <= n; j++ ){
            A[i][j] = (rand() % 10000)/100.0;
        }
    }
    forall i = 1 to n do /*Create pipeline processes */
        PipeProcess(i);

    for(i = 1; i <= n; i++){
        cout << x[i] << " "; 
    }

}
/*
float B[n+1] = {0, 5, 2, 1, 7, 2, 3, 6, 7, 1,
                2, 3, 6, 1, 3, 7, 2, 7, 6, 0}; */