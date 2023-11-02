#include <stdlib.h>
#include <math.h>

#define n 32
#define tolerance 0.003

float A[n+2][n+2], B[n+2][n+2];
int stream higher[n+1], stream lower[n+1];
spinlock Arrival, Departure;
int i, j;
boolean globaldone;
int count;
/*6.11*/
void LocalBarrier(int i) {
    int dummy;
    if (i > 1)
        send(higher[i-1],1); /*send to Process i-1*/
    if (i < n) {
        send(lower[i+1],1); /*send to Process i+1*/
        recv(higher[i],dummy); /*receive from Process i-1*/
    }
    if (i > 1)
        recv(lower[i],dummy); /*receive from Process i+1*/
}

boolean Aggregate(boolean mydone) {
    boolean result;
    /*Arrival Phase - Count the processes arriving*/
    Lock(Arrival);
    count = count + 1;
    globaldone = globaldone && mydone; /*aggregation*/
    if (count < n) {
        Unlock(Arrival); /*continue Arrival Phase*/
    }
    else {
        Unlock(Departure); /*end Arrival Phase*/
    }
    /*Departure Phase - Count the processes leaving*/
    Lock(Departure);
    count = count - 1;
    result = globaldone; /*return “done” flag*/
    if (count > 0) {
        Unlock(Departure); /*continue Departure Phase*/
    }
    else {
        Unlock(Arrival); /*terminate Departure Phase*/
        globaldone = true; /*reset for new Aggregation*/
    }
    return(result);
}


main( ){

    cout.precision(3);
    /*Read in initial values for array A*/
    for(i = 1; i <= n;i++){
        for(j = 1; j <= n; j++ ){
            A[i][j] = (rand() % 200) / 200.0;
        }
    }
    B = A;
    forall i = 1 to n do {
        int j;
        float change, maxchange;
        boolean done;
        do {
            maxchange = 0;
            for(j = 1; j <= n; j++) {
                B[i][j] = (A[i-1][j] + A[i+1][j] + A[i][j-1] + A[i][j+1]) / 4;
                change = fabs(B[i][j] - A[i][j]);
                if(change > maxchange) {
                    maxchange = change;
                }
            }
            LocalBarrier(i);
            A[i] = B[i];
            done = Aggregate(maxchange < tolerance);
        }
        while (!done);
    }

    cout << "Ruthwik Preetham"<< endl ;

    for(i = 0; i <= n + 1; i++){
            cout << "Row:  " << i << "   Result" <<endl;
            for(j = 0; j <= n+1; j++){
            if((j > 0) && (j % 10) == 0){
                cout << endl;
            }
            cout << A[i][j] << "  ";
            }
        cout << endl;
    }

    
}