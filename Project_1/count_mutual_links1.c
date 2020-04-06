#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#include "read_graph_from_file1.c"

int count_mutual_links1 (int N, char **table2D, int *num_involvements) {
  int m_links, incoming;
  m_links = 0;
  #if defined(_OPENMP)
  {
    #pragma omp parallel for private(incoming) reduction(+:m_links)
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

int main(int argc, char* argv[]) {
	char* filename;
	char** table2D;
	int N;
	int N_size;

	if (argc < 2) {

		printf("Filename required.\n");
		exit(0);
	}
	filename = argv[1];

	read_graph_from_file1(filename, &N, &table2D);

  for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%d ", table2D[i][j]);
		}
		printf("\n");
	}

  int *num_involvements = (int*)malloc(N*sizeof(int*));
  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }
  int mutual_links;
  mutual_links = count_mutual_links1(N, table2D, num_involvements);
  printf("number of mutual links: %d\n", mutual_links);
  for (int i = 0; i < N; i++){
    printf("%d ", num_involvements[i]);
  }
  printf("\n");
	return 0;
}
