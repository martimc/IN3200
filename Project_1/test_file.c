#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

int main(int argc, char* argv[]) {
  char* filename1, *filename2;
  char** table2D;
  int N1, N2, N_size, mutual_links;
  clock_t start_read1, start_count1, end_read1, end_count1;

  if (argc < 2) {

    printf("Filename required.\n");
    exit(0);
  }

  filename1 = argv[1];
  printf("the filename is: %s\n", filename1);

  //start_read1 = clock();
  read_graph_from_file1(filename1, &N1, &table2D);
  //end_read1 = clock();
  int *num_involvements = (int*)malloc(N1*sizeof(int*));

  for (int i = 0; i < N1; i++){
    num_involvements[i] = 0;
  }

  start_count1 = clock();
  mutual_links = count_mutual_links1(N1, table2D, num_involvements);
  end_count1 = clock();
  printf("number of mutual links: %d\n", mutual_links);

  int n;
  printf("top n webpages: ");
  scanf("%d", &n);
  printf(" \n");
  top_n_webpages(N1, num_involvements, n);

  //printf("table2D: read file time: %e secs, count links time: %e secs.\n",
  //((double) (end_read1 - start_read1)) / CLOCKS_PER_SEC, ((double) (end_count1 - start_count1)) / CLOCKS_PER_SEC);

  printf(" \n");
  printf("start CRS-format: \n");
  printf(" \n");

	int N_links, * row_ptr, * col_idx;
  clock_t start_read2, start_count2, end_read2, end_count2;

	filename2 = argv[2];
  printf("the filename is: %s\n", filename2);

  //start_read2 = clock();
	read_graph_from_file2(filename2, &N2, &N_links, &row_ptr, &col_idx);
  //end_read2 = clock();

  for (int i = 0; i < N2; i++){
    num_involvements[i] = 0;
  }

  //start_count2 = clock();
  mutual_links = count_mutual_links2(N2, N_links, row_ptr, col_idx, num_involvements);
  //end_count2 = clock();
  printf("number of mutual links: %d\n", mutual_links);

  printf(" \n");

  top_n_webpages(N2, num_involvements, n);

  //printf("CRS-format: read file time: %e secs, count links time: %e secs.\n",
  //((double) (end_read2 - start_read2)) / CLOCKS_PER_SEC, ((double) (end_count2 - start_count2)) / CLOCKS_PER_SEC);

	return 0;
}
