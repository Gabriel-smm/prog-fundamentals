#include "polyfunc.h"

int initArr( FILE *fp, Point Arr[]){
    int count = 0;
    while(fscanf(fp, "%d %d", &Arr[count].x, &Arr[count].y) == 2){
	count++;
	if (count >= 30) break;
        
    }
	
    printf("\nThe %d vertices' coodinates read are: \n", count);


    printf("   X   |    Y\n");
    printf("-------+-------\n");
    for(int i = 0; i < count; i++){
    printf(" %3.d   |  %3.d\n", Arr[i].x, Arr[i].y);
    }
    printf("\n");

    return count;
}

float findPerimeter(Point arr[], int readings){
    float perimTotal = 0.0;
    for(int i = 0; i < readings - 1; i++){
        float length = sqrt(( pow( (arr[i + 1].x - arr[i].x), 2) + pow(arr[i + 1].y - arr[i].y, 2) ));
        perimTotal += length;
    }
    perimTotal += sqrt(( pow(arr[readings - 1].x - arr[0].x, 2) + pow(arr[readings - 1].y - arr[0].y, 2) ));
    return perimTotal;
}

float findArea(Point arr[], int readings){
    float addChain = 0;
    for (int i = 0; i < readings - 1; i++){
        addChain += (arr[i].x * arr[i + 1].y) - (arr[i].y * arr[i + 1].x);
    }
    addChain += (arr[readings - 1].x * arr[0].y) - (arr[readings - 1].y * arr[0].x);
    float area = 0.5 * fabs(addChain);
    
    return area;
}

