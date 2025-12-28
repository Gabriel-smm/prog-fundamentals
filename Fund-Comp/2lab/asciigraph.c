//Name: Gabriel da Silva Marques - Lab2, Assignment part 3
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main () {

	float x, y;

	printf("Plot for y=2*(sin(x)+1) for x from 0.0 to 15.0\n");

	// these variables will be used to find the minimum x and y values. I just assigned a random number above the Y range of the function so that the if stantements works in the first iteration
	float min_y = 10;
	float min_x = 0;

	//using the same logic for the first the minimum values, I just assigned a number below the Y range so that the second if statement starts at the first iteration
	float max_y = -10;
	float max_x = 0;

	printf("   X       Y");
	for(int i = 0; i <= 300; i++) {
		x = i * 0.05; // I want to visualize my equation in increments of 0.05 for x until 15.0 (which means 300 iterations)
		y = 2 *(sin(PI * (i * 0.05))+1.00);
		printf(" \n%6.2f  %6.2f  ", x,y);
		int num = (y + 0.18) * 10;

		if(min_y > y){
			min_y = y;
			min_x = x;
		}

		if(max_y < y){
			max_y = y;
			max_x = x;
		}



		for(int j = 1; j <= num; j++){
			printf("#");
	
		}
	}

	printf("\nThe maximum of %.2f was at %.2f", max_y, max_x);
	printf("\nThe mininum of %.2f was at %.2f\n", min_y, min_x);
	return 0;
}
