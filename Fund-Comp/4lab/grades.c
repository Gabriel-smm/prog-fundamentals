//Gabriel Marques
//grades.c for lab4
//This program is supposed to compute the average and standard deviation of a given set o integers


#include <stdio.h>
#include <math.h>

float average(int arr[], int n);
float standardDeviation(int arr[], int n, float average);

int main()
{
    int grades[] =
        { 96,73,62,87,80,63,93,79,71,99,
        82,83,80,97,89,82,93,92,95,89,
        71,97,91,95,63,81,76,98,64,86,
        74,79,98,82,77,68,87,70,75,97,
        71,94,68,87,79 };
        
    float av, stdev;

    int n = sizeof(grades)/sizeof(int);
    printf("\nThere are %d grades in the array\n", n);


    av = average(grades, n);
    printf("Average is %f", av);

    
    stdev = standardDeviation(grades, n, av);
    printf("\nThe standard deviation is %f\n\n", stdev);
  
  return 0;
}



float average(int arr[], int n){
    float sum = 0;
    for(int i = 0; i < n; i++){
        sum += arr[i];        
    }
    return sum / (float)n;
}

float standardDeviation(int arr[], int n, float average){
    float sumSquared = 0;
    for(int i = 0; i < n; i++){
        sumSquared += (arr[i] - average) * (arr[i] - average);        
    }
    return sqrt(sumSquared / (float)(n - 1));
}
