#include <stdio.h>
#include <stdlib.h>

void top_n_webpages(int num_webpages, int *num_involvements, int n){
	if (n > num_webpages){
		printf("too many webpages.\n");
		exit;
	}
	else
	{
	int max_involvements, *top_n_webpage, prev_webpage;
	max_involvements = 0;
	top_n_webpage = malloc(n*sizeof(int));
	for (int i = 0; i < n; i++){
		top_n_webpage[i] = 0;
	}
	for (int j = 0; j < num_webpages; j++){
		if (num_involvements[j] > max_involvements){
			max_involvements = num_involvements[j];
			top_n_webpage[0] = j+1;
		}
	}
	printf("the nr. 1 webpage is %d with %d involvements.\n",
	top_n_webpage[0], num_involvements[top_n_webpage[0]-1]);
	for (int i = 1; i < n; i++){
		max_involvements = 0;
		for (int j = 0; j < num_webpages; j++){
			if (num_involvements[j] >= max_involvements && num_involvements[j] < num_involvements[top_n_webpage[i-1]-1]){
				max_involvements = num_involvements[j];
				top_n_webpage[i] = j+1;
			}
			if (num_involvements[j] == num_involvements[top_n_webpage[i-1]-1]){
				for (int k = 0; k < i; k++){
					if (top_n_webpage[k]-1 == j){
						break;
					}
					if (k == i-1){
						max_involvements = num_involvements[j];
						top_n_webpage[i] = j+1;
					}
				}
			}
		}
	}
	for (int i = 1; i < n; i++){
		printf("the nr. %d webpage is %d with %d involvements.\n",
		i+1, top_n_webpage[i], num_involvements[top_n_webpage[i]-1]);
	}
	}
}
