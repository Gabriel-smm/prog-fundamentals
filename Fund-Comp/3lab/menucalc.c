//Gabriel Marques
//menucalc.c for lab3
//the program calculate and display an operation, chosen by a user, with the inputed numbers also from the user

#include <stdio.h>
#include <math.h>

int printAskMenu();
double add(double x, double y);
double sub(double x, double y);
double mult(double x, double y);
double div(double x, double y);
 
int main () {


    printf("Hi! Welcome to your Menu Calculator!");
    int init = printAskMenu();

    while (init != 5){

        if (init < 1 || init > 5) {
            printf("That is not an option. You must chose a number between 1 and 5");
            init = printAskMenu();
            continue;
        }

        double x, y;
        double result;
        char *sym;
        
        printf("\nWhat is the first number of the operation? ");
        scanf("%lf", &x);

        printf("\nWhat is the second number of the operation? ");
        scanf("%lf", &y);


        if (init == 1){
            result = add(x,y);
            sym = "+"; 
        } else if (init == 2) {
            result = sub(x,y);
            sym = "-";
        } else if (init == 3) {
            result = mult(x,y);
            sym = "x";
        } else if (init == 4) {
            if (y == 0){
                printf("It is not possible to divide a number by 0");
                init = printAskMenu();
                continue;
            }
            result = div(x,y);
            sym = "/";
        } 


        printf("\n(%lf) %s (%lf) = %lf\n", x, sym, y, result);

        init = printAskMenu();
    }
    printf("bye!!\n");
    return 0;

}


double add(double x, double y){
    return x + y; 
}

double sub(double x, double y){
    return x - y; 
}

double mult(double x, double y){
    return x * y; 
}

double div(double x, double y){
    return x / y; 
}

int printAskMenu(){

    int operator;
    double x, y;
    printf("\n\nChoose 1 to add\nChoose 2 to subtract\nChoose 3 to multiply\nChoose 4 to divide\nChoose 5 to quit\n");
    printf("\n What is the desired operation? ");
    scanf("%d", &operator);

    return operator;
    
}



