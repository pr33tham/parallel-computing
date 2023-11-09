ARCHITECTURE MESH2(25);
#include <stdlib.h>
#include <math.h>

#define n 150 /*Processes*/
#define pointsOnMesh 70

float process_list[number_of_processes];
float stream global_sum_value[number_of_processes];

float start, end, h, my_sum, final_output;
int p, num, r;

float f(float l) {
    return sqrt(4 - l^2);
}

void integrationFunction(int myIndex, float start, float end, float h) {
    float l, sum = 0;
    int i;
    l = start + myIndex * (end - start) / n;

    for( i = 0; i < pointsOnMesh; i++) {
        sum = sum + f(l);
        l = l + h;
    }
    sum = h * sum;
    send(global_sum_value[myIndex], sum);
}

main() {
    start = 0;
    end = 2;
    int i;
    h  = (end - start) / (n * pointsOnMesh);
    forall i = 0 to n -1 do {
        int index;
        float sum = 0;
        float l = start + i * (end - start) / n;
        for(index = 0; index < pointsOnMesh; index++) {
            sum = sum + f(l);
            l = l + h;
        }
        sum = h * sum;
        send(global_sum_value[])
    }
}