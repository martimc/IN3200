#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]){
  int n = 50;
  char *temperature = malloc(n*sizeof(char));
  char *time = malloc(n*sizeof(char));
  FILE *temp_file;
  char *filename;
  float *array = malloc(n*sizeof(float));

  if( argc < 2 ){
    printf("bad usage, one input argument");
    exit(1);
  }
  else{
    filename = argv[1];
  }

  if ((temp_file = fopen(filename, "rb")) == NULL){
    printf("Error! could not open file");
    exit(1);
  }

  int i = 0;
  while (fscanf(temp_file, "%s %s[^\n]", time, temperature) != EOF){
    i++;
    printf("time: %s, temperature: %f \n", time, (float)atof(temperature));
    array[i-1] = (float)atof(temperature);
  }
  int max = i;
  while (i-- >= 0){
      if (array[i] > array[max]){
        max = i;
      }
  }

  printf("max temp: %.2f at time: %s \n", array[max], &time[max]);

  fclose(temp_file);
  free(temperature); free(time); free(array);

  return 0;
}
