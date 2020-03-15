#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "read_graph_from_file2.c"

int count_mutual_links2(int N, int N_links, int *row_ptr, int *col_idx, int *num_involvements){
  int m_links, incoming;
  m_links = 0;
  for (int i = 0; i < N; i++){
    incoming = row_ptr[i+1]-row_ptr[i];
    if (incoming > 1){
      for (int j = row_ptr[i]; j < row_ptr[i+1]; j++){
        num_involvements[col_idx[j]] += incoming-1;
      }
      m_links += (incoming*(incoming-1))/2;
    }
  }
  return m_links;
}

int main(int argc, char* argv[]) {
	char* filename;
	int N, N_links, * row_ptr, * col_idx;

	if (argc < 2) {

		printf("Filename required.\n");
		exit(0);
	}
	filename = argv[1];

	read_graph_from_file1(filename, &N, &N_links, &row_ptr, &col_idx);

  int *num_involvements = (int*)malloc(N*sizeof(int*));
  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }

  int mutual_links;
  printf("start counting: \n");
  mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
  printf("number of mutual links: %d\n", mutual_links);

  printf("\n");
	return 0;
}
