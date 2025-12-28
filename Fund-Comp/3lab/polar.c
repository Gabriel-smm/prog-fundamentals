//Gabriel Marques
//polar.c for Lab3
//this program converts cartesian coordinates into polar coordinates

#include <stdio.h>
#include <math.h>

int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);

#define PI 3.141592653589793

int main (){

    double x, y;

    //user's input
    printf("What is the X coordinate? ");
    scanf("%lf", &x);

    printf("\nWhat is the Y coordinate? ");
    scanf("%lf", &y);


    //calling functions
    show_info(get_quadrant(x,y), get_radius(x,y), get_angle(x,y));
    
    


    return 0;
}



/*     creating functions    */

void show_info(int quad, double radius, double angle){

    char *quadrant;

    if (quad == 1){
        quadrant = "I";
    } else if (quad == 2){
        quadrant = "II";
    } else if (quad == 3){
        quadrant = "III";
    } else {
        quadrant = "IV";
    }

    printf("The point lies in the quadrant %s\n", quadrant);
    printf("Its corresponding points on the polar plane are r = %lf, angle = %lf, (%lf, %lf) \n", radius, angle, radius, angle);

}

double get_angle(double x, double y){
    return  atan2(y, x) * (180.0 / PI); //atan2() gives the angle in radians, so the multiplication converts it to degrees
}

double get_radius(double x, double y){
    return sqrt( (pow(x, 2) + pow(y, 2)) ); // square root of x squared plus y squared
}


int get_quadrant(double x, double y){
    if (x > 0){
        if (y > 0){
            return 1;
        } else {
            return 4;
        }
    } else {
        if (y > 0){
            return 2;
        } else {
            return 3;
        }
    }
} 
