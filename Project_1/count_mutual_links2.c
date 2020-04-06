#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  int m_links, incoming, num_threads;
  m_links = 0;
  #if defined(_OPENMP)
  {
    #pragma omp parallel
    {
      #pragma omp for private(incoming) reduction(+:m_links)
      for (int i = 0; i < N; i++){
        incoming = row_ptr[i+1]-row_ptr[i];
        if (incoming > 1){
          for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
            num_involvements[col_idx[j]] += incoming-1;
          }
          m_links += (incoming*(incoming-1))/2;
        }
      }
      num_threads = omp_get_num_threads();
    }
    printf("No. of threads is %d.\n",num_threads);
  }
  #else
  {
    for (int i = 0; i < N; i++){
      incoming = row_ptr[i+1]-row_ptr[i];
      if (incoming > 1){
        for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
          num_involvements[col_idx[j]] += incoming-1;
        }
        m_links += (incoming*(incoming-1))/2;
      }
    }
  }
  #endif
  return m_links;
}
