#include <stdio.h>
#include <math.h>

int main(){
	int n;
	double sum;

	sum = 0;
	
	for (int i=0; i<=n; i++){
		sum += (double) pow(-1,i)*1/((double)pow(2,2*i));
	}
	printf("the sum is %f \n", sum);
	
	return 0;
}