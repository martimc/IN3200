#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int count_mutual_links1 (int N, char **table2D, int *num_involvements) {
  int m_links, incoming, num_threads;
  m_links = 0;
  #if defined(_OPENMP)
  {
    #pragma omp parallel
    {
      #pragma omp for private(incoming) reduction(+:m_links)
      for (int i = 0; i < N; i++){
        incoming = 0;
        for (int j = 0; j < N; j++){
          incoming += table2D[i][j];
        }
        for (int j = 0; j < N; j++){
          if (table2D[i][j] == 1){
            num_involvements[j] += incoming-1;
          }
        }
        if (incoming > 1){
          m_links += (incoming*(incoming-1))/2;
        }
        num_threads = omp_get_num_threads();
      }
    }
    printf("No. of threads is %d.\n",num_threads);
  }
  #else
  {
    for (int i = 0; i < N; i++){
      incoming = 0;
      for (int j = 0; j < N; j++){
        incoming += table2D[i][j];
      }
      for (int j = 0; j < N; j++){
        if (table2D[i][j] == 1){
          num_involvements[j] += incoming-1;
        }
      }
      if (incoming > 1){
        m_links += (incoming*(incoming-1))/2;
      }
    }
  }
  #endif
  return m_links;
}
