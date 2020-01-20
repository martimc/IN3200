#include <stdio.h>
#include <stdlib.h>

int main(){
	int nx, ny, nz;
	nx = 5;
	ny = 3;
	nz = 3;
	/*int *A_storage = (int*)malloc(nx*ny*nz*sizeof(int));*/
	int ***u = (int***)malloc(nx*sizeof(int**));

	for (int i = 0; i < nx; i++){
		u[i] = (int**)malloc(ny*sizeof(int*));
		for (int j = 0; j < ny; j++){
			u[i][j] = (int*)malloc(nz*sizeof(int));
		}
	}

	for (int i = 0; i < nx; i++){
		for (int j = 0; j < ny; j++){
			for (int k = 0; k < nz; k++){
				u[i][j][k] = i*ny*nz + j*nz + k;
			}
		}
	}


	
	for (int i = 0; i < nx; i++){
		for (int j = 0; j < ny; j++){
			free(u[i][j]);
		}
		free(u[i]);
	}
	free(u);

	return 0;
}