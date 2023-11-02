/* PROGRAM MatrixMultiplyParallel */ 
#include <stdlib.h>
#include <math.h>
#define n 10
float A[n+1][n+1], B[n+1][n+1], C[n+1][n+1]; 
int i, j; 

void VectorProduct(int i, int j) {
  float sum;
  int k;

  sum = 0;
  for (k = 1; k <= n; k++)
    sum = sum + A[i][k]*B[k][j];
  C[i][j] = sum;
}

void printMatrix(float p[n+1][n+1]) {
  int l, m;
  for (l = 1; l <= n; l++) {
    for (m = 1; m <= n; m++) 
      cout << p[l][m] << " ";
    cout << "\n";
  }
  cout << "\n";
}

main() { 
  cout.precision(8); /* use 8 significant digits for float output */
  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++) {
      a[i][j] = (rand() % 10000)/100.0;
      b[i][j] = (rand() % 10000)/100.0;
    }
      
 
  forall i = 1 to n do
    forall j = 1 to n do
      /*compute row i of A times column j of B in parallel */
      VectorProduct(i, j);
  
  cout << "A = " << "\n";
  printMatrix(A);
  cout << "\n";
  
  cout << "B = " << "\n";
  printMatrix(B);
  cout << "\n";
  
  cout << "C = " << "\n";  
  printMatrix(C);
  cout << "\n";
}