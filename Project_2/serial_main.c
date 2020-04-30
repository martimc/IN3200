#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "count_friends_of_ten.c"

int main(int argc, char* argv[]){
  int M, N, friends_of_ten, test;
  int **v;
  M = 6;
  N = 5;
  v = (int**)malloc(M*sizeof(int*));
  for (int i = 0; i < M; i++){
    v[i] = (int*)malloc(N*sizeof(int));
  }
  /*srand(time(NULL));
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      v[i][j] = rand()%9 + 1;
    }
  }*/
  v[0][0] = 1; v[0][1] = 5; v[0][2] = 6; v[0][3] = 3; v[0][4] = 1;
  v[1][0] = 2; v[1][1] = 4; v[1][2] = 4; v[1][3] = 1; v[1][4] = 7;
  v[2][0] = 7; v[2][1] = 2; v[2][2] = 3; v[2][3] = 1; v[2][4] = 2;
  v[3][0] = 3; v[3][1] = 2; v[3][2] = 2; v[3][3] = 5; v[3][4] = 3;
  v[4][0] = 4; v[4][1] = 6; v[4][2] = 2; v[4][3] = 5; v[4][4] = 2;
  v[5][0] = 3; v[5][1] = 2; v[5][2] = 2; v[5][3] = 5; v[5][4] = 3;

  friends_of_ten = count_friends_of_ten(M, N, v);

  printf("There is %d friend of ten in the given list\n", friends_of_ten);

  free(v);

  return 0;
}
