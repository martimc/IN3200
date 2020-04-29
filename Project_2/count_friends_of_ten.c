#include <stdio.h>
#include <stdlib.h>

int count_friends_of_ten(int M, int N, int **v){
  int up_diag, down_diag, right, down, friends_of_ten;
  friends_of_ten = 0;
  if (M < 3){
    for (int i = 0; i < M; i++){
      for (int j = 0; j < N-2; j++){
        right = v[i][j] + v[i][j+1] + v[i][j+2];
        if (right == 10){
          friends_of_ten += 1;
        }
      }
    }
    return friends_of_ten;
  }
  for (int i = 0; i < M; i++){
    for (int j = 0; j < N; j++){
      up_diag = 0; down_diag = 0; right = 0; down = 0;
      if (i < 2 && j < N-2){ // first two rows with every column until the last two
        right = v[i][j] + v[i][j+1] + v[i][j+2];
        down_diag = v[i][j] + v[i+1][j+1] + v[i+2][j+2];
        down = v[i][j] + v[i+1][j] + v[i+2][j];
      }
      else if (i > M-3 && j < N-2){ // last two rows with every column until the last two
        up_diag = v[i][j] + v[i-1][j+1] + v[i-2][j+2];
        right = v[i][j] + v[i][j+1] + v[i][j+2];
      }
      else if (i < M-2 && j > N-3){ // last two columns except the final two rows
        down = v[i][j] + v[i+1][j] + v[i+2][j];
      }
      else if (i > 2 && i < M-2 && j < N-2){ // everything except the first and last two rows and last two
        up_diag = v[i][j] + v[i-1][j+1] + v[i-2][j+2];
        right = v[i][j] + v[i][j+1] + v[i][j+2];
        down_diag = v[i][j] + v[i+1][j+1] + v[i+2][j+2];
        down = v[i][j] + v[i+1][j] + v[i+2][j];
      }
      if (up_diag == 10){
        friends_of_ten += 1;
      }
      if (right == 10){
        friends_of_ten += 1;
      }
      if (down_diag == 10){
        friends_of_ten += 1;
      }
      if (down == 10){
        friends_of_ten += 1;
      }
    }
  }

  return friends_of_ten;
}
