#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void swap(int* xp, int* yp) {
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

int partition (int *arr, int low, int high, int *arr2) {
	int pivot = arr[high];
	int pivot2 = arr2[high];
	int i = (low-1);

	for (int j = low; j <= high-1; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(&arr[i], &arr[j]);
			swap(&arr2[i], &arr2[j]);
		}
		if (arr[j] == pivot) {
			if (arr2[j] < pivot2) {
				i++;
				swap(&arr[i], &arr[j]);
				swap(&arr2[i], &arr2[j]);
			}
		}
	}
	i++;
	swap(&arr[i], &arr[high]);
	swap(&arr2[i], &arr2[high]); 
	return (i);
}

void quicksort(int *sort, int low, int high, int *col_idx) {
	if (low <= high) {
		int pi = partition(sort, low, high, col_idx);

		quicksort(sort, low, pi-1, col_idx);
		quicksort(sort, pi+1, high, col_idx);
	}
}

void read_graph_from_file1 (char *filename, int *N, int *N_links, int **row_ptr, int **col_idx){
	FILE* datafile;
	int j, i, low, high, nodes, edges, *sort;

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
	for (i = 0; i < nodes+1; i++) {
		(*row_ptr)[i] = 0;
	}

	*col_idx = (int*)malloc((edges) * sizeof(int*));
	for (i = 0; i < edges; i++) {
		(*col_idx)[i] = 0;
	}
	sort = (int*)malloc((edges) * sizeof(int*));
	for (i = 0; i < edges; i++) {
		sort[i] = 0;
	}

	fscanf(datafile, "%*[^\n]\n");
	int l = 0;
	while (fscanf(datafile, "%d %d", &j, &i) == 2) {
		sort[l] = i;
		(*col_idx)[l] = j;
		l++;
	}
	fclose(datafile);
	printf("done reading file\n");
	/*int min_idx;
	for (i = 0; i < edges - 1; i++) {
		min_idx = i;
		for (j = i + 1; j < edges; j++) {
			if (sort[j] < sort[min_idx] || sort[j] == sort[min_idx] && (*col_idx)[j] < (*col_idx)[min_idx]) {
				min_idx = j;
			}
		}
		swap(&sort[min_idx], &sort[i]);
		swap(&(*col_idx)[min_idx], &(*col_idx)[i]);

		printf("number of sorts: %d \n", i);
	}*/
	low = 0; high = edges-1;

	quicksort(sort, low, high, (*col_idx));		

	int k = 1;
	for (i = 0; i < edges; i++) {
		if (sort[i] == k-1) {
			(*row_ptr)[k] += 1;
		}
		else if (sort[i] == k) {
			k += 1;
			(*row_ptr)[k] += (*row_ptr)[k-1] + 1;
		}
		else {
			for (j = 1; j <= sort[i] - k; j++) {
				(*row_ptr)[k + j] += (*row_ptr)[k];
			}
			(*row_ptr)[sort[i]+1] += (*row_ptr)[k] + 1;
			k = sort[i] + 1;
		}
	}
	
	if (k != nodes) {
		for (i = k; i <= nodes; i++) {
			(*row_ptr)[i] = (*row_ptr)[k];
		}
	}
}

int main(int argc, char* argv[]) {
	clock_t start_t, end_t, total_t;
	char* filename;
	int N, N_links, * row_ptr, * col_idx;

	if (argc < 2) {

		printf("Filename required.\n");
		exit(0);
	}
	filename = argv[1];

	start_t = clock();
	printf("Starting of the program, start_t = %ld\n", start_t);

	printf("Going to scan a big loop, start_t = %ld\n", start_t);

	read_graph_from_file1(filename, &N, &N_links, &row_ptr, &col_idx);

	end_t = clock();
	printf("End of the big loop, end_t = %ld\n", end_t);

	total_t = (double)((end_t - start_t) / CLOCKS_PER_SEC);
	printf("Total time taken by CPU: %ld\n", total_t);
	printf("Exiting of the program...\n");

	return 0;
}