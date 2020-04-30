#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "mpi_count_friends_of_ten.c"

int main (int argc, char **argv){
  int M, N, rank, num_triple_friends;
  int **v;
  M = 0; N = 0;

  MPI_Init (&argc, &argv);
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  num_triple_friends = 0;

  if (rank==0) {
    M = 6;
    N = 5;
    v = (int**)malloc(M*sizeof(int*));
    for (int i = 0; i < M; i++){
      v[i] = (int*)malloc(N*sizeof(int));
    }

    v[0][0] = 1; v[0][1] = 5; v[0][2] = 6; v[0][3] = 3; v[0][4] = 1;
    v[1][0] = 2; v[1][1] = 4; v[1][2] = 4; v[1][3] = 1; v[1][4] = 7;
    v[2][0] = 7; v[2][1] = 2; v[2][2] = 3; v[2][3] = 1; v[2][4] = 2;
    v[3][0] = 3; v[3][1] = 2; v[3][2] = 2; v[3][3] = 5; v[3][4] = 3;
    v[4][0] = 4; v[4][1] = 6; v[4][2] = 2; v[4][3] = 5; v[4][4] = 2;
    v[5][0] = 3; v[5][1] = 2; v[5][2] = 2; v[5][3] = 5; v[5][4] = 3;

  }
  num_triple_friends = mpi_count_friends_of_ten (M, N, v);

  printf("MPI rank <%d>: number of triple friends=%d\n", rank, num_triple_friends);
  if (rank==0){
    free(v);
  }

  MPI_Finalize ();
  return 0;
}
