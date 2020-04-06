#include <stdio.h>
#include <stdlib.h>

void top_n_webpages(int num_webpages, int *num_involvements, int n){
	int *max_involvements, top_n_webpage, prev_webpage;
	max_involvements = malloc(n*sizeof(int));
	for (int i = 0; i < n; i++){
		max_involvements[i] = 0;
	}
	top_n_webpage = 0;
	for (int j = 0; j < num_webpages; j++){
		if (num_involvements[j] > max_involvements[0]){
			max_involvements[0] = num_involvements[j];
			top_n_webpage = j+1;
		}
	}
	printf("the nr. 1 webpage is %d with %d involvements.\n",
	top_n_webpage, num_involvements[top_n_webpage-1]);
	prev_webpage = top_n_webpage
	for (int i = 1; i < n; i++){
		if j != prev_webpage
		for (int j = 0; j < num_webpages; j++){
			if (num_involvements[j] >= max_involvements[i] && num_involvements[j] <= max_involvements[i-1]){
				max_involvements[i] = num_involvements[j];
				top_n_webpage = j+1;
			}
		}
		printf("the nr. %d webpage is %d with %d involvements.\n",
		i+1, top_n_webpage, num_involvements[top_n_webpage-1]);
	}
}
