#include <stdlib.h>

int number;
int i = 1; 
float fact = 1;

unsigned float factorial(int num) {
    for(i = 2; i <= num; i++){
        fact = fact * i;
    }
    return fact;
}

main(){
    cout.precision(10);
    cout << "Enter a positive number" << endl;
    cin >> number;
    cout << "Factorial is " << factorial(number);
}

