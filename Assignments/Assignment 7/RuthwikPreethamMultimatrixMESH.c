ARCHITECTURE TORUS(7); 
#include <stdlib.h>
#define m 7
#define p 2 /*Size of partitions R_Preetham*/
typedef float partition[p+1][p+1];
partition A[m][m], B[m][m], C[m][m]; /*Master arrays and result array R_Preetham*/
partition stream Achan[m][m], stream Bchan[m][m]; /*Streams to communicate between processes R_Preetham*/
int i,j; /*Index integers for looping R_Preetham*/

void Multiply(int row, int col, value partition myA, value partition myB, partition mainC)
{
  int i,j,k,iter,above,left; 
  partition myC = {0}; /*Initialize array with zeroes R_Preetham*/
  if (row > 0) above = row-1;
    else above = m-1;
  if (col > 0) left = col-1;
    else left = m-1; 
  for (iter = 1; iter <= m; iter++) {
    send(Achan[row][left], myA); /*Send myA to the left row R_Preetham*/
	  send(Bchan[above][col], myB); /*Send myB to upper column R_Preetham*/

	  for (i = 1; i <= p; i++)
	   for (j = 1; j <= p; j++)
		  for (k = 1; k <= p; k++)
		    myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j]; /*Matrix multiplicaiton R_Preetham*/
	  recv(Achan[row][col], myA); /*Recieve myA* R_Preetham*/
	  recv(Bchan[row][col], myB); /*Recieve myB* R_Preetham*/
  }
  mainC = myC; /*Copy to the global result array C R_Preetham*/
}

main( ) {

  int k, l;
  /*Initialise Array A and B with random values R_Preetham*/
  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  for (k = 1; k <= p; k++)
	    for (l = 1; l <= p; l++) {
		    A[i][j][k][l] = (rand() % 100)/10.0;
		    B[i][j][k][l] = (rand() % 100)/10.0;
	     }


  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  fork (@i * m + j) /*Using fork to create prcesses as outer and inner forall is not efficient R_Preetham*/
      Multiply(i, j, A[i][(j+i)%m], B[(i+j)%m][j], C[i][j]); /*Calling Multiply function to perform matrix multiplication R_Preetham*/

  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  join;

  /*Display the computed array C to console R_Preetham*/
  cout.precision(4);
  for (i = 0; i < m; i++) {
	 for (j = 0; j < m; j++) {
	  cout << "partition[" << i << ", " << j << "]" << endl;
	  for (k = 1; k <= p; k++) {
		 for (l = 1; l <= p; l++)
		  cout << C[i][j][k][l] << ", ";
	    cout << endl;
	  }
	 }
  }
}
