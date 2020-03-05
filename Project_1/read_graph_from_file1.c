#include <stdio.h>

void read_graph_from_file1 (char *filename, int *N, char ***table2D){
	FILE* datafile;
	int j, i, N_size;

	datafile = fopen(filename, "r");

	if (datafile == NULL) {
		printf("Failure to open file %s\n", filename);
		exit(0);
	}

	fscanf(datafile, "%*[^\n]\n");
	fscanf(datafile, "%*[^\n]\n");

	fscanf(datafile, "%*s %*s %d %*[^\n]\n", N);

	N_size = *N;
	
	*table2D = (char**)malloc(N_size * sizeof(char**));
	
	for (i = 0; i < N_size; i++) {
		(*table2D)[i] = (char*)malloc(N_size * sizeof(char*));
	}

	for (i = 0; i < N_size; i++) {
		for (j = 0; j < N_size; j++) {
			(*table2D)[i][j] = 0;
		}
	}

	fscanf(datafile, "%*[^\n]\n");

	while (fscanf(datafile, "%d %d", &j, &i) == 2) {
		(*table2D)[i][j] = 1;
	}

	fclose(datafile);
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

	return 0;
}