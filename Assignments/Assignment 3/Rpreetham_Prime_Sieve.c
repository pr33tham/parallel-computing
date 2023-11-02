/* PROGRAM Sieve */
#include <stdlib.h>

#define n 20
#define group 20
#define endMarker -1

boolean isPrime[n];
int numberOfProcesses = n / group;
int stream primeStarter[2];

int loc;

int findLocalStart(int s, int t) { 
    int v = s;
    if (v % t == 0)
        return s;
    else do {
        v++;
    }
    while( v% t != 0);
    return v;
}

main() {
    int i, p, k;
    for(i = 0; i < group; i++) {
        isPrime[i] = TRUE;
    }
    for(i = 1; i < group; i++) {
        if(isPrime[i]){
            send(primeStarter[1], i);
            loc = i + i;
            while (loc < group) {
                isPrime[loc] = False;
                loc = loc + i;
            }
        } 
    }
    forall i = 1 to numberOfProcesses do {
        int m, q;
        int lowerBound = (i - 1) * group;
        int upperBound = i * group;
        int currLoc;

        cout << "Process: " << i << " - Lower: " << lowerBound << " and Upper: " << upperBound;
        for(m = lowerBound; m < upperBound; m++ ) {
            isPrime[m] = TRUE;
        }
        recv(primeStarter[i], q);
        cout << "got here recv init" << i  << q<< ENDL;
        if (i < numberOfProcesses) {
            send(primeStarter[i+1], q);
            cout << "got here send init" << i+1 << q<< ENDL;
        }
        while (q != endMarker) {
            currLoc = findLocalStart(lowerBound, q);
            while (currLoc <= upperBound) {
                isPrime[currLoc] = False;
                currLoc = currLoc + q;
            }
            recv(primeStarter[i], q);
            if(i < numberOfProcesses){
                send(primeStarter[i+1], q);
                        cout << "got here send continue" << i+1 << q<< ENDL;
            }
        }
    }

    for (p = 2; p < n; p++)
        cout << isPrime[p] << " " << p << endl;

}