#include <stdio.h>
#include <stdlib.h>

int main(){
	int n;
	n = 10;
	int *array = malloc(n*sizeof(int));

	for (int i = 0; i < n; i++){
		array[i] = rand();
	}

	int max = array[0];
	int min = array[0];
	int length = 1;
	while (length < n){
		if (max < array[length]){
			max = array[length];
		}
		if (min > array[length]){
			min = array[length];
		}
		length++;
	}

	/*for (int i = 0; i < n; i++){
		printf("array value is %d \n", array[i]);
	}*/
	printf("max value is %d \n", max);
	printf("min value is %d \n", min);

	free(array);

	return 0;
}