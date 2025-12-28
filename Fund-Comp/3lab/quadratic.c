// Fund Comp
// Gabriel Marques - Quadratics.c - Lab 3, part 1
// The programs computes the roots based on the inputed quadratic coeficients until 0 is inputed to coeficient a 

#include <stdio.h>
#include <math.h>

float discriminant(float a,float b,float c);


int main() {


    double a, b, c, disc;
    double x1, x2;


  while (1){  
    printf("\nEnter the coefficients (a,b,c) of a quadratic equation: \n");
    printf("a: ");
    scanf("%lf", &a); 
    printf("b: ");
    scanf("%lf", &b);
    printf("c: ");
    scanf("%lf", &c);

    if(a==0)
      break;

    disc = discriminant(a, b, c);

    if (disc < 0) {
	  printf("This quadratic equation has no solution\n");
    } else if (disc == 0) {
	  x1 = (-b) / (2 * a);
	  printf("The equation has one solution and it is %f\n", x1);
    } else {
	  x1 = (- b + sqrt(disc)) / (2 * a);
	  x2 = (- b - sqrt(disc)) / (2 * a);
	  printf("The equation has two roots and they are %f and %f\n", x1, x2);
    }

  }

  printf("\nThe program ends here! Thank you!\n");
  

  return 0;
}



float discriminant (float a,float b,float c){
  return pow(b,2) - (4 * a * c);
}
