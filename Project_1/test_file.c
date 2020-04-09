#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include "main.h"

int main(int argc, char* argv[]) {
  char* filename, *filename1, *filename2;
  char** table2D;
  int N1, N2, N_size, mutual_links;
  clock_t start_read1, start_count1, end_read1, end_count1;
  int N_links, * row_ptr, * col_idx;
  clock_t start_read2, start_count2, end_read2, end_count2;

  if (argc < 2) {

    printf("Filename required.\n");
    exit(0);
  }

  #if defined(_OPENMP)
  {
    filename1 = argv[1];
    printf("the file used for table2D is: %s\n", filename1);
    filename2 = argv[2];
    printf("the file used for CRS is: %s\n", filename2);

    start_read1 = clock();
    read_graph_from_file1(filename1, &N1, &table2D);
    end_read1 = clock();

    start_read2 = clock();
    read_graph_from_file2(filename2, &N2, &N_links, &row_ptr, &col_idx);
    end_read2 = clock();

    int *num_involvements1 = (int*)malloc(N1*sizeof(int*));
    int *num_involvements2 = (int*)malloc(N2*sizeof(int*));

    for (int i = 0; i < N1; i++){
      num_involvements1[i] = 0;
      num_involvements2[i] = 0;
    }

    start_count1 = clock();
    mutual_links = count_mutual_links1(N1, table2D, num_involvements1);
    end_count1 = clock();
    printf("number of mutual links from table2D: %d\n", mutual_links);

    start_count2 = clock();
    mutual_links = count_mutual_links2(N2, N_links, row_ptr, col_idx, num_involvements2);
    end_count2 = clock();
    printf("number of mutual links from CRS-format: %d\n", mutual_links);

    printf(" \n");

    int n;
    printf("top n webpages: ");
    scanf("%d", &n);
    printf(" \n");
    top_n_webpages(N1, num_involvements1, n);

    printf("table2D: read file time: %e secs, count links time: %e secs.\n",
    ((double) (end_read1 - start_read1)) / CLOCKS_PER_SEC, ((double) (end_count1 - start_count1)) / CLOCKS_PER_SEC);

    printf("CRS-format: read file time: %e secs, count links time: %e secs.\n",
    ((double) (end_read2 - start_read2)) / CLOCKS_PER_SEC, ((double) (end_count2 - start_count2)) / CLOCKS_PER_SEC);
  }
  #else
  {
    filename = argv[1];
    printf("the filename is: %s\n", filename);

    start_read1 = clock();
    read_graph_from_file1(filename, &N1, &table2D);
    end_read1 = clock();

    start_read2 = clock();
    read_graph_from_file2(filename, &N2, &N_links, &row_ptr, &col_idx);
    end_read2 = clock();

    int *num_involvements1 = (int*)malloc(N1*sizeof(int*));
    int *num_involvements2 = (int*)malloc(N2*sizeof(int*));

    for (int i = 0; i < N1; i++){
      num_involvements1[i] = 0;
      num_involvements2[i] = 0;
    }

    start_count1 = clock();
    mutual_links = count_mutual_links1(N1, table2D, num_involvements1);
    end_count1 = clock();
    printf("number of mutual links from table2D: %d\n", mutual_links);

    start_count2 = clock();
    mutual_links = count_mutual_links2(N2, N_links, row_ptr, col_idx, num_involvements2);
    end_count2 = clock();
    printf("number of mutual links from CRS-format: %d\n", mutual_links);

    printf(" \n");

    int n;
    printf("top n webpages: ");
    scanf("%d", &n);
    printf(" \n");
    top_n_webpages(N1, num_involvements1, n);

    printf("table2D: read file time: %e secs, count links time: %e secs.\n",
    ((double) (end_read1 - start_read1)) / CLOCKS_PER_SEC, ((double) (end_count1 - start_count1)) / CLOCKS_PER_SEC);

    printf("CRS-format: read file time: %e secs, count links time: %e secs.\n",
    ((double) (end_read2 - start_read2)) / CLOCKS_PER_SEC, ((double) (end_count2 - start_count2)) / CLOCKS_PER_SEC);
  }
  #endif

	return 0;
}
