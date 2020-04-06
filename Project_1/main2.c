#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include "main2.h"

int main(int argc, char* argv[]) {
	char* filename;
	int N, N_links, * row_ptr, * col_idx;

	if (argc < 2) {

		printf("Filename required.\n");
		exit(0);
	}
	filename = argv[1];

	read_graph_from_file2(filename, &N, &N_links, &row_ptr, &col_idx);

  int *num_involvements = (int*)malloc(N*sizeof(int*));
  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }

  int mutual_links;
  mutual_links = count_mutual_links2(N, N_links, row_ptr, col_idx, num_involvements);
  printf("number of mutual links: %d\n", mutual_links);

  int n;
  printf("top n webpages: \n");
  scanf("%d", &n);
  top_n_webpages(N, num_involvements, n);

	return 0;
}
