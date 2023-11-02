/* PROGRAM Sieve */
#include <stdlib.h>
#include <math.h>
#define n 400
#define Chunk_size 20
#define End_Marker -1
boolean  Prime[n+1];
int num,loc;
int number_of_processes = n/Chunk_size;
int stream Prime_starter[21];/*number_of_processes+1*/
 /*oversized for testing with n up to 100*/

int find_local_start(int s, int t) { int v = s;
        if (v % t == 0)
        return s;
        else do
        {v++;
        }while( v% t != 0);
        return v;
}

main( ) {
int i;
int k;
int p;
for( k = 1; k <= Chunk_size; k++ ) {
  Prime[k] = TRUE;
}
for (k = 2; k <= Chunk_size; k++)
  if (Prime[k]) {
    send(Prime_starter[2], k);  /*Write into stream*/
    loc = k + k;
    while (loc <= Chunk_size)
    {
      Prime[loc] = False;
      loc = loc + k;
    }
  }
  send(Prime_starter[2], End_Marker);

forall i = 2 to number_of_processes do {
  int m, q, remainder;
  int lower_bound = (i-1)*Chunk_size+1;
  int upper_bound = i * Chunk_size;
  int my_loc;
  cout<< "Process " << i << " lower = "<< lower_bound<< "  Upper =  "<<
  upper_bound << ENDL;
  for( m = lower_bound; m <= upper_bound; m++ )
    Prime[m] = TRUE;

  recv(Prime_starter[i],q );
  cout << "got here recv init" << i  << q<< ENDL;
  if (i < number_of_processes)
  {send(Prime_starter[i+1],q);
  cout << "got here send init" << i+1 << q<< ENDL;}

  while (q != End_Marker)
  {
  my_loc = find_local_start(lower_bound, q);
  while (my_loc <= upper_bound)
  {
    Prime[my_loc] = False;
    my_loc = my_loc + q;
  }
  recv(Prime_starter[i],q );
  if (i < number_of_processes)
    {send(Prime_starter[i+1],q);

      cout << "got here send continue" << i+1 << q<< ENDL;}
  }
}

for (p = 1; p<=n; p++)
  cout<< Prime[p] << " " << p << ENDL;
}
