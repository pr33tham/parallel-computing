#include <stdlib.h> 

int i;
int sum = 0;
main(){
    cout.precision(4);
    for( i = 1; i<=100;i++){
        sum = sum + i;
    }

    cout << "total sum = " << sum;
}