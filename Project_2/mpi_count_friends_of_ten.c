#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int mpi_count_friends_of_ten(int M, int N, int **v){
  int up_diag, down_diag, right, down, friends_of_ten, my_friends_of_ten, my_rank, comm_sz;
  int my_M, my_N, start, end, their_M, rows_left, start_idx, end_idx, interval, their_start, their_end;
  int **my_v, **their_v;
  friends_of_ten = 0;
  my_friends_of_ten = 0;

  MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  if (my_rank == 0){
    start = 0; start_idx = 0;
    end = M/comm_sz; end_idx = end;
    my_N = N;
    rows_left = M-end;
    if (rows_left < 2){
      my_M = end + rows_left;
    }
    else{
      my_M = end + 2;
    }
    my_v = (int**)malloc(my_M*sizeof(int*));
    for (int i = 0; i < my_M; i++){
      my_v[i] = (int*)malloc(my_N*sizeof(int));
    }
    for (int i = 0; i < my_M; i++){
      for (int j = 0; j < my_N; j++){
        my_v[i][j] = v[i][j];
      }
    }
    for (int j = 1; j < comm_sz; j++){
      start = j*M/comm_sz;
      end = (j+1)*M/comm_sz;
      interval = end-start;
      rows_left = M-end;

      if (rows_left < 2){
        their_M = interval + rows_left;
      }
      else{
        their_M = interval + 2;
      }
      if (start > 1){
        their_M += 2;
        their_start = 2;
        start -= 2;
      }
      else{
        their_start = 0;
      }
      their_end = their_start + interval;

      MPI_Send(&their_start, 1, MPI_INT, j, 0, MPI_COMM_WORLD);
      MPI_Send(&their_end, 1, MPI_INT, j, 1, MPI_COMM_WORLD);
      MPI_Send(&their_M, 1, MPI_INT, j, 2, MPI_COMM_WORLD);
      MPI_Send(&my_N, 1, MPI_INT, j, 3, MPI_COMM_WORLD);

      int *data = (int *)malloc(their_M*my_N*sizeof(int));
      their_v = (int**)malloc(their_M*sizeof(int*));
      for (int i = 0; i < their_M; i++){
        their_v[i] = &(data[my_N*i]);//(int*)malloc(my_N*sizeof(int));
      }
      for (int i = 0; i < their_M; i++){
        for (int j = 0; j < my_N; j++){
          their_v[i][j] = v[start + i][j];
        }
      }
      MPI_Send(&(their_v[0][0]), their_M*my_N, MPI_INT, j, 4, MPI_COMM_WORLD);
    }
    free(their_v);
  }
  else{
    MPI_Recv(&start_idx, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&end_idx, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&my_M, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&my_N, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int *data = (int *)malloc(my_M*my_N*sizeof(int));
    my_v = (int**)malloc(my_M*sizeof(int*));
    for (int i = 0; i < my_M; i++){
      my_v[i] = &(data[my_N*i]);//(int*)malloc(my_N*sizeof(int));
    }
    MPI_Recv(&(my_v[0][0]), my_M*my_N, MPI_INT, 0, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  if (my_M < 3 && my_N > 2){
    for (int i = start_idx; i < end_idx; i++){
      for (int j = 0; j < my_N-2; j++){
        right = my_v[i][j] + my_v[i][j+1] + my_v[i][j+2];
        if (right == 10){
          my_friends_of_ten += 1;
        }
      }
    }
  }
  else{
    for (int i = start_idx; i < end_idx; i++){
      for (int j = 0; j < my_N; j++){
        up_diag = 0; down_diag = 0; right = 0; down = 0;
        if (i < 2 && j < my_N-2){ // first two rows with every column until the last two
          right = my_v[i][j] + my_v[i][j+1] + my_v[i][j+2];
          down_diag = my_v[i][j] + my_v[i+1][j+1] + my_v[i+2][j+2];
          down = my_v[i][j] + my_v[i+1][j] + my_v[i+2][j];
        }
        else if (i > my_M-3 && j < my_N-2){ // last two rows with every column until the last two
          up_diag = my_v[i][j] + my_v[i-1][j+1] + my_v[i-2][j+2];
          right = my_v[i][j] + my_v[i][j+1] + my_v[i][j+2];
        }
        else if (i < my_M-2 && j > my_N-3){ // last two columns except the final two rows
          down = my_v[i][j] + my_v[i+1][j] + my_v[i+2][j];
        }
        else if (i > 1 && i < my_M-2 && j < my_N-2){ // everything except the first and last two rows and last two columns
          up_diag = my_v[i][j] + my_v[i-1][j+1] + my_v[i-2][j+2];
          right = my_v[i][j] + my_v[i][j+1] + my_v[i][j+2];
          down_diag = my_v[i][j] + my_v[i+1][j+1] + my_v[i+2][j+2];
          down = my_v[i][j] + my_v[i+1][j] + my_v[i+2][j];
        }
        if (up_diag == 10){
          my_friends_of_ten += 1;
        }
        if (right == 10){
          my_friends_of_ten += 1;
        }
        if (down_diag == 10){
          my_friends_of_ten += 1;
        }
        if (down == 10){
          my_friends_of_ten += 1;
        }
      }
    }
  }

  MPI_Allreduce(&my_friends_of_ten, &friends_of_ten, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

  free(my_v);
  return friends_of_ten;
}
