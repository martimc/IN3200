#include <stdio.h>

void read_graph_from_file1 (char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){
	FILE* datafile;
	int j, i, nodes, edges, *sort, *temp_col;

	datafile = fopen(filename, "r");

	if (datafile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fscanf(datafile, "%*[^\n]\n");
	fscanf(datafile, "%*[^\n]\n");

	fscanf(datafile, "%*s %*s %d %*s %d\n", N, N_links);

	nodes = *N;
	edges = *N_links;
	*row_ptr = (int*)malloc((nodes + 1) * sizeof(int*));
	for (i = 0; i < nodes; i++) {
		(*row_ptr)[i] = 0;
	}
	(*row_ptr)[nodes] = edges;
	*col_idx = (int*)malloc((edges) * sizeof(int*));
	for (i = 0; i < edges; i++) {
		(*col_idx)[i] = 0;
	}
	sort = (int*)malloc((edges) * sizeof(int*));
	for (i = 0; i < edges; i++) {
		sort[i] = 0;
	}
	temp_col = (int*)malloc((edges) * sizeof(int*));
	for (i = 0; i < edges; i++) {
		temp_col[i] = 0;
	}

	fscanf(datafile, "%*[^\n]\n");
	int l = 0;
	while (fscanf(datafile, "%d %d", &j, &i) == 2) {
		for (int k = i+1; k < nodes; k++) {
			(*row_ptr)[k] += 1;
		}
		sort[l] = i;
		temp_col[l] = j;
		l++;
	}
	
	for (i = 0; i < nodes; i++) {
		int k = (*row_ptr)[i];
		for (j = 0; j < edges; j++) {
			if (sort[j] == i) {
				(*col_idx)[k] = temp_col[j];
				k++;
			}
		}
	}
	
	for (i = 0; i <= nodes; i++) {
		printf("%d ", (*row_ptr)[i]);
	}

	printf("\n");
	
	for (i = 0; i < edges; i++) {
		printf("%d ", (*col_idx)[i]);
	}

	fclose(datafile);
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

	return 0;
}