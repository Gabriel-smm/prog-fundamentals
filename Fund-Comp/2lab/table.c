#include <stdio.h>
#include <math.h>


int main() {

	// data input from the user to defie columns and rows
	int x, y;
	printf("Enter number for x: ");
	scanf("%d", &x);
	printf("Enter number for y: ");
	scanf("%d", &y);


	//creating the first line, that labels the columns
	printf("*      ");
	for (int i = 1; i <= x;i++){
		printf("%d    ", i);
		
	}

	printf("\n   ");
	

	//creating the barrier between the x label
	for (int i = 1; i <= x; i++){
		printf("-----");

	}
	printf("\n");


	//nested loop for the rows and numbers
	for (int r = 1; r <= y; r++){
		printf("%2d |", r);
		for (int c = 1; c <= x; c++){
			printf("   %2d", c*r);
		}
		printf("\n");
	}

	return 0;
}
