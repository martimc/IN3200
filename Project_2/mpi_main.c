#include <stdio.h>
#include <string.h> /* For strlen */
#include <mpi.h> /* For MPI functions, etc */

const int MAX_STRING = 100;

int main(void) {
  char greeting[MAX_STRING];
  int comm_sz; /* Number of processes */
  int my_rank; /* My process rank */

  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  if (my_rank != 0) {
    sprintf(greeting, "Greetings from process %d of %d!", my_rank, comm_sz);
    MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }
  else {
    printf("Greetings from process %d of %d!\n", my_rank, comm_sz);
    for (int q = 1; q < comm_sz; q++) {
      MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf("%s\n", greeting);
    }
  }

MPI_Finalize();
return 0;
} /* main */

/*int main (int argc, char **argv){
  int M=0, N=0, rank, num_triple_friends;
  int **v=NULL;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  num_triple_friends = 0;
  if (rank==0) {
    // decide the values for M and N
    // allocate 2D array v and assign it with suitable values
  }
  //num_triple_friends = MPI_count_friends_of_ten (M, N, v);
  printf("MPI rank <%d>: number of triple friends=%d\n",
  rank, num_triple_friends);
  if (rank==0)
  // deallocation of 2D array v
  MPI_Finalize ();
  return 0;
}*/
