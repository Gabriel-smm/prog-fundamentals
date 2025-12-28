#include "polyfunc.h"

int main (){

    char infile[20];
    FILE *fp;
    Point coordPoints[30];

    printf("\nEnter name of the file: ");
    scanf("%s", infile);

    fp = fopen(infile, "r"); 
    if (!fp) {                  
        printf("file %s not found\n", infile);
        return 1;
    }
        int readings = initArr(fp, coordPoints);
        float perimeter = findPerimeter(coordPoints, readings);
        float area = findArea(coordPoints, readings);
        printf("The perimeter found is %.1f\n", perimeter);
        printf("The area found is %.1f\n", area);
        printf("\n");
    


}
