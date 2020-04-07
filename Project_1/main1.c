#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char* argv[]) {
	char* filename;
	char** table2D;
	int N, N_size, mutual_links;
  int *num_involvements = (int*)malloc(N*sizeof(int*));

	if (argc < 2) {

		printf("Filename required.\n");
		exit(0);
	}
	filename = argv[1];

	read_graph_from_file1(filename, &N, &table2D);

  for (int i = 0; i < N; i++){
    num_involvements[i] = 0;
  }

  mutual_links = count_mutual_links1(N, table2D, num_involvements);
  printf("number of mutual links: %d\n", mutual_links);

  int n;
  printf("top n webpages: \n");
  scanf("%d", &n);
  top_n_webpages(N, num_involvements, n);

	return 0;
}
