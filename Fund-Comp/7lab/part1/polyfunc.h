// polygon.c
// Gabriel Marques
// The following program computes the perimeter and area from the given coodinate points of a polygon

#include <stdio.h>
#include <math.h>

typedef struct {
   int x;
   int y;
} Point;

int initArr( FILE *fp, Point Arr[]);
float findPerimeter(Point arr[], int readings);
float findArea(Point arr[], int readings);

