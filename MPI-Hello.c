ARCHITECTURE HYPERCUBE(10);
#include <mpi.h>
int myrank, totalproc; 

main( ) {
  MPI_Init( );
  MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
  MPI_Comm_size(MPI_COMM_WORLD, &totalproc);
  cout << "Hello World from process" << myrank
       << " out of " << totalproc << endl;
  MPI_Finalize( );
}